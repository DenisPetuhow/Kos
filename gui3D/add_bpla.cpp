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

    // Загружаем шрифт
    osgText::Font* font = osgText::readFontFile("font/times.ttf");
    if(font) {
        text->setFont(font);
    } else {
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
            BPLA_ALT_KM
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

    // Преобразование координат (высота - единая константа BPLA_ALT_KM)
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,
        cur_pos_bpla[0] * DEG_TO_RAD,
        BPLA_ALT_KM
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

    // Обновляем линии видимости к КА
    updateVisibilityLines(time, scene);
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

        // Удаляем все линии видимости
        for(auto it = m_visibility_lines.begin(); it != m_visibility_lines.end(); ++it) {
            if(it.value().valid()) {
                scene->m_root_agsk->removeChild(it.value());
            }
        }
        m_visibility_lines.clear();

        m_create_object = false;
        return true;
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════
// УСТАНОВКА СПИСКА КА ДЛЯ ПРОВЕРКИ ВИДИМОСТИ
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::setKaList(QVector<ASDOrbitalObjectPar> ka_list)
{
    m_ka_list = ka_list;
    qDebug() << "БПЛА #" << m_BPLA.id_bpla << "получил список из" << ka_list.size() << "КА";
}

// ═══════════════════════════════════════════════════════════════════════════
// ПРОВЕРКА ВИДИМОСТИ КА С ПОЗИЦИИ БПЛА
//
// ГЕОМЕТРИЯ СОГЛАСОВАНА С ЗЕЛЕНЫМ КОНУСОМ (addCone)!
//
// Конус в addCone строится так:
//   - ось: от КА к центру Земли (надир)
//   - угол полураствора: gamma
//   - радиус основания: r = h * tan(gamma)
//
// Значит БПЛА "внутри зоны покрытия" тогда и только тогда, когда
// угол между осью конуса (КА -> надир) и вектором (КА -> БПЛА)
// МЕНЬШЕ gamma. Это надирный угол.
//
// Старая версия сравнивала gamma с углом МЕСТА (elevation) от БПЛА -
// это ДРУГАЯ геометрия, из-за чего линии не совпадали с конусом:
// при большом gamma конус огромный, а Elev > gamma почти не выполнялся.
//
// Дополнительно проверяем, что КА над горизонтом БПЛА (нет "видимости
// сквозь Землю"), если gamma задан больше геометрического максимума.
// ═══════════════════════════════════════════════════════════════════════════
bool add_BPLA::isKaVisible(QDateTime time,
                           QVector<double> coordKA_AGESC_km,
                           QVector<double> coordBPLA_geo_deg,
                           double ka_gamma_deg)
{
    ASDCoordConvertor conv;

    // Обе точки приводим к ГСК на момент time
    QVector<double> ka_gsc = conv.convAgescToGsc(coordKA_AGESC_km, time);
    QVector<double> bpla_gsc = ASDCoordConvertor::convGeoToGsc(
        coordBPLA_geo_deg[1] * DEG_TO_RAD,   // lat, радианы
        coordBPLA_geo_deg[0] * DEG_TO_RAD,   // lon, радианы
        BPLA_ALT_KM                          // та же высота, что у модели БПЛА
    );

    // Ось конуса: от КА к центру Земли (надир) = -ka_gsc
    double ax = -ka_gsc[0];
    double ay = -ka_gsc[1];
    double az = -ka_gsc[2];

    // Вектор от КА к БПЛА
    double bx = bpla_gsc[0] - ka_gsc[0];
    double by = bpla_gsc[1] - ka_gsc[1];
    double bz = bpla_gsc[2] - ka_gsc[2];

    double na = sqrt(ax*ax + ay*ay + az*az);
    double nb = sqrt(bx*bx + by*by + bz*bz);
    if(na < 1e-9 || nb < 1e-9)
        return false;

    // Надирный угол: угол между осью конуса и направлением на БПЛА
    double cos_nadir = (ax*bx + ay*by + az*bz) / (na * nb);
    if(cos_nadir > 1.0)  cos_nadir = 1.0;
    if(cos_nadir < -1.0) cos_nadir = -1.0;
    double nadir_angle = acos(cos_nadir);

    // БПЛА вне конуса
    if(nadir_angle > ka_gamma_deg * DEG_TO_RAD)
        return false;

    // Проверка горизонта: угол места КА от БПЛА должен быть > 0.
    // Зенит БПЛА = направление bpla_gsc (от центра Земли),
    // Elev > 0 <=> скалярное произведение (зенит, БПЛА->КА) > 0
    double vx = ka_gsc[0] - bpla_gsc[0];
    double vy = ka_gsc[1] - bpla_gsc[1];
    double vz = ka_gsc[2] - bpla_gsc[2];
    double elev_dot = bpla_gsc[0]*vx + bpla_gsc[1]*vy + bpla_gsc[2]*vz;

    return (elev_dot > 0.0);
}

// ═══════════════════════════════════════════════════════════════════════════
// СОЗДАНИЕ ЛИНИИ ВИДИМОСТИ ОТ БПЛА ДО КА
// ═══════════════════════════════════════════════════════════════════════════
osg::ref_ptr<osg::Geode> add_BPLA::createVisibilityLine(QVector<double> bpla_agesc_m,
                                                         QVector<double> ka_agesc_m,
                                                         int ka_id)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
    vertices->push_back(osg::Vec3(bpla_agesc_m[0], bpla_agesc_m[1], bpla_agesc_m[2]));
    vertices->push_back(osg::Vec3(ka_agesc_m[0], ka_agesc_m[1], ka_agesc_m[2]));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    geometry->setVertexArray(vertices.get());

    // Желтая линия
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 0.9f)); // Желтый
    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

    osg::StateSet* state_set = geometry->getOrCreateStateSet();

    osg::LineWidth* line_width = new osg::LineWidth();
    line_width->setWidth(2.0f);
    state_set->setAttributeAndModes(line_width, osg::StateAttribute::ON);

    state_set->setMode(GL_BLEND, osg::StateAttribute::ON);
    state_set->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    state_set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(geometry.get());

    return geode;
}

