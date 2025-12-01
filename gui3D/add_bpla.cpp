#include "add_bpla.h"

// ═══════════════════════════════════════════════════════════════════════════
// SINGLETON ДЛЯ 3D МОДЕЛИ БПЛА
// ═══════════════════════════════════════════════════════════════════════════
// Загружается один раз для всех экземпляров БПЛА, экономя память
osg::ref_ptr<osg::MatrixTransform> add_BPLA::m_bpla = 0;

// ═══════════════════════════════════════════════════════════════════════════
// КОНСТРУКТОР БПЛА
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Конструктор класса add_BPLA
 * @param _BPLA - структура с параметрами БПЛА (координаты старта/финиша, скорость, время)
 * @param icon - путь к файлу иконки для отображения БПЛА на дальних расстояниях
 * @param scene - указатель на 3D сцену, куда будет добавлен объект
 *
 * Инициализирует параметры БПЛА, вычисляет азимут и дальность полета
 */
add_BPLA::add_BPLA(ASD_bpla_struct _BPLA, QString icon, ASDScene3D * scene)
{
    m_scene = scene;
    m_BPLA = _BPLA;
    m_icon = icon;
    cur_pos_bpla.resize(2);

    // Копируем параметры из структуры
    lat0_bpla    = _BPLA.lat0_bpla;      // Широта старта (градусы)
    lon0_bpla    = _BPLA.lon0_bpla;      // Долгота старта (градусы)
    lat_fin_bpla = _BPLA.lat_fin_bpla;   // Широта финиша (градусы)
    lon_fin_bpla = _BPLA.lon_fin_bpla;   // Долгота финиша (градусы)
    speed_bpla   = _BPLA.speed_bpla;     // Скорость БПЛА (км/ч)
    t0_runBPLA   = _BPLA.t0_runBPLA;     // Время старта

    // Вычисление азимута (направления полета) от старта к финишу
    az_bpla = get_azimuth(lat0_bpla, lon0_bpla, lat_fin_bpla, lon_fin_bpla);

    // Начальная позиция = позиция старта
    cur_pos_bpla[0] = lat0_bpla;
    cur_pos_bpla[1] = lon0_bpla;

    // ───────────────────────────────────────────────────────────────────────
    // РАСЧЁТ ДАЛЬНОСТИ ПО СФЕРИЧЕСКОЙ ГЕОМЕТРИИ
    // ───────────────────────────────────────────────────────────────────────
    // Преобразуем широты в полярные углы (от полюса)
    double tp = M_PI/2. - cur_pos_bpla[0]*DEG_TO_RAD;  // Полярный угол старта
    double ts = M_PI/2. - lat_fin_bpla*DEG_TO_RAD;     // Полярный угол финиша
    double fp = cur_pos_bpla[1]*DEG_TO_RAD;            // Долгота старта (радианы)
    double fs = lon_fin_bpla*DEG_TO_RAD;               // Долгота финиша (радианы)

    // Формула расстояния по дуге большого круга на сфере
    // length_bpla = R * arccos(cos(θ1)*cos(θ2) + sin(θ1)*sin(θ2)*cos(φ2-φ1))
    length_bpla = acos(cos(tp)*cos(ts) + sin(tp)*sin(ts)*cos(fs-fp)) * R_EARTH;

    // m_create_object = true означает "БПЛА в полете, объект должен отображаться"
    // становится false когда БПЛА достигает цели
    m_create_object = true;
}

// ═══════════════════════════════════════════════════════════════════════════
// ВЫЧИСЛЕНИЕ АЗИМУТА (НАПРАВЛЕНИЯ ПОЛЕТА)
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Вычисляет азимут (направление) от точки 1 к точке 2 на сфере
 * @param lat1, lon1 - широта и долгота стартовой точки (градусы)
 * @param lat2, lon2 - широта и долгота конечной точки (градусы)
 * @return азимут в радианах (0 = север, π/2 = восток, π = юг, 3π/2 = запад)
 *
 * Использует сферическую тригонометрию для расчета направления полета
 */
