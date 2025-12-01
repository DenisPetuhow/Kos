#include "add_bpla.h"

// Singleton для 3D модели (загружается 1 раз)
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

    m_create_object = true;  // ✅ ИСПРАВЛЕНО: true - объект должен существовать
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
        m_create_object = false;  // ✅ БПЛА достиг цели
    }

    return cur_pos;
}

// ═══════════════════════════════════════════════════════════════════
// ГЛАВНЫЙ МЕТОД ОТРИСОВКИ (ИСПРАВЛЕННЫЙ)
// ═══════════════════════════════════════════════════════════════════
void add_BPLA::repaint(QDateTime time, ASDScene3D *scene)
{
    qDebug() << "=== BPLA repaint START ===" << m_BPLA.id_bpla;

    if(!scene) {
        qDebug() << "ERROR: scene is NULL!";
        return;
    }

    if(!scene->m_root_gsk.valid()) {
        qDebug() << "ERROR: m_root_gsk is invalid!";
        return;
    }

    // ═══════════════════════════════════════════════════════════════
    // 1. РАСЧЁТ ТЕКУЩЕЙ ПОЗИЦИИ
    // ═══════════════════════════════════════════════════════════════
    cur_pos_bpla = getPos_BpLA(time);
    qDebug() << "Position (lon, lat):" << cur_pos_bpla[0] << cur_pos_bpla[1];
    qDebug() << "m_create_object:" << m_create_object;
    qDebug() << "m_transform.valid():" << m_transform.valid();

    // ✅ ИСПРАВЛЕНО: правильная логика удаления
    // Если БПЛА достиг цели (m_create_object == false) И объект существует, удаляем его
    if(m_create_object == false && m_transform.valid())
    {
        qDebug() << "Removing BPLA - reached destination";
        scene->m_root_gsk->removeChild(m_transform);
        m_transform = nullptr;
        return;
    }

    // Если БПЛА достиг цели, но объект уже удален, просто выходим
    if(m_create_object == false)
    {
        qDebug() << "BPLA reached destination, object already removed";
        return;
    }

    // Преобразование Geo → GSC
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,  // lat
        cur_pos_bpla[0] * DEG_TO_RAD,  // lon
        10                              // высота 10 км
    );
    qDebug() << "GSC coords (x,y,z):" << coord[0] << coord[1] << coord[2];

    // ═══════════════════════════════════════════════════════════════
    // 2. ОДНОКРАТНАЯ ЗАГРУЗКА 3D МОДЕЛИ (Singleton)
    // ═══════════════════════════════════════════════════════════════
    if(m_bpla == 0) {
        qDebug() << "Loading 3D model (singleton)...";
        m_bpla = new osg::MatrixTransform();

        // A. Попробуем загрузить 3D модель
        osg::ref_ptr<osg::MatrixTransform> model3d_object =
            scene->addObject(QString("gui3D/model.3ds"));

        if(model3d_object.valid()) {
            qDebug() << "3D model loaded successfully";
            // Масштабирование модели
            osg::Matrix scale_matrix = osg::Matrix::scale(osg::Vec3d(500, 500, 500));
            model3d_object->setMatrix(scale_matrix);

            // Загрузка иконки для дальних расстояний
            osg::ref_ptr<osg::MatrixTransform> model3d_icon =
                scene->addObjectIconPoint(QString("images/bpl.png"));

            // LOD (Level of Detail) - переключение по расстоянию
            osg::ref_ptr<osg::LOD> lod = new osg::LOD;
            lod->addChild(model3d_object, 0,      50000);   // 0-50 км: 3D модель
            lod->addChild(model3d_icon,   50000,  1e20);    // >50 км: иконка

            m_bpla->addChild(lod);
        } else {
            qDebug() << "3D model not found, using icon only";
            // Если модель не найдена, используем только иконку
            osg::ref_ptr<osg::MatrixTransform> model3d_icon =
                scene->addObjectIconPoint(QString("images/bpl.png"));

            if(model3d_icon.valid()) {
                m_bpla->addChild(model3d_icon);
            } else {
                qDebug() << "ERROR: Icon not found either!";
            }
        }
    }

    // ═══════════════════════════════════════════════════════════════
    // 3. СОЗДАНИЕ ЭКЗЕМПЛЯРА БПЛА (ТОЛЬКО ПЕРВЫЙ РАЗ!)
    // ═══════════════════════════════════════════════════════════════
    if(!m_transform.valid()) {
        qDebug() << "Creating BPLA object for first time";

        // A. Создание главной трансформации
        m_transform = new osg::MatrixTransform();
        m_transform->addChild(m_bpla.get());

        // B. Создание текстовой метки
        osg::Vec3 pos(0, 0, 0);
        osg::Vec4 color(1.0f, 1.0f, 0.0f, 1.0f);  // Жёлтый
        float size = 15;

        osgText::Text* text = new osgText::Text;
        text->setColor(color);
        text->setFont("font/times.ttf");
        text->setCharacterSize(size);
        text->setPosition(pos);
        text->setAxisAlignment(osgText::Text::SCREEN);

        // ✅ ИСПРАВЛЕНО: osgText::Text вместо osgText::String
        text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);

        text->setDrawMode(osgText::Text::TEXT);
        text->setText(
            QString("БПЛА #%1").arg(m_BPLA.id_bpla).toStdString(),
            osgText::String::ENCODING_UTF8
        );

        osg::ref_ptr<osg::Geode> geod = new osg::Geode();
        geod->addDrawable(text);

        // LOD для текста (видимость 500 м - 10 км)
        osg::ref_ptr<osg::LOD> lod_text = new osg::LOD;
        lod_text->addChild(geod, 500, 10000);

        osg::ref_ptr<osg::MatrixTransform> m_transform_text =
            new osg::MatrixTransform();
        m_transform_text->addChild(lod_text);

        // Смещение текста относительно модели
        osg::Matrix text_offset = osg::Matrix::translate(
            osg::Vec3d(0, 200, 0)  // 200 м вверх
        );
        m_transform_text->setMatrix(text_offset);

        m_transform->addChild(m_transform_text.get());

        // C. Вычисляем начальную матрицу трансформации
        osg::Matrix mt_translate, mt_rotate_lon, mt_rotate_lat,
                    mt_rotate_heading, mt_sum;

        mt_translate = osg::Matrix::translate(
            osg::Vec3d(coord[0]*1000, coord[1]*1000, coord[2]*1000)
        );

        mt_rotate_lon = osg::Matrix::rotate(
            osg::Quat(cur_pos_bpla[0] * DEG_TO_RAD, osg::Z_AXIS)
        );

        mt_rotate_lat = osg::Matrix::rotate(
            osg::Quat(M_PI_2 - cur_pos_bpla[1] * DEG_TO_RAD, osg::Y_AXIS)
        );

        mt_rotate_heading = osg::Matrix::rotate(
            osg::Quat(az_bpla, osg::Z_AXIS)
        );

        mt_sum = mt_rotate_heading * mt_rotate_lat * mt_rotate_lon * mt_translate;

        // D. Устанавливаем начальную матрицу и добавляем в сцену
        m_transform->setMatrix(mt_sum);
        scene->m_root_gsk->addChild(m_transform);

        qDebug() << "BPLA object created and added to scene";
    }
    // ═══════════════════════════════════════════════════════════════
    // 4. ОБНОВЛЕНИЕ ПОЗИЦИИ И ОРИЕНТАЦИИ (КАЖДЫЙ КАДР)
    // ═══════════════════════════════════════════════════════════════
    else {
        qDebug() << "Updating BPLA position";

        // ✅ ТОЛЬКО ОБНОВЛЯЕМ МАТРИЦУ, НЕ ПЕРЕСОЗДАЁМ ОБЪЕКТ!

        // Матрицы трансформации
        osg::Matrix mt_translate, mt_rotate_lon, mt_rotate_lat,
                    mt_rotate_heading, mt_sum;

        // 1. Перемещение в текущую позицию (в метрах)
        mt_translate = osg::Matrix::translate(
            osg::Vec3d(coord[0]*1000, coord[1]*1000, coord[2]*1000)
        );

        // 2. Вращение по долготе
        mt_rotate_lon = osg::Matrix::rotate(
            osg::Quat(cur_pos_bpla[0] * DEG_TO_RAD, osg::Z_AXIS)
        );

        // 3. Вращение по широте
        mt_rotate_lat = osg::Matrix::rotate(
            osg::Quat(M_PI_2 - cur_pos_bpla[1] * DEG_TO_RAD, osg::Y_AXIS)
        );

        // 4. Вращение по азимуту (направление полёта)
        mt_rotate_heading = osg::Matrix::rotate(
            osg::Quat(az_bpla, osg::Z_AXIS)
        );

        // 5. Итоговая матрица
        mt_sum = mt_rotate_heading * mt_rotate_lat * mt_rotate_lon * mt_translate;

        // ✅ ПРОСТО ОБНОВЛЯЕМ МАТРИЦУ!
        m_transform->setMatrix(mt_sum);
    }

    qDebug() << "=== BPLA repaint END ===";
}

bool add_BPLA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        // ✅ ДОБАВЛЕНА ПРОВЕРКА
        if(m_transform.valid()) {
            scene->m_root_gsk->removeChild(m_transform);
            m_transform = nullptr;
        }

        m_create_object = false;

        return true;
    }
    return false;
}
