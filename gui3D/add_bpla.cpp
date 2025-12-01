#include "add_bpla.h"

osg::ref_ptr<osg::MatrixTransform> add_BPLA::m_bpla = 0;

add_BPLA::add_BPLA(ASD_bpla_struct _BPLA, QString icon, ASDScene3D * scene)
{
    m_scene = scene;
    m_BPLA = _BPLA;
    m_icon = icon;
    cur_pos_bpla.resize(2);
    lat0_bpla    = _BPLA.lat0_bpla;
    lon0_bpla    = _BPLA.lon0_bpla;
    lat_fin_bpla = _BPLA.lat_fin_bpla;
    lon_fin_bpla = _BPLA.lon_fin_bpla;
    speed_bpla   = _BPLA.speed_bpla;
    t0_runBPLA   = _BPLA.t0_runBPLA;

    az_bpla = get_azimuth(lat0_bpla, lon0_bpla, lat_fin_bpla, lon_fin_bpla);
    cur_pos_bpla[0] = lat0_bpla;
    cur_pos_bpla[1] = lon0_bpla;

    // Расчёт дальности
    double tp = M_PI/2. - cur_pos_bpla[0]*DEG_TO_RAD;
    double ts = M_PI/2. - lat_fin_bpla*DEG_TO_RAD;
    double fp = cur_pos_bpla[1]*DEG_TO_RAD;
    double fs = lon_fin_bpla*DEG_TO_RAD;
    length_bpla = acos(cos(tp)*cos(ts) + sin(tp)*sin(ts)*cos(fs-fp)) * R_EARTH;

    m_create_object = true;
}

double add_BPLA::get_azimuth(const double lat1, const double lon1,
                             const double lat2, const double lon2)
{
    double tp = M_PI/2. - lat1*DEG_TO_RAD;
    double ts = M_PI/2. - lat2*DEG_TO_RAD;
    double fp = lon1*DEG_TO_RAD;
    double fs = lon2*DEG_TO_RAD;
    double length = acos(cos(tp)*cos(ts) + sin(tp)*sin(ts)*cos(fs-fp));

    double hsm, hsb;
    if(length < 50./6371.)
        return atan2((fs-fp)/sin(tp), (tp-ts) + 1e-6);

    hsm = atan2(cos((ts-tp)/2)*cos((fs-fp)/2), cos((ts+tp)/2)*sin((fs-fp)/2));
    hsb = atan2(sin((ts-tp)/2)*cos((fs-fp)/2), sin((ts+tp)/2)*sin((fs-fp)/2));

    return (hsm + hsb);
}

QPointF add_BPLA::coordpoint2(QPointF p, double D1, double A1)
{
    QPointF res;
    double A = PiTOPi(A1);
    double FI1 = p.y()*DEG_TO_RAD;
    double AL1 = p.x()*DEG_TO_RAD;

    double SA = sin(A);
    double CA = cos(A);
    double SX = sin(D1);
    double CX = cos(D1);
    double SF1 = sin(FI1);
    double CF1 = cos(FI1);

    double FI11 = asin(SF1*CX + CF1*SX*CA);
    if(FI11 > M_PI)
        FI1 = FI11 - M_PI;

    double ALA = asin(SA*SX / cos(FI11));
    if((CX - SF1*sin(FI11)) < 0.0)
        ALA = M_PI - ALA;

    ALA = ALA + AL1;
    if(ALA > M_PI)
        ALA = ALA - M_PI/2.;

    res.setX(PiTOPi(ALA)*RAD_TO_DEG);
    res.setY(FI11*RAD_TO_DEG);

    return res;
}

double add_BPLA::PiTOPi(double d)
{
    if (d >= -M_PI && d <= M_PI) return d;

    double modu = fmod(d, M_PI*2);

    if (modu < -M_PI) {
        modu += M_PI*2;
    }

    if (modu > M_PI) {
        modu -= M_PI*2;
    }

    return modu;
}

QVector<double> add_BPLA::getPos_BpLA(QDateTime dt)
{
    QVector<double> cur_pos(2);

    double s = (speed_bpla) * t0_runBPLA.secsTo(dt) / 3600.;
    QPointF aaa = coordpoint2(QPointF(lon0_bpla, lat0_bpla), s/6371.0, az_bpla);

    if(length_bpla - s >= 0) {
        cur_pos[0] = aaa.x(); // lon
        cur_pos[1] = aaa.y(); // lat
    } else {
        cur_pos[0] = lon_fin_bpla;
        cur_pos[1] = lat_fin_bpla;
        m_create_object = false;
    }

    return cur_pos;
}