double add_BPLA::get_azimuth(const double lat1, const double lon1,
                             const double lat2, const double lon2)
{
    // Преобразуем широты в полярные углы
    double tp = M_PI/2. - lat1*DEG_TO_RAD;
    double ts = M_PI/2. - lat2*DEG_TO_RAD;
    double fp = lon1*DEG_TO_RAD;
    double fs = lon2*DEG_TO_RAD;

    // Угловое расстояние между точками
    double length = acos(cos(tp)*cos(ts) + sin(tp)*sin(ts)*cos(fs-fp));

    double hsm, hsb;

    // Для малых расстояний (< 50 км) используем упрощенную формулу
    if(length < 50./6371.)
        return atan2((fs-fp)/sin(tp), (tp-ts) + 1e-6);

    // Для больших расстояний используем точную формулу сферической тригонометрии
    hsm = atan2(cos((ts-tp)/2)*cos((fs-fp)/2), cos((ts+tp)/2)*sin((fs-fp)/2));
    hsb = atan2(sin((ts-tp)/2)*cos((fs-fp)/2), sin((ts+tp)/2)*sin((fs-fp)/2));

    return (hsm + hsb);
}

// ═══════════════════════════════════════════════════════════════════════════
// ВЫЧИСЛЕНИЕ КООРДИНАТ ТОЧКИ НА СФЕРЕ ПОСЛЕ ПЕРЕМЕЩЕНИЯ
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Вычисляет новую точку на сфере после перемещения на расстояние D1 в направлении A1
 * @param p - исходная точка (x = долгота, y = широта в градусах)
 * @param D1 - угловое расстояние перемещения (радианы = км / R_EARTH)
 * @param A1 - азимут направления движения (радианы)
 * @return новая точка (x = долгота, y = широта в градусах)
 *
 * Используется для расчета текущей позиции БПЛА во время полета
 */
QPointF add_BPLA::coordpoint2(QPointF p, double D1, double A1)
{
    QPointF res;
    double A = PiTOPi(A1);                // Нормализуем азимут в диапазон [-π, π]
    double FI1 = p.y()*DEG_TO_RAD;        // Широта исходной точки (радианы)
    double AL1 = p.x()*DEG_TO_RAD;        // Долгота исходной точки (радианы)

    // Предвычисленные тригонометрические функции
    double SA = sin(A);
    double CA = cos(A);
    double SX = sin(D1);   // D1 - угловое расстояние
    double CX = cos(D1);
    double SF1 = sin(FI1);
    double CF1 = cos(FI1);

    // Формула расчета новой широты на сфере
    double FI11 = asin(SF1*CX + CF1*SX*CA);
    if(FI11 > M_PI)
        FI1 = FI11 - M_PI;

    // Формула расчета новой долготы
    double ALA = asin(SA*SX / cos(FI11));
    if((CX - SF1*sin(FI11)) < 0.0)
        ALA = M_PI - ALA;

    ALA = ALA + AL1;
    if(ALA > M_PI)
        ALA = ALA - M_PI/2.;

    // Преобразуем обратно в градусы и нормализуем
    res.setX(PiTOPi(ALA)*RAD_TO_DEG);
    res.setY(FI11*RAD_TO_DEG);

    return res;
}

// ═══════════════════════════════════════════════════════════════════════════
// НОРМАЛИЗАЦИЯ УГЛА В ДИАПАЗОН [-π, π]
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Нормализует угол в диапазон [-π, π]
 * @param d - входной угол в радианах
 * @return нормализованный угол в диапазоне [-π, π]
 */
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

// ═══════════════════════════════════════════════════════════════════════════
// РАСЧЕТ ТЕКУЩЕЙ ПОЗИЦИИ БПЛА
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Вычисляет текущую позицию БПЛА в заданное время
 * @param dt - текущее время
 * @return вектор координат [lon, lat] в градусах
 *
 * Вычисляет пройденное расстояние исходя из времени и скорости,
 * затем рассчитывает новые координаты на траектории полета
 */