// ═══════════════════════════════════════════════════════════════════════════
// ОБНОВЛЕНИЕ ЛИНИЙ ВИДИМОСТИ (вызывается каждый кадр)
// ═══════════════════════════════════════════════════════════════════════════
void add_BPLA::updateVisibilityLines(QDateTime time, ASDScene3D* scene)
{
    if(m_ka_list.size() == 0) return;

    QSet<int> currently_visible;
    QSet<int> newly_visible;
    QSet<int> lost_visibility;

    // Текущая позиция БПЛА (lon, lat)
    QVector<double> cur_pos_bpla_geo(2);
    cur_pos_bpla_geo[0] = cur_pos_bpla[0]; // lon
    cur_pos_bpla_geo[1] = cur_pos_bpla[1]; // lat

    // Координаты БПЛА в AGESC (для рисования линий).
    // Высота ТА ЖЕ, что у 3D модели БПЛА (BPLA_ALT_KM) - линия начинается
    // ровно в модели, а не на поверхности Земли.
    QVector<double> coord_bpla_gsc = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,
        cur_pos_bpla[0] * DEG_TO_RAD,
        BPLA_ALT_KM
    );
    QVector<double> coord_bpla_agesc = ASDCoordConvertor::convGscToAgesc(coord_bpla_gsc, time);
    QVector<double> bpla_agesc_m(3);
    bpla_agesc_m[0] = coord_bpla_agesc[0] * 1000;
    bpla_agesc_m[1] = coord_bpla_agesc[1] * 1000;
    bpla_agesc_m[2] = coord_bpla_agesc[2] * 1000;

    // Проверяем каждый КА
    for(int i = 0; i < m_ka_list.size(); i++)
    {
        ASDOrbitalObjectPar ka_par = m_ka_list[i];
        int ka_id = ka_par.idVeh;

        if(ka_id == 0) continue; // Пропускаем КА без ID

        // Получаем координаты КА в AGESC
        ASDOrbitalVehicle ka_vehicle(ka_par);
        QVector<double> ka_agesc_km = ka_vehicle.getCoordAGESC(time);

        // Получаем gamma для КА - ТОТ ЖЕ, что использован для зеленого конуса
        double ka_gamma = 30.0; // Резерв на случай пустого bsa
        if(ka_par.bsa.size() > 0) {
            ka_gamma = ka_par.bsa[0].gamma;
        } else {
            // bsa пуст - значит calc() не заполнил m_ka[i].bsa до setKaList().
            // Сообщаем один раз на КА, чтобы не заспамить лог.
            static QSet<int> warned;
            if(!warned.contains(ka_id)) {
                qWarning() << "[БПЛА] КА #" << ka_id << ka_par.nameVeh
                           << ": bsa пуст, используется gamma =" << ka_gamma << "° по умолчанию";
                warned.insert(ka_id);
            }
        }

        // Проверка видимости
        if(isKaVisible(time, ka_agesc_km, cur_pos_bpla_geo, ka_gamma))
        {
            currently_visible.insert(ka_id);

            // Создаем/обновляем линию если её нет
            if(!m_visibility_lines.contains(ka_id))
            {
                newly_visible.insert(ka_id);

                QVector<double> ka_agesc_m(3);
                ka_agesc_m[0] = ka_agesc_km[0] * 1000;
                ka_agesc_m[1] = ka_agesc_km[1] * 1000;
                ka_agesc_m[2] = ka_agesc_km[2] * 1000;

                osg::ref_ptr<osg::Geode> line = createVisibilityLine(bpla_agesc_m, ka_agesc_m, ka_id);
                scene->m_root_agsk->addChild(line);
                m_visibility_lines[ka_id] = line;
            }
            else
            {
                // Обновляем существующую линию
                QVector<double> ka_agesc_m(3);
                ka_agesc_m[0] = ka_agesc_km[0] * 1000;
                ka_agesc_m[1] = ka_agesc_km[1] * 1000;
                ka_agesc_m[2] = ka_agesc_km[2] * 1000;

                osg::ref_ptr<osg::Geode> old_line = m_visibility_lines[ka_id];
                if(old_line.valid()) {
                    scene->m_root_agsk->removeChild(old_line);
                }

                osg::ref_ptr<osg::Geode> new_line = createVisibilityLine(bpla_agesc_m, ka_agesc_m, ka_id);
                scene->m_root_agsk->addChild(new_line);
                m_visibility_lines[ka_id] = new_line;
            }
        }
    }

    // Удаляем линии к КА, которые больше не видны
    auto it = m_visibility_lines.begin();
    while(it != m_visibility_lines.end())
    {
        if(!currently_visible.contains(it.key()))
        {
            lost_visibility.insert(it.key());

            if(it.value().valid()) {
                scene->m_root_agsk->removeChild(it.value());
            }
            it = m_visibility_lines.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Компактный лог с временными метками
    if(newly_visible.size() > 0) {
        QString time_str = time.toString("yyyy-MM-dd HH:mm:ss");
        qDebug() << "[" << time_str << "] БПЛА #" << m_BPLA.id_bpla
                 << "→ Вход в зону видимости КА:" << newly_visible
                 << "(всего видно:" << currently_visible.size() << ")";
    }
    if(lost_visibility.size() > 0) {
        QString time_str = time.toString("yyyy-MM-dd HH:mm:ss");
        qDebug() << "[" << time_str << "] БПЛА #" << m_BPLA.id_bpla
                 << "→ Выход из зоны видимости КА:" << lost_visibility
                 << "(осталось видно:" << currently_visible.size() << ")";
    }
}
