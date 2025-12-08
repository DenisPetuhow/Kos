#include "add_bpla.h"

// Singleton для 3D модели
osg::ref_ptr<osg::MatrixTransform> add_BPLA::m_bpla_model = 0;

add_BPLA::add_BPLA(ASD_bpla_struct _BPLA, ASDScene3D * scene)
{
    m_scene = scene;
    m_BPLA = _BPLA;
    cur_pos_bpla.resize(2);

    lat0_bpla    = _BPLA.lat0_bpla;
    lon0_bpla    = _BPLA.lon0_bpla;
    lat_fin_bpla = _BPLA.lat_fin_bpla;
    lon_fin_bpla = _BPLA.lon_fin_bpla;
    speed_bpla   = _BPLA.speed_bpla;
    t0_runBPLA   = _BPLA.t0_runBPLA;

    az_bpla = get_azimuth(lat0_bpla, lon0_bpla, lat_fin_bpla, lon_fin_bpla);

    cur_pos_bpla[0] = lon0_bpla;
    cur_pos_bpla[1] = lat0_bpla;

    // Расчет дальности
    double tp = M_PI/2. - lat0_bpla*DEG_TO_RAD;
    double ts = M_PI/2. - lat_fin_bpla*DEG_TO_RAD;
    double fp = lon0_bpla*DEG_TO_RAD;
    double fs = lon_fin_bpla*DEG_TO_RAD;
    length_bpla = acos(cos(tp)*cos(ts) + sin(tp)*sin(ts)*cos(fs-fp)) * R_EARTH;

    m_create_object = true;

    qDebug() << "БПЛА #" << _BPLA.id_bpla << "инициализирован, дальность:" << length_bpla << "км";
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
    if (modu < -M_PI) modu += M_PI*2;
    if (modu > M_PI) modu -= M_PI*2;

    return modu;
}

QVector<double> add_BPLA::getPos_BpLA(QDateTime dt)
{
    QVector<double> cur_pos(2);

    double s = speed_bpla * t0_runBPLA.secsTo(dt) / 3600.;
    QPointF aaa = coordpoint2(QPointF(lon0_bpla, lat0_bpla), s/6371.0, az_bpla);

    if(length_bpla - s >= 0) {
        cur_pos[0] = aaa.x();
        cur_pos[1] = aaa.y();
    } else {
        cur_pos[0] = lon_fin_bpla;
        cur_pos[1] = lat_fin_bpla;
        m_create_object = false;
    }

    return cur_pos;
}

// ═══════════════════════════════════════════════════════════════════════════
// СОЗДАНИЕ 3D МОДЕЛИ БПЛА (Singleton)
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::createBplaModel(ASDScene3D* scene)
{
    qDebug() << "Загружаем 3D модель БПЛА (singleton)...";

    m_bpla_model = new osg::MatrixTransform();

    // Загружаем модель из файла
    osg::ref_ptr<osg::MatrixTransform> model_3d = scene->addObject(QString("gui3D/model.3ds"));

    if(!model_3d.valid())
    {
        qDebug() << "ОШИБКА: модель gui3D/model.3ds не найдена!";
        return;
    }

    qDebug() << "Модель загружена, масштабируем до размера БПЛА";

    // Масштабируем модель
    osg::Matrix scale_matrix = osg::Matrix::scale(200, 200, 200);
    model_3d->setMatrix(scale_matrix);

    m_bpla_model->addChild(model_3d);

    qDebug() << "Модель БПЛА готова (масштаб 200)";
}

// ═══════════════════════════════════════════════════════════════════════════
// СОЗДАНИЕ ТЕКСТОВОЙ МЕТКИ с номером БПЛА
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::createLabel()
{
    qDebug() << "Создаем текстовую метку БПЛА #" << m_BPLA.id_bpla;

    // Создаем текст
    osgText::Text* text = new osgText::Text();

    // Устанавливаем текст
    text->setText(
        QString("БПЛА #%1").arg(m_BPLA.id_bpla).toStdString(),
        osgText::String::ENCODING_UTF8
    );

    // Настройки текста
    text->setCharacterSize(30);  // Большой размер
    text->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));  // Желтый
    text->setPosition(osg::Vec3(0, 0, 800));  // Смещение вверх на 800м
    text->setAlignment(osgText::Text::CENTER_CENTER);
    text->setAxisAlignment(osgText::Text::SCREEN);  // Поворот к камере
    text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
    text->setDrawMode(osgText::Text::TEXT);
    text->setBackdropType(osgText::Text::DROP_SHADOW_BOTTOM_RIGHT);  // Тень для лучшей видимости

    // Пытаемся загрузить шрифт
    if(!text->setFont("font/times.ttf"))
    {
        qDebug() << "Шрифт font/times.ttf не найден, используется стандартный";
    }

    // Добавляем текст в Geode
    osg::ref_ptr<osg::Geode> text_geode = new osg::Geode();
    text_geode->addDrawable(text);

    // Настройка состояния для корректного отображения
    osg::StateSet* state_set = text_geode->getOrCreateStateSet();
    state_set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    state_set->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    state_set->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    state_set->setMode(GL_BLEND, osg::StateAttribute::ON);

    // Добавляем текст к главной трансформации
    m_transform->addChild(text_geode);

    qDebug() << "Текстовая метка создана и добавлена";
}