QVector<double> add_BPLA::getPos_BpLA(QDateTime dt)
{
    QVector<double> cur_pos(2);

    // Вычисляем пройденное расстояние: S = V * t
    // t0_runBPLA.secsTo(dt) - время в секундах с момента старта
    // speed_bpla - скорость в км/ч, делим на 3600 для преобразования в км/сек
    double s = (speed_bpla) * t0_runBPLA.secsTo(dt) / 3600.;

    // Вычисляем новую позицию на сфере
    // s/6371.0 - преобразуем км в угловое расстояние (радианы)
    QPointF aaa = coordpoint2(QPointF(lon0_bpla, lat0_bpla), s/6371.0, az_bpla);

    // Проверяем, не достиг ли БПЛА цели
    if(length_bpla - s >= 0) {
        // Еще в полете
        cur_pos[0] = aaa.x(); // lon (долгота)
        cur_pos[1] = aaa.y(); // lat (широта)
    } else {
        // Достигли конечной точки
        cur_pos[0] = lon_fin_bpla;
        cur_pos[1] = lat_fin_bpla;
        m_create_object = false;  // Помечаем для удаления объекта
    }

    return cur_pos;
}

// ═══════════════════════════════════════════════════════════════════════════
// ГЛАВНЫЙ МЕТОД ОТРИСОВКИ БПЛА
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Обновляет отображение БПЛА на сцене
 * @param time - текущее время симуляции
 * @param scene - указатель на 3D сцену
 *
 * Вызывается каждый кадр для обновления позиции БПЛА.
 * При первом вызове создает 3D объект, при последующих - обновляет его матрицу трансформации
 */