void add_BPLA::repaint(QDateTime time, ASDScene3D *scene)
{
    qDebug() << "########## BPLA REPAINT START ##########" << m_BPLA.id_bpla;

    // Получаем текущую позицию
    cur_pos_bpla = getPos_BpLA(time);
    qDebug() << "Position:" << cur_pos_bpla;

    // Если достигли цели, удаляем объект
    if(m_create_object == false && m_transform.valid())
    {
        qDebug() << "УДАЛЯЕМ БПЛА - достигнута цель";
        scene->m_root_gsk->removeChild(m_transform);
        m_transform = nullptr;
        return;
    }

    if(m_create_object == false)
    {
        qDebug() << "БПЛА уже достиг цели";
        return;
    }

    // Преобразование координат Geo -> GSC (в километрах)
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,  // lat (широта)
        cur_pos_bpla[0] * DEG_TO_RAD,  // lon (долгота)
        10                              // высота 10 км
    );

    qDebug() << "GSC coordinates (km):" << coord[0] << coord[1] << coord[2];

    // Создаем матрицу трансформации
    osg::Matrix mt1, mt2, mt3, mt4, mt_sum;

    // Перемещение в позицию (преобразуем км в метры)
    mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000, coord[1]*1000, coord[2]*1000));

    // Вращения для правильной ориентации
    mt1 = osg::Matrix::rotate(osg::Quat(cur_pos_bpla[0]*DEG_TO_RAD, osg::Z_AXIS));
    mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2 - cur_pos_bpla[1]*DEG_TO_RAD, osg::Y_AXIS));
    mt3 = osg::Matrix::rotate(osg::Quat(az_bpla, osg::Z_AXIS));

    mt_sum = mt3 * mt2 * mt1 * mt4;

    // СОЗДАНИЕ ОБЪЕКТА (только первый раз)
    if(!m_transform.valid())
    {
        qDebug() << "СОЗДАЕМ ОБЪЕКТ БПЛА ВПЕРВЫЕ";

        m_transform = new osg::MatrixTransform();

        // Используем иконку если задана
        if(!m_icon.isEmpty())
        {
            qDebug() << "Загружаем иконку:" << m_icon;
            osg::ref_ptr<osg::MatrixTransform> icon = scene->addObjectIconPoint(m_icon);

            if(icon.valid())
            {
                osg::AutoTransform* at = new osg::AutoTransform;
                at->addChild(icon);
                at->setAutoScaleToScreen(true);
                at->setMinimumScale(0);
                at->setMaximumScale(1000);  // Увеличено для лучшей видимости
                m_transform->addChild(at);
                qDebug() << "Иконка загружена успешно";
            }
            else
            {
                qDebug() << "ОШИБКА: иконка не загрузилась!";
            }
        }
        else
        {
            qDebug() << "Иконка не задана, создаем точку";
        }

        // ВСЕГДА добавляем большую яркую точку для отладки
        qDebug() << "Создаем видимую точку";
        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
        osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

        // Точка в локальных координатах (0,0,0) - позиционируется матрицей
        vertices->push_back(osg::Vec3(0, 0, 0));
        geometry->setVertexArray(vertices.get());

        // ЯРКО-КРАСНЫЙ цвет
        osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
        color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));  // Красный
        geometry->setColorArray(color);
        geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
        geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));

        // ОГРОМНЫЙ размер точки для видимости
        osg::Point *point = new osg::Point;
        point->setSize(200.0);  // Очень большая точка
        geode->getOrCreateStateSet()->setAttribute(point);
        geode->addDrawable(geometry.get());

        // Отключаем освещение
        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

        m_transform->addChild(geode);

        // Устанавливаем матрицу и добавляем в сцену
        m_transform->setMatrix(mt_sum);
        scene->m_root_gsk->addChild(m_transform);

        qDebug() << "БПЛА создан:" << m_BPLA.id_bpla;
    }
    // ОБНОВЛЕНИЕ ПОЗИЦИИ (каждый кадр после создания)
    else
    {
        qDebug() << "Обновляем позицию БПЛА";
        m_transform->setMatrix(mt_sum);
    }

    qDebug() << "########## BPLA REPAINT END ##########";
}

bool add_BPLA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if(m_transform.valid()) {
            scene->m_root_gsk->removeChild(m_transform);
            m_transform = nullptr;
        }

        m_create_object = false;

        return true;
    }
    return false;
}