// ═══════════════════════════════════════════════════════════════════════════
// СОЗДАНИЕ 3D ЛИНИИ ТРАЕКТОРИИ
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::createTrajectoryLine(ASDScene3D* scene)
{
    qDebug() << "Создаем траекторию от (" << lon0_bpla << "," << lat0_bpla
             << ") до (" << lon_fin_bpla << "," << lat_fin_bpla << ")";

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
    const int num_segments = 20;

    for(int i = 0; i <= num_segments; i++)
    {
        double t = static_cast<double>(i) / num_segments;
        double angular_dist = (length_bpla / R_EARTH) * t;

        QPointF point = coordpoint2(QPointF(lon0_bpla, lat0_bpla), angular_dist, az_bpla);

        QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
            point.y() * DEG_TO_RAD,
            point.x() * DEG_TO_RAD,
            10
        );

        vertices->push_back(osg::Vec3(coord[0]*1000, coord[1]*1000, coord[2]*1000));
    }

    qDebug() << "Создано" << vertices->size() << "точек траектории";

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    geometry->setVertexArray(vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 0.8f));
    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, vertices->size()));

    osg::StateSet* state_set = geometry->getOrCreateStateSet();

    osg::LineWidth* line_width = new osg::LineWidth();
    line_width->setWidth(3.0f);
    state_set->setAttributeAndModes(line_width, osg::StateAttribute::ON);

    state_set->setMode(GL_BLEND, osg::StateAttribute::ON);
    state_set->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    state_set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::LineStipple* stipple = new osg::LineStipple();
    stipple->setFactor(2);
    stipple->setPattern(0x00FF);
    state_set->setAttributeAndModes(stipple, osg::StateAttribute::ON);
    state_set->setMode(GL_LINE_STIPPLE, osg::StateAttribute::ON);

    m_trajectory_line = new osg::Geode();
    m_trajectory_line->addDrawable(geometry.get());
    scene->m_root_gsk->addChild(m_trajectory_line);

    qDebug() << "Траектория создана";
}

// ═══════════════════════════════════════════════════════════════════════════
// ГЛАВНЫЙ МЕТОД ОТРИСОВКИ
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::repaint(QDateTime time, ASDScene3D *scene)
{
    // Расчет текущей позиции
    cur_pos_bpla = getPos_BpLA(time);

    // Проверка достижения цели
    if(m_create_object == false)
    {
        if(m_transform.valid()) {
            qDebug() << "БПЛА #" << m_BPLA.id_bpla << "достиг цели, удаляем";
            scene->m_root_gsk->removeChild(m_transform);
            m_transform = nullptr;
        }
        return;
    }

    // Преобразование координат
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,
        cur_pos_bpla[0] * DEG_TO_RAD,
        10
    );

    // Матрица трансформации
    osg::Matrix mt_translate, mt_rotate_lon, mt_rotate_lat, mt_rotate_heading, mt_sum;

    mt_translate = osg::Matrix::translate(coord[0]*1000, coord[1]*1000, coord[2]*1000);
    mt_rotate_lon = osg::Matrix::rotate(osg::Quat(cur_pos_bpla[0]*DEG_TO_RAD, osg::Z_AXIS));
    mt_rotate_lat = osg::Matrix::rotate(osg::Quat(M_PI_2 - cur_pos_bpla[1]*DEG_TO_RAD, osg::Y_AXIS));
    mt_rotate_heading = osg::Matrix::rotate(osg::Quat(az_bpla, osg::Z_AXIS));

    mt_sum = mt_rotate_heading * mt_rotate_lat * mt_rotate_lon * mt_translate;

    // Создание объектов (первый раз)
    if(!m_transform.valid())
    {
        qDebug() << "Создаем объект БПЛА #" << m_BPLA.id_bpla;

        // Главная трансформация
        m_transform = new osg::MatrixTransform();

        // Загружаем модель (singleton)
        if(m_bpla_model == 0)
            createBplaModel(scene);

        // Добавляем модель
        if(m_bpla_model.valid())
        {
            m_transform->addChild(m_bpla_model.get());
            qDebug() << "Модель добавлена";
        }

        // Создаем текстовую метку
        createLabel();

        // Создаем траекторию
        createTrajectoryLine(scene);

        // Устанавливаем позицию и добавляем в сцену
        m_transform->setMatrix(mt_sum);
        scene->m_root_gsk->addChild(m_transform);

        qDebug() << "БПЛА #" << m_BPLA.id_bpla << "создан и добавлен в сцену";
    }
    // Обновление позиции
    else
    {
        m_transform->setMatrix(mt_sum);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// УДАЛЕНИЕ ОБЪЕКТА
// ═══════════════════════════════════════════════════════════════════════════
bool add_BPLA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if(m_transform.valid()) {
            scene->m_root_gsk->removeChild(m_transform);
            m_transform = nullptr;
        }

        if(m_trajectory_line.valid()) {
            scene->m_root_gsk->removeChild(m_trajectory_line);
            m_trajectory_line = nullptr;
        }

        m_create_object = false;
        return true;
    }
    return false;
}