void add_BPLA::repaint(QDateTime time, ASDScene3D *scene)
{
    qDebug() << "########## BPLA REPAINT START ##########" << m_BPLA.id_bpla;

    // ───────────────────────────────────────────────────────────────────────
    // 1. РАСЧЁТ ТЕКУЩЕЙ ПОЗИЦИИ
    // ───────────────────────────────────────────────────────────────────────
    cur_pos_bpla = getPos_BpLA(time);
    qDebug() << "Position:" << cur_pos_bpla;

    // ───────────────────────────────────────────────────────────────────────
    // 2. ПРОВЕРКА ДОСТИЖЕНИЯ ЦЕЛИ
    // ───────────────────────────────────────────────────────────────────────
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

    // ───────────────────────────────────────────────────────────────────────
    // 3. ПРЕОБРАЗОВАНИЕ КООРДИНАТ: Географические → Геоцентрические (GSC)
    // ───────────────────────────────────────────────────────────────────────
    // GSC (Geocentric Coordinate System) - система координат с центром в центре Земли
    // Результат в километрах: [x, y, z]
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
        cur_pos_bpla[1] * DEG_TO_RAD,  // lat (широта в радианах)
        cur_pos_bpla[0] * DEG_TO_RAD,  // lon (долгота в радианах)
        10                              // высота 10 км над поверхностью Земли
    );

    qDebug() << "GSC coordinates (km):" << coord[0] << coord[1] << coord[2];

    // ───────────────────────────────────────────────────────────────────────
    // 4. СОЗДАНИЕ МАТРИЦЫ ТРАНСФОРМАЦИИ
    // ───────────────────────────────────────────────────────────────────────
    // Матрица определяет позицию и ориентацию объекта в 3D пространстве
    osg::Matrix mt1, mt2, mt3, mt4, mt_sum;

    // mt4: Перемещение в позицию (координаты в метрах)
    mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000, coord[1]*1000, coord[2]*1000));

    // mt1: Вращение по оси Z (долгота)
    mt1 = osg::Matrix::rotate(osg::Quat(cur_pos_bpla[0]*DEG_TO_RAD, osg::Z_AXIS));

    // mt2: Вращение по оси Y (широта)
    // M_PI_2 = π/2, вычитаем широту для правильной ориентации
    mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2 - cur_pos_bpla[1]*DEG_TO_RAD, osg::Y_AXIS));

    // mt3: Вращение по азимуту (направление полета)
    mt3 = osg::Matrix::rotate(osg::Quat(az_bpla, osg::Z_AXIS));

    // Итоговая матрица: комбинация всех трансформаций
    // Порядок важен! Сначала вращения, потом перемещение
    mt_sum = mt3 * mt2 * mt1 * mt4;

    // ═══════════════════════════════════════════════════════════════════════
    // 5. СОЗДАНИЕ 3D ОБЪЕКТА (только при первом вызове)
    // ═══════════════════════════════════════════════════════════════════════
    if(!m_transform.valid())
    {
        qDebug() << "СОЗДАЕМ ОБЪЕКТ БПЛА ВПЕРВЫЕ";

        // Главная трансформация объекта
        m_transform = new osg::MatrixTransform();

        // ───────────────────────────────────────────────────────────────────
        // 5.1. ЗАГРУЗКА 3D МОДЕЛИ С LOD СИСТЕМОЙ (Singleton)
        // ───────────────────────────────────────────────────────────────────
        // LOD (Level of Detail) - система переключения детализации по расстоянию
        if(m_bpla == 0)
        {
            qDebug() << "Загружаем 3D модель БПЛА (singleton)...";
            m_bpla = new osg::MatrixTransform();

            // Пытаемся загрузить существующую 3D модель спутника
            // Используем модель спутника как временную замену для БПЛА
            osg::ref_ptr<osg::Node> sat_node = scene->m_root_models->getChild(0);

            if(sat_node.valid())
            {
                qDebug() << "Используем модель спутника для БПЛА";

                // Создаем трансформацию для масштабирования
                osg::ref_ptr<osg::MatrixTransform> model3d_scaled = new osg::MatrixTransform();

                // Клонируем модель спутника
                osg::ref_ptr<osg::Node> cloned_model = dynamic_cast<osg::Node*>(sat_node->clone(osg::CopyOp::DEEP_COPY_ALL));

                if(cloned_model.valid())
                {
                    model3d_scaled->addChild(cloned_model);

                    // Масштабируем модель (БПЛА меньше спутника)
                    osg::Matrix scale_matrix = osg::Matrix::scale(osg::Vec3d(300, 300, 300));
                    model3d_scaled->setMatrix(scale_matrix);

                    // ─────────────────────────────────────────────────────────
                    // 5.2. СОЗДАНИЕ ИКОНКИ ДЛЯ ДАЛЬНИХ РАССТОЯНИЙ
                    // ─────────────────────────────────────────────────────────
                    osg::ref_ptr<osg::MatrixTransform> icon_transform;

                    if(!m_icon.isEmpty())
                    {
                        qDebug() << "Загружаем иконку:" << m_icon;
                        icon_transform = scene->addObjectIconPoint(m_icon);

                        if(icon_transform.valid())
                        {
                            // AutoTransform - автоматически ориентирует объект к камере
                            osg::AutoTransform* at = new osg::AutoTransform;
                            at->addChild(icon_transform);
                            at->setAutoScaleToScreen(true);  // Масштаб зависит от расстояния
                            at->setMinimumScale(0);
                            at->setMaximumScale(1000);

                            // ─────────────────────────────────────────────────
                            // 5.3. НАСТРОЙКА LOD (LEVEL OF DETAIL)
                            // ─────────────────────────────────────────────────
                            // Переключение между моделью и иконкой в зависимости от расстояния до камеры
                            osg::ref_ptr<osg::LOD> lod = new osg::LOD;
                            lod->addChild(model3d_scaled, 0,      100000);  // 0-100 км: 3D модель
                            lod->addChild(at,             100000, 1e20);    // >100 км: иконка

                            m_bpla->addChild(lod);
                            qDebug() << "LOD система создана: модель (0-100км), иконка (>100км)";
                        }
                        else
                        {
                            qDebug() << "Иконка не загрузилась, используем только 3D модель";
                            m_bpla->addChild(model3d_scaled);
                        }
                    }
                    else
                    {
                        qDebug() << "Иконка не задана, используем только 3D модель";
                        m_bpla->addChild(model3d_scaled);
                    }
                }
                else
                {
                    qDebug() << "ОШИБКА: не удалось клонировать модель";
                }
            }
            else
            {
                qDebug() << "ПРЕДУПРЕЖДЕНИЕ: модель спутника не найдена";
            }
        }

        // Добавляем модель к трансформации
        if(m_bpla.valid() && m_bpla->getNumChildren() > 0)
        {
            m_transform->addChild(m_bpla.get());
        }

        // ───────────────────────────────────────────────────────────────────
        // 5.4. ДОБАВЛЕНИЕ ОТЛАДОЧНОЙ ТОЧКИ (ВСЕГДА ВИДИМАЯ)
        // ───────────────────────────────────────────────────────────────────
        qDebug() << "Создаем видимую отладочную точку";
        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
        osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

        // Точка в локальных координатах (0,0,0)
        vertices->push_back(osg::Vec3(0, 0, 0));
        geometry->setVertexArray(vertices.get());

        // Ярко-красный цвет для отладки
        osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
        color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
        geometry->setColorArray(color);
        geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
        geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));

        // Большой размер для видимости
        osg::Point *point = new osg::Point;
        point->setSize(150.0);
        geode->getOrCreateStateSet()->setAttribute(point);
        geode->addDrawable(geometry.get());

        // Отключаем освещение для точки (всегда яркая)
        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

        m_transform->addChild(geode);

        // ───────────────────────────────────────────────────────────────────
        // 5.5. СОЗДАНИЕ 3D ТРАЕКТОРИИ ПОЛЕТА
        // ───────────────────────────────────────────────────────────────────
        if(!m_trajectory_line.valid())
        {
            createTrajectoryLine(scene);
        }

        // ───────────────────────────────────────────────────────────────────
        // 5.6. ФИНАЛИЗАЦИЯ: установка матрицы и добавление в сцену
        // ───────────────────────────────────────────────────────────────────
        m_transform->setMatrix(mt_sum);
        scene->m_root_gsk->addChild(m_transform);

        qDebug() << "БПЛА создан и добавлен в сцену:" << m_BPLA.id_bpla;
    }
    // ═══════════════════════════════════════════════════════════════════════
    // 6. ОБНОВЛЕНИЕ ПОЗИЦИИ (каждый кадр после создания)
    // ═══════════════════════════════════════════════════════════════════════
    else
    {
        qDebug() << "Обновляем позицию БПЛА";
        // Просто обновляем матрицу трансформации
        // Геометрия не пересоздается - высокая производительность!
        m_transform->setMatrix(mt_sum);
    }

    qDebug() << "########## BPLA REPAINT END ##########";
}

// ═══════════════════════════════════════════════════════════════════════════
// УДАЛЕНИЕ ОБЪЕКТА БПЛА ИЗ СЦЕНЫ
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Удаляет объект БПЛА из 3D сцены
 * @param scene - указатель на 3D сцену
 * @return true если удаление успешно, false если сцена уже закрывается
 *
 * Вызывается при закрытии приложения или явном удалении БПЛА
 */
bool add_BPLA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if(m_transform.valid()) {
            scene->m_root_gsk->removeChild(m_transform);
            m_transform = nullptr;
        }

        // Удаляем траекторию
        if(m_trajectory_line.valid()) {
            scene->m_root_gsk->removeChild(m_trajectory_line);
            m_trajectory_line = nullptr;
        }

        m_create_object = false;

        return true;
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════
// СОЗДАНИЕ 3D ЛИНИИ ТРАЕКТОРИИ ПОЛЕТА
// ═══════════════════════════════════════════════════════════════════════════
/**
 * @brief Создает 3D линию, показывающую траекторию полета БПЛА
 * @param scene - указатель на 3D сцену
 *
 * Рисует пунктирную линию от точки старта до точки финиша БПЛА.
 * Линия создается вдоль дуги большого круга на поверхности Земли.
 * Для плавности линия разбивается на сегменты (20 точек).
 */
void add_BPLA::createTrajectoryLine(ASDScene3D* scene)
{
    qDebug() << "Создаем 3D траекторию БПЛА от (" << lon0_bpla << "," << lat0_bpla
             << ") до (" << lon_fin_bpla << "," << lat_fin_bpla << ")";

    // ───────────────────────────────────────────────────────────────────────
    // 1. СОЗДАНИЕ МАССИВА ТОЧЕК ТРАЕКТОРИИ
    // ───────────────────────────────────────────────────────────────────────
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    const int num_segments = 20;  // Количество сегментов для плавной кривой

    // Генерируем точки вдоль траектории
    for(int i = 0; i <= num_segments; i++)
    {
        // Вычисляем промежуточную позицию (от 0 до 1)
        double t = static_cast<double>(i) / num_segments;

        // Угловое расстояние вдоль траектории
        double angular_dist = (length_bpla / R_EARTH) * t;  // В радианах

        // Вычисляем координаты промежуточной точки
        QPointF point = coordpoint2(
            QPointF(lon0_bpla, lat0_bpla),  // Стартовая точка
            angular_dist,                    // Угловое расстояние
            az_bpla                          // Азимут
        );

        // Преобразуем географические координаты в геоцентрические (GSC)
        QVector<double> coord = ASDCoordConvertor::convGeoToGsc(
            point.y() * DEG_TO_RAD,  // lat (широта)
            point.x() * DEG_TO_RAD,  // lon (долгота)
            10                        // высота 10 км
        );

        // Добавляем точку в массив (координаты в метрах)
        vertices->push_back(osg::Vec3(
            coord[0] * 1000,
            coord[1] * 1000,
            coord[2] * 1000
        ));
    }

    qDebug() << "Создано" << vertices->size() << "точек траектории";

    // ───────────────────────────────────────────────────────────────────────
    // 2. СОЗДАНИЕ ГЕОМЕТРИИ ЛИНИИ
    // ───────────────────────────────────────────────────────────────────────
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    geometry->setVertexArray(vertices.get());

    // Цвет линии: ярко-зеленый с прозрачностью
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 0.8f));  // RGBA: зеленый, 80% непрозрачность
    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    // Тип примитива: LINE_STRIP (непрерывная линия через все точки)
    geometry->addPrimitiveSet(
        new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, vertices->size())
    );

    // ───────────────────────────────────────────────────────────────────────
    // 3. НАСТРОЙКА ВНЕШНЕГО ВИДА ЛИНИИ
    // ───────────────────────────────────────────────────────────────────────
    osg::StateSet* state_set = geometry->getOrCreateStateSet();

    // Толщина линии
    osg::LineWidth* line_width = new osg::LineWidth();
    line_width->setWidth(3.0f);  // 3 пикселя
    state_set->setAttributeAndModes(line_width, osg::StateAttribute::ON);

    // Включаем смешивание (blending) для прозрачности
    state_set->setMode(GL_BLEND, osg::StateAttribute::ON);
    state_set->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    // Отключаем освещение для линии (всегда яркая)
    state_set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    // Пунктирная линия (требует включения stipple)
    osg::LineStipple* line_stipple = new osg::LineStipple();
    line_stipple->setFactor(2);      // Фактор повтора шаблона
    line_stipple->setPattern(0x00FF); // Шаблон: 00000000 11111111 (пунктир)
    state_set->setAttributeAndModes(line_stipple, osg::StateAttribute::ON);

    // Включаем режим пунктирной линии
    state_set->setMode(GL_LINE_STIPPLE, osg::StateAttribute::ON);

    // ───────────────────────────────────────────────────────────────────────
    // 4. СОЗДАНИЕ GEODE И ДОБАВЛЕНИЕ В СЦЕНУ
    // ───────────────────────────────────────────────────────────────────────
    m_trajectory_line = new osg::Geode();
    m_trajectory_line->addDrawable(geometry.get());

    // Добавляем траекторию в корневой узел сцены
    scene->m_root_gsk->addChild(m_trajectory_line);

    qDebug() << "3D траектория создана и добавлена в сцену";
}
