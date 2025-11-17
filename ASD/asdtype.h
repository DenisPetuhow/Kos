/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdtype.h.\n
 ** Описание: Содержит описание базовых переменных и констант.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 23.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:
 **
 **
 *****************************************************************************/

#ifndef ASDTYPE_H
#define ASDTYPE_H
#include <QColor>
#include <QDateTime>
#include <QString>
#include <QVector>
#include <QMap>



/*************************************************************************
 * ОПИСАНИЕ ТИПА ПОСТОЯННЫХ
 *************************************************************************/
#define ALFA_EARTH    1./298.25784          //!< Коэффицент полярного сжатия Земли

#define R_MOON        1737.1                //!< Средний радиус Луны (км).


#define OMEGA_EARTH   7292115e-11           //!< Скорость вращения Земли (рад/с).
#define K_EARTH       398600.4418             //!< Гравитационная постоянная Земли  (км^3/с^2).
#define K2_EARTH      -1.7555e10            //!< Вторая гармоника гравитационного поля Земли (км^5/c^2).
#define R_EARTH       6371                  //!< Средний радиус Земли (км).
#define R_EARTH_EQU   6378.137              //!< Экваториальный радиус (км).
#define R_EARTH_POL   6356.751              //!< Полярный радиус (км).
#define DEG_TO_RAD    1.7453292519943e-2    //!< Коэффициент перевода из градусов в радианы.
#define RAD_TO_DEG    57.295779513082       //!< Коэффициент перевода из радианов в градусы.
#define C20           K2_EARTH/(K_EARTH*pow(R_EARTH_EQU,2)) //!< Второй гравитационный коэффицент
//используются в стандартной атмосфере
#define R_GAS             8.31432               //!< Газовая пос
#define MC            0.02896442            //!< Молярная маса воздуха на нулевой высоте.
#define GS            9.80665               //!< Среднее значение ускорения свободного падения на уровне моря на широте 45.32.33.
#define AR            6356767.              //!< Средний радис земли (М).
#define NA            6.02257e23            //!< Число Авагадро.
//математические константы
#define DEG_TO_RAD    1.7453292519943e-2    //!< Постоянная для преобразования градусов в радианы.
#define RAD_TO_DEG    57.295779513082       //!< Постоянная для преобразования радиан в градусы.

/*************************************************************************
 * ПЕРЕЧИСЛЕНИЯ
 *************************************************************************/

enum TypeZoneObserv
{
    konuas, //!< конус
    pyramid //!< пирамида с прямоугольным основанием
};

//! \brief Перечисление содержит типы траекторий БР
enum TypeTrajectBR
{
    optimal, //!< оптимальная
    flat, //!< настильная
    hinged //!< навесная
};

//! \brief Перечисление содержит типы систем координат.
enum SystemCoord
{
    AGESC, //!< Абсолютная Геоцентрическая Экваториальная СК.
    GSC, //!< Гринвичская СК.
    TSC, //!< Топоцентрическая СК.
    OSC, //!< Орбитальная СК.
    KepSC //!< Кеплерова СК.
};





//! \brief Перечисление содержит типы прогноза.
enum Forecast
{
    F_CENTRAL, //!< Прогноз с учетом центрального гравитационного поля Земли.
    F_KEP, //!< Прогноз в кеплеровых уровнениях движения.
    F_NORMAL //!< Прогноз с учетом полярного сжатия Земли.
};


//! \brief Перечисление содержит типы бортовой аппаратуры.
enum BseType
{
    OER = 0, //!< Оптико-электронная разведка.
    RLR = 1, //!< Радио-локационная разведка.
    RTR = 2, //!< Радио-техническая разведка.
    NAVIGATION = 3, //!< Навигационный системы.
    COMMUNICATION = 4, //!< Системы связи.
    BAL_OBJ = 5, //!< Баллистический объект.
    OERT=6,//!< Телевизионная Оптико-электронная разведка.
    OERF=7,//!< фото Оптико-электронная разведка.
    RLRF=8,//!< фото радиолокационный обзор.
    UN = 9 //!< Неопределено.
};

//! \brief Перечисление содержит типы начальных условий.
enum InitDataType
{
    KEPLER, //!< Кеплер
    ECI, //!< АГЭСК
    TLE //!< Радио-техническая разведка
};

/*************************************************************************
 * СТРУКТУРЫ
 *************************************************************************/
struct ASD_bpla_struct{

    int id_bpla;
    double speed_bpla;
    double lon0_bpla;
    double lat0_bpla;
    double lon_fin_bpla;
    double lat_fin_bpla;
    double az_bpla;
    double length_bpla;
    QDateTime t0_runBPLA;
    int time_interval; // интервал оповещения о местеположении (минуты)
    bool flag_plan = false;
};



//! \brief Структура данных характерезующих полет баллистической ракеты
struct ASDParFlightBalRoc
{
    QDateTime timeStart; //!< Время старта баллистической ракеты
    QDateTime timeDrop; //!< Время падения баллистической ракеты
    double heightMax; //!< Высота апогея
    double distance; //!< Дальность полета
    QVector <double> heightBR; //!< Массив высот баллистической ракеты с шагом секунда
    QVector <double> velocityBr; //!< Скорость БР
    QVector <double> angleVelocityBr; //!< Угол наклона вектора скорости
};
//! \brief Структура данных характерезующих полет противоракеты
struct ASDParFlightAntiRoc
{
    QDateTime timeStart; //!< Время старта баллистической ракеты
    QDateTime timeIntercept; //!< Время перехвата баллистической ракеты
    double distanceIntercept; //!< Дальность перехвата баллистической ракеты от точки старта противоракеты
    double velosityIntercept; //!< Относительная скорость встречи перехватчика и баллистической ракетой
    double velosityAut; //!< Скорость в конце активного участка
    double heightIntercept; //!< Высота перехвата
};

enum ASDFrequency
{
    HF=0,
    P=1,
    VHF=2,
    UHF=3,
    L=4,
    S=5,
    C=6,
    X=7,
    Ku=8,
    K=9,
    Ka=10,
    mm=11,
    mmV=12,
    mmW=13
};

static QStringList ASDFrequency_string(QStringList()<<"HF"<<"P"<<"VHF"<<"UHF"<<"L"<<"S"<<"C"<<"X"<<"Ku"<<"K"<<"Ka"<<"mm"<<"mmV"<<"mmW");
enum Tasks
{
    SERVICE,
    MONITORING,
    POSITIONING
};
enum ModulationTypes{
    mod_Otehr,
    mod_BPSK,
    mod_PSK4,
    mod_PSK16,
    mod_QAM16,
    mod_PSK8,
    mod_QAM32
};
enum AntennaTypes{
    ant_Other,
    ant_AFAR,
    ant_Mirr,
    ant_Horn,
    ant_Pin,
    ant_Measuring
};
enum PolarizationCoherency{
    polar_1,
    polar_2,
    polar_3,
    polar_4,
    polar_5
};

//! \brief Структура данных характерезующих работу системы ПКО
struct ASDParJobRKO
{
    QDateTime timeDetect; //!< Время обнаружения баллистической ракеты
    QString nameDetect; //!< Средство, которое обноруживыает БР
    double flightTime; //!< Подлетное время БР
};

struct ASDAngleObjSsc
{
    double pitch; //!< ╤â╨│╨╛╨╗ ╤é╨░╨╜╨│╨░╨╢╨░
    double yaw; //!< ╤â╨│╨╛╨╗ ╤Ç╤ï╤ü╨║╨░╨╜╨╕╤Å
    double roll; //!< ╤â╨│╨╛╨╗ ╨║╤Ç╨╡╨╜╨░
    ASDAngleObjSsc()
    {
        pitch = 0;
        yaw = 0;
        roll = 0;
    }
};
//! \brief Структура исходных данных для расчета параметров активного участка траектории.
struct ASDAutPar
{
    double massWarhead; //!< Масса головной части (кг).
    double massFirstStage; //!< Масса первой ступени (кг).
    double massTwoStage; //!< Масса ретьей ступени (кг).
    double massThreeStage; //!< Масса nhtnmtq ступени (кг).
    double massFuelFirstStage; //!< Масса топлива первой ступени (кг).
    double massFuelTwoStage; //!< Масса топлива второй ступени (кг).
    double massFuelThreeStage; //!< Масса топлива третьей ступени (кг).
    double massSecFirstStage; //!< Секундный расход топлива первой ступени (кг).
    double massSecTwoStage; //!< Секундный расход топлива второй ступени (кг).
    double massSecThreeStage; //!< Секундный расход топлива третьей ступени (кг).
    double specificImpulseEngineFirstStage; //!< Удельный импульс тяги первого двигателя (м/с).
    double specificImpulseEngineTwoStage; //!< Удельный импульс тяги второго двигателя (м/с).
    double specificImpulseEngineThreeStage; //!< Удельный импульс тяги третьего двигателя (м/с).
    double diameterRocket; //!< Диаметр ракеты (равен диаметру ступени)(с).
    double lenghtRocket; //!< Длина ракеты (м).
    double lenghFairing; //!< Длина головной части (м).
    double radiusFairing; //!< Радиус затупления головной части (м).
    double areaNozzleEnginesFirstStage; //!< Площадь среза сопла двигателя первой ступени (м<sup>2</sup>).
    double areaNozzleEnginesTwoStage; //!< Площадь среза сопла двигателя второй ступени (м<sup>2</sup>).
    double areaNozzleEnginesThreeStage; //!< Площадь среза сопла двигателя третьей ступени (м<sup>2</sup>).
    double timeWorkEngineFirstStage; //!< Время работы двигателя первой ступени (с).
    double timeWorkEngineTwoStage; //!< Время работы двигателя второй ступени (с).
    double timeWorkEngineThreeStage; //!< Время работы двигателя третьей ступени (с).
    double timeFullFlight; //!< Полное время полета БР (с).
    double integrationStepFirst; //!< Шаг интегрирования, первая ступень (с).
    double integrationStepTwo; //!< Шаг интегрирования, вторая ступень (с).
    ASDAutPar()
    {
        memset(this, 0, sizeof(ASDAutPar));
    }
};
/*!
 * \brief Углы взаимного расположения обьектов в космическом простанстве
 */


struct ASDAngleMounting
{
    union
    {
        double azimuth;
        double pitch;
    };
    union
    {
        double elevation;
        double yaw;
    };
    double roll;
    double dist;
    ASDAngleMounting()
    {
        pitch=0;
        yaw=0;
        roll=0;
    }
};

//typedef ASDAngleMounting ASDAngleObjSsc;
typedef ASDAngleMounting ASDAngleObjConSc;
//struct ASDAngleMounting
//{
//    double pitch; //!< тангаж
//    double yaw;   //!< рыскание
//    double roll;  //!< крен
//    ASDAngleMounting()
//    {
//        pitch = 0;
//        yaw = 0;
//        roll = 0;
//    }
//};

/// Следующие две структуры дублируются. Нужно удалить.

//typedef  ASDAngleMounting ASDAngleObjSsc;
//typedef  ASDAngleMounting ASDAngleObjConSc;


/*!
 * \brief боковой лепесток
 */
struct ASDSideLobe
{
    int type; //!< тип бокового лепестка (1 - лепескок с сечением в виде эллипса, 2 - лепесток тороид
    double angle_azimuth; //!< угол в азимутальной плоскости - в плоскости рыскания
    double angle_elev;   //!< угол в угломестной плоскоти - в плоскости тангажа

    double deltaV;//!< угол раствора по вертикали. перпендикулярно плоскости орбиты
    double deltaH;//!< угол раствора по горизонтали. по плоскости орбиты
    double power;//!<
    ASDSideLobe()
    {
        type = 0;
    }
};

//! \brief Структура параметров текущего положения объекта относительно точки старта.
struct ASDCurPos
{
    double time; //!< Время с момента запуска (с).
    double velocity; //!< Скорость РН (м/с).
    double height; //!< Высота (м).
    double geoAngle; //!< Геоцентрический угол (рад).
    double angleInclinVel; //!< Угол наклона вектора скорости \todo единицы измерения.
    ASDCurPos()
    {
        memset(this, 0, sizeof(ASDCurPos));
    }
};

//! \brief Структура параметров активного участа полета ракеты.
struct ASDMotionProgramPar
{
    double timeVertical; //!< Длительность вертикального участка (с).
    double factorVertic; //!< Некоторый постоянный коэффицент для рассматриваемого типа ракеты \todo откуда берется.
    double angleAttack; //!< Предельное значение угла атаки на дозвуковом участке траектории \todo единицы измерения.
    double derTangageTwoStage; //!< Производная по углу тангажа для второй ступени.
    double derTangageThreeStage; //!< Производная по углу тангажа для третей ступени.
    double azimuth; //!< Азимут стрельбы
    double longitude_start; //!< Долгота точки старта.
    double latitude_start; //!< Широта точки старта.

};

/*!
 * \brief Структура содержащая параметры баллистического объекта.
 */
struct ASDBallisticVehicleParam
{
    QString name; //!< Название баллистического объекта.
    int variant; //!< Вид баллистического обьекта. 0 - Минитмен, 1 - Трайден
    QDateTime dateTimeStart; //!< Дата и время старта.
    int typeTrassa; //!< Тип траектории 0 - оптимальная, 1 - настильная, 2 - навесная.
    QString name_start; //!< точка старта
    QString name_stop; //!< точка падения
    double longEnd; //!< Долгота точки падения.
    double latEnd; //!< Широта точки падения.
    double launchAzimuth; //!< Азимут запуска
    int quantityStage; //!< Число ступеней в РН
    double range;  //!< Дальность полета РН
    double rangeMax; //!< Максимальная дальность полета, определяемая ТТХ
    double tau_R;
    ASDAutPar autPar;
    ASDMotionProgramPar motionProgramPar;
    int id; //!< уникальный номер
    bool check; //!< участие в моделировании
    ASDBallisticVehicleParam()
    {
        id = 0;
        check = true;
    }
};

//! \brief Структура параметров пассивного участка.
struct ASDDescendPar
{
    double radiusFairing; //!< Радиус затупления (м).
    double lenghFairing; //!< Длина затупления (м).
    double diameter; //!< Диаметр спускаемого объекта (м).
    double lenght; //!< Длина спускаемого объекта (м).
    double m; //!< Масса объекта (м).
};

//! \brief Структура начальных условий КА (в элементах Кеплера).
struct ASDScKeplerInitData
{
    QString name;//!< Название.
    double i;//!< Наклонение, рад.
    double l;//!< Долгота восходящего узла, рад.
    double e;//!< Эксцентриситет.
    double a;//!< Большая полуось орбиты, км.
    double u;//!< Аргумент широты , рад.
    double omega;//!< Аргумент perig , рад.
    //double t_epoch;//!< эпоха юлианская
    QDateTime t_epoch;//!< Дата и время начальных данных.
};

//! \brief Структура параметров переходной орбиты.
struct ASDTransferOrbit
{
    double i;//!< Наклонение, рад.
    double l;//!< Долгота восходящего узла, рад.
    double e;//!< Эксцентриситет.
    double a;//!< Большая полуось орбиты, км.
    double omega;//!< Аргумент широты перигея , рад.
    double dV1; //!< Величина импульса перелета на переходную орбиту, км/с.
    double dV2; //!< Величина импульса ухода с переходной орбиты, км/с (если нужно).
    ASDTransferOrbit()
    {
        dV1 = 0;
        dV2 = 0;
    }
};

//! \brief Структура начальных условий КА AGS (ECI)
struct ASDScEciInitData
{
    QString name;//!< Наименование космиеского аппарата.
    double x;//!< Координаты x,км.
    double y;//!< Координаты y, км.
    double z;//!< Координаты z, км.
    double vx;//!< Составляющие скорости V<sub>x</sub>, км/с.
    double vy;//!< Составляющие скорости V<sub>y</sub>, км/с.
    double vz;//!< Составляющие скорости V<sub>z</sub>, км/с.
    //double t_epoch;//!< эпоха юлианская().
    QDateTime t_epoch;//!< Дата и время начальных данных.
};

//! \brief Структура начальных условий КА TLE данные.
struct ASDScStleInitData
{
    QString satName; //!< Название спутника.
    QString firstString; //!< Первая строка орбитальных элементов.
    QString secondString; //!< Вторая строка орбитальных элементов.
};
//! \brief Структура геодезические координаты объекта на Земле.
struct ASDGeoPointEarth
{
    double longitude; //!< Долгота, рад.
    double latitude; //!< Геодезическая широта, рад.
    double height; //!< Высота, км;

};

//! \brief Структура координаты объекта на Земле.
struct ASDPointEarth
{
    double longitude; //!< Долгота, рад.
    double latitude; //!< Широта, рад.
    double height; //!< Высота, км.
};

//! \brief Структура координат объекта на заданный момент времени
struct ASDPosObj
{
    double x; //!< Координата x.
    double y; //!< Координата y.
    double z; //!< Координата z.
    double Vx;//!< Координата Vx.
    double Vy;//!< Координата Vy.
    double Vz;//!< Координата Vz.
    int time; //!< Относительное время.
    QDateTime time_real; //!< Дата и время.
};

//! \brief Структура координаты объекта в пространтсве.
struct ASDCoordObj
{
    double x; //!< Координата x.
    double y; //!< Координата y.
    double z; //!< Координата z.
    int time; //!< Относительное время.

};

//!  \brief Структура начальные условия КА TLE телеграммы
struct ASDScTleInitData
{
    unsigned int epochYear; //!< Год.
    double epochDay; //!< Эпоха (день года и дробная часть дня).
    double bstar; //!< Коэффициент торможения SGP4-типа (bstar drag term), размерность - (радиус земли)<sup>-1</sup>.
    double inclination; //!< Наклонение, радиан (от 0 до PI).
    double raan; //!< Прямое восхождение восходящего узла, радиан.
    double eccentr; //!< Эксцентриситет.
    double perigee; //!< Аргумент перигея, радиан.
    double meanAnomaly; //!< Средняя аномалия, радиан.
    double meanMotion; //!< Среднее движение, радиан/мин.
    unsigned long revolNumber; //!< Номер витка в эпоху [оборотов].
};

//! \brief Структура параметров для установки данных возмущающих сил в модели с ДУ.
struct ASDFmcData
{
    bool geoEarth; //!< Учет возмущения гравитационного поля земли.
    bool geoSun;//!< Учет возмущения гравитационного поля Солнца.
    bool geoMoon;//!< Учет возмущения гравитационного поля Луны.
    bool atmDrag;//!< Учет возмущения атмосферы земли.
    bool solarPressure;//!< Учет светового давления.
    int grvModel;//!< 0-для центрального гравитационного поля Земли,
    //! 1-для гравитационного поля Земли c учетом полярного сжатия.


    ASDFmcData()
    {
        geoEarth = true;
        geoSun = geoMoon = false;
        atmDrag = false;
        solarPressure = false;
        grvModel = 0;

    }
};

//! \brief Структура параметров бортовой специальной аппаратуры.
struct ASDLobe
{
    int type;
    double angle_azimuth;
    double angle_elev;
    double deltaV;
    double deltaH;
    double gain;
    ASDLobe()
    {
        type=1;
        gain=1.;
    }
};
struct ASDBsePar
{
    BseType type;//!< Тип аппаратуры.
    QString name;//!< Название.
    // установочные данные
    //  double gamma; //!< Минимальный угол полураствора (для конуса обзора).
    double alfaMounting; //!< Установочный угол в горизонтальной плоскости, градусов.
    double etaMounting; //!< Установочный угол в плоскости отвеса, градусов.
    double betaMounting; //!< Установочный угол в поворота плоскости , градусов.
    double deltaTau; //!< Смещение аппаратуры по оси Tay орбитальной системы координат, метров.
    double deltaN;//!< Смещение аппаратуры по оси N орбитальной системы координат, метров.
    double deltaB;//!< Смещение аппаратуры по оси B орбитальной системы координат, метров.
    // double deltaV;//!< угол раствора по вертикали (для параллепипеда обзора).
    //  double deltaH;//!< угол раствора по горизонтали (для параллепипеда обзора).
    double deltaL;//!< ширина полосы захвата,км (для систем обзора).
    //  double pitch; //!< тангаж ( в плоскости КА)
    //  double yaw;   //!< рыскание (перпендикулярно плоскости КА)
    //  double roll;  //!< крен (вращение оптической оси КА, направленной на Землю)


    // 25.06.2018 дополнительные параметры
    double deltaVr;//!< скорость перенацеливания,с (для систем обзора).
    double skor;//!< Точность позиционирования, м(мин. разрешение (для систем обзора))
    double Pr;//!< Производительность, млн кв км/сут
    double fmem;//!<Емкость ПЗУ, Гбайт
    // дополнительные параметры для оптико-электронных средств
    // double resonving_Power;//!< разрешающая способность, лин/мм.
    // double length_line;//!< длина фотоприемной линейки, м.
    // double focus;//!< фокусное расстояние, м.
    // double countN_PZS;//!< количество пар элементов ПЗС, шт.
    // дополнительные параметры для PЛ средств
    // add

    union{
        double pitch;
        double az;
    };
    union{
        double el;
        double yaw;
    };
    double gamma;
    double roll;
    union{
        double deltaH;
        double azWidth;
    };
    union{
        double deltaV;
        double elWidth;
    };
    double power;
    double gain;
    double power_min;
    double frequency;
    double delta_frequency;
    int type_signal;
    double Tc;
    QVector<ASDFrequency>range_frequency;
    ModulationTypes modType;
    AntennaTypes antType;
    double Q;
    PolarizationCoherency typePol;
    double lwd;
    double RR;
    double TAU;

    ASDBsePar()
    {
        gamma = 40*DEG_TO_RAD;
        alfaMounting = 0;
        etaMounting = 0;
        betaMounting=0.;
        deltaTau = 0;
        deltaN = 0;
        deltaB = 0;
        deltaL=20.;
        deltaVr=300.;
        skor=30.;
        Pr=1.;
        fmem=160.;
        deltaV = 0;
        deltaH =0;
        pitch = 0;
        yaw = 0;
        roll = 0;

        power=100.;
        power_min=1e-14;
        frequency=8*1e9;
        delta_frequency=1e6;
        type_signal=0;
        Tc=1e-4;
        gain=10.;
        range_frequency.append(C);
        range_frequency.append(X);
        range_frequency.append(K);
        modType=mod_Otehr;
        antType=ant_Other;
        lwd=0;
        RR=0;
        TAU=0;
        typePol=polar_1;
        Q=13;
    }

    QVector<ASDLobe>side_lobe;

    // дополнительные параметры
    QVector<QString> name_param;//!< Название параметра.
    QVector<double> param_value;//!< Значение параметра.
    //
};

//! \brief Структура паараметров бортовой аппаратуры КА-инспектора.
struct ASDBseInspect
{
    int num_modul; //!< Количество инспектирующих модулей
    double velosity; //!< Запас характерестической скорости
    ASDBseInspect()
    {
        num_modul = 0;
        velosity = 0;
    }
};

//! \brief Структура параметров орбитального объекта.
struct ASDOrbitalObjectPar
{
    BseType type;//!< Тип системы.
    QString nameSys;//!< Название системы.
    QString nameVeh; //!< Название средства
    int idVeh; //!< Уникальный идентификатор средства

    InitDataType type_dat;//!< Тип начальных условий.
    ASDScKeplerInitData kep;//!< Начальный вектор положения.
    ASDScEciInitData ags;//!< Начальный вектор положения.
    ASDScStleInitData stle;//!< Начальные условия КА TLE данные.
    ASDFmcData forcedan; //!< Установка учета возмущающих сил.
    QVector <ASDBsePar> bsa;//!< Параметры бортовой специальной аппаратуры.
    int type_kis;//!<Тип бортовой аппаратуры по взаимодействию с НАКУ (1 или 2)

    ASDBseInspect bse_inspect; //!< Бортовая аппаратура КА-инспектора.

};

/*!
 * \brief Структура содержит параметры баллистического объекта.
 */
struct ASDBallisticVichleParam
{
    QString name; //!< Название баллистического объекта.
    QDateTime dateTimeStart; //!< Дата и время старта.
    int typeTrassa; //!< Тип траектории 0 - отимальная, 1 - настильная, 2 - навесная.
    double longth; //!< Долгота старта.
    double lat; //!< Широта старта.
    double longthEnd; //!< Долгота точки падения.
    double latEnd; //!< Широта точки падения.
    double launchAzimuth; //!< Азимут запуска
    int quantityStage; //!< Число ступеней в РН
    double range;  //!< Дальность полета РН
    double rangeMax; //!< Максимальная дальность полета определяемая ТТХ
    ASDAutPar autPar;
    ASDMotionProgramPar motionProgramPar;
};
/*!
 * \brief Структура содержит параметры противобаллистического объекта.
 */
struct ASDAntiBallisticVichleParam
{
    QString name; //!< Название баллистического объекта.
    QDateTime dateTimeStart; //!< Дата и время старта.
    double longth; //!< Долгота старта.
    double lat; //!< Широта старта.
    double MinDist; //!< Минимальная дальность.
    double MaxDist; //!< Максимальная дальность.
    double Vaut; //!< скорость в конце АУТ.
    double TettaAut; //!< угол наклона вектора скорости.
    double HAut; //!< высота окончания активного участка.
    double TimeAut; //!< продолжительность активного участка.
    double RangeAut; //!< угловая дальность активного участка.
    double timePreparation; //!< время подготовки ракеты.
    ASDAntiBallisticVichleParam ()
    {
        timePreparation = 0;
    }

};
/*!
 * \brief координаты объекта
 */
struct points
{

    double lat;//!< широта  в град
    double lon;//!< долгота  в град
    double h;//! <высота в метрах
    points()
    {
        lat = 0.;
        lon = 0.;
        h = 0.;
    }
};

struct SRegExplor //! данные о разведке района
{
    int weight; //! сколько раз разведанн район
    QVector <int> vecKA; //! вектор КА, участвующих в разведке района
    SRegExplor()
    {
        weight = 0;
    }
};

struct mapDatViz
{
    QVector<double> pos;
    //QDateTime current;
    int n_obj;
    QString OrbobjName;
    QVector<bool> eartzone;
    QVector<QString> eartpointName;
    QVector<points> orbToeart;
};

//Орбитальное средство (FIXME нужен класс?)
typedef struct
{
    QVector<double> agesc;
    //	ASDMobileZone zone;
    QVector <ASDBsePar> bsa;
    int ID;
    QString name;
} OrbitalVehicle;

typedef struct
{
    QVector<double> posW;
    QVector<double> posV;
    int id;
    QString name;

} Orbsel;

struct SPoint
{
    int numberKA;
    int numberVeh;
    int numberVehRko;
    QDateTime time_Rko;
    QDateTime time_Veh;

};

/*!
 * \brief данные наземного района наблюдения
 */

struct Paramregion
{
    QString name;
    double minlong;
    double maxlong;
    double minlat;
    double maxlat;
    double weight;
    int idRegion;
    ASDBsePar bsa;
    Paramregion()
    {
        name="";
        minlong=0.;
        maxlong=360.;
        minlat=-90.;
        maxlat=90.;
        weight=100.;
    }
};

/*!
 * \brief данные наземного района наблюдения с ПР
 */

struct ParamregionO
{
    QString name;
    double mlat;// Широта центра, в градусах
    double mlong;//Долгота центра, в градусах
    double dllat;// длина по широте, км
    double dllon;// длина по долготе, км
    int countR; // количество объектов
    int type;// тип объекта
    double ldir;// требуемое разрешение, м
    int idRegion;

    ParamregionO()
    {
        name="";
        mlat=0.;// Широта центра, в градусах
        mlong=0.;//Долгота центра, в градусах
        dllat=100.;// длина по широте, км
        dllon=150.;// длина по долготе, км
        countR=0; // количество объектов
        type=0;// тип объекта
        ldir=10.;// требуемое разрешение, м
        idRegion=0;
    }
};

//struct Paramregion//!< данные наземного района наблюдения
//{
//	QString name;//!< название  района
//	double minlong;//!< минимальная долгота, град
//	double maxlong;//!< максимальная долгота, град
//	double minlat;//!< минимальная широта, град
//	double maxlat;//!< максимальная широта, град
//	Paramregion()
//	{
//		name = "";
//		minlong = 0.;
//		maxlong = 360.;
//		minlat = -90.;
//		maxlat = 90.;
//	}
//};

//! Название элементов структуры для форм (ParamBSKOpticT)
//QStringList SParamBSKOpticT(QStringList()<< QString::fromUtf8("площадь элементов, м*м")<< QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м")   << QString::fromUtf8("относ. отверстие объектива")  << QString::fromUtf8("время экспозиции, с")<< QString::fromUtf8("квантовая эффективность")<< QString::fromUtf8("световая экспозиция")<< QString::fromUtf8(" к-т пропускаяния OC"));


/*!
 * \brief Исходные данные  Tелевизионной аппаратуры ОЭС
 */
struct ParamBSKOpticT//!< данные  Tелевизионной аппаратуры ОЭС
{
    float Sel;//! площадь элементов фотоприемника, м*м
    float l;//! спектральный диапазон, мкм
    float F;//! фокусное расстояние, м
    float teta;//! относительное отверстие объектива,
    float te;//! время экспозиции, с
    float mu;//! квантовая эффективность фотоприемника
    float Ht;//! световая экспозиция, при которой отношение сигнал/шум =1, лк*с
    float tau0;//! к-т пропускаяния оптической системы
    float Vscan;//! скорость перенацеливания(град/сек)
    float Saer;//! суточная производительность, млн км*2
    float SKOpos;//! точность позиционирования,м
    ParamBSKOpticT()
    {
        Sel=10e-10;
        l=0.5;
        F=27;
        teta=0.091;// 1:11
        te=10e-4;
        mu=0.1;
        Ht=2e-5;
        tau0=0.8;
        Vscan=0.05;
        Saer=10;
        SKOpos=20.;
    }


};



/*!
 * \brief Исходные данные РЛС изображения
 */
//QStringList SParamBSKPLSF(QStringList() << QString::fromUtf8("диапазон PB, ГГц")<< QString::fromUtf8("мощность излучения, Вт")<< QString::fromUtf8("угол выноса ближней границы, град")<< QString::fromUtf8("угол выноса дальней границы, град")<< QString::fromUtf8("разрешение, м")<< QString::fromUtf8("порог. чувствительность, м<sup>2</sup>"));
struct ParamBSKRLRF//!< данные  Tелевизионной аппаратуры ОЭС
{
    float L;//! диапазон PB, ГГц
    float Power;//! мощность излучения, Вт
    float gamma_min;//! угол выноса ближней границы, град
    float gamma_max;//! угол выноса дальней границы, град
    float dl;//! разрешение, м
    float Sepr;//! порог. чувствительность, м<sup>2</sup>
    float Vscan;//! скорость перенацеливания(град/сек)
    float Saer;//! суточная производительность, млн км*2
    float SKOpos;//! точность позиционирования,м

    ParamBSKRLRF()
    {
        L=0.41;
        Power=10.5;
        gamma_min=27;
        gamma_max=78;// 1:11
        dl=1;
        Sepr=0.15;
        Vscan=0.05;
        Saer=10;
        SKOpos=20.;

    }


};

/*!
 * \brief Исходные данные PT обнаружения
 */

struct ParamBSKRTI//!< данные   аппаратуры РТ контроля
{
    float fmin;//! минимальная частота приема сигналов, МГц
    float fmax;//! максимальная частота приема сигналов, МГц
    float N0;//! чувствительность приемника,dB
    float gamma;//! ширина диаграммы направленности, град

    float Vscan;//! скорость перенацеливания(град/сек)
    float Saer;//! суточная производительность, млн км*2
    float SKOpos;//! СКО ошибки позиционирования,угл. мин
    ParamBSKRTI()
    {
        fmin=40.;
        fmax=6000.;
        N0=10.5;
        gamma=180.;
        Vscan=0.05;
        Saer=10;
        SKOpos=20.;

    }


};


//! Название элементов структуры для форм (ParamBSKOpticF)
//QStringList SParamBSKOpticF(QStringList() << QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м") << QString::fromUtf8("разреш. способность,лин/мм")<< QString::fromUtf8(" к-т пропускания OC"));

/*!
 * \brief Исходные данные  ФОТОаппаратуры ОЭС
 */
struct ParamBSKOpticF//!< данные  ФОТОаппаратуры ОЭС
{

    float l;//! спектральный диапазон, мкм
    float F;//! фокусное расстояние, м
    float R;//! разрешающая способность системы,лин/мм
    float tau0;//! к-т пропускаяния оптической системы
    ParamBSKOpticF()
    {
        R=60.;
        l=0.5;
        F=0.6;
        tau0=0.8;
    }


};
/*!
 * \brief данные  объекта наблюдения ОЭС
 */
struct ParamOBJOPTIC//!< данные наземного объекта наблюдения
{
    QString name;//!< название  объекта
    points point; //!< координаты  объекта
    // Габариты объекта
    double LengthObj;//!< длина, м
    double WidthObj;//!< ширина, м
    double HObj;//!< высота, м
    int type_Obj;//тип объекта(номер из списка)
    int type_M;// тип материала(номер из списка)
    // Спектральные к-ты яркости объекта
    float lumL04;//!< для диапазона 0.4 мкм
    float lumL05;//!< для диапазона 0.5 мкм
    float lumL06;//!< для диапазона 0.6 мкм
    float lumL07;//!< для диапазона 0.7 мкм
    float lumL08;//!< для диапазона 0.8 мкм
    float lumL09;//!< для диапазона 0.9 мкм
    // условия наблюдения (фон)
    int type_PP;//!< тип подстилающей поверхности(номер из списка)
    int type_VV;//!< видимость (номер из списка)
    int type_CL;//!< тип облачности(номер из списка)
    ParamOBJOPTIC()
    {
        LengthObj=0.;
        WidthObj=0.;
        LengthObj=0.;
        HObj=0.;
        lumL04=0.08;
        lumL05=0.08;
        lumL06=0.08;
        lumL07=0.08;
        lumL08=0.07;
        lumL09=0.07;
        type_PP=0;
        type_VV=0;
        type_CL=0;
        type_Obj=0;
        type_M=0;
    }



};

/*!
 * \brief условия  наблюдения объекта ОЭС
 */
struct ParamdirOptic//!< данные условий наблюдения объекта
{
    bool bsun;//!< учитывать освещенность Солнца
    bool bmeteo;//!< учитывать гидрометеорологические условия
    bool bOpticFon;//!< учитывать яркость фона
    bool bOpticAtmos;//!< рассчитывать к-т пропускания атмосферы
    bool bOpticAerozol;//!< рассчитывать к-т задымленности атмосферы
    bool bOpticSolarRad;//!< рассчитывать спектральную плотность освещенности Земли,
    //!<  обусловленное рассеиванием солнечной радиации задымленности атмосферы
    float Sm;//!< Метеорологическая дальность видимости, км
    float sunelev;//!<  угол Солнца, град
    float sunaz;//!< азимут Солнца, град
    // Спектральные к-ты яркости фона
    float flumL04;//!< для диапазона 0.4 мкм
    float flumL05;//!< для диапазона 0.5 мкм
    float flumL06;//!< для диапазона 0.6 мкм
    float flumL07;//!< для диапазона 0.7 мкм
    float flumL08;//!< для диапазона 0.8 мкм
    float flumL09;//!< для диапазона 0.9 мкм
    // направления наблюдения (объект- средсво наблюдения)
    double Dn;//!< дальность ,км
    double elev;//!< угол места(объект- средсво наблюдения), град
    double az;//!< азимут (объект- средсво наблюдения), град
    double elev_opticDir;//!< угол наклона оптической оси, град
    //double y;//!< угол поля зрения на объект наблюдения, град
    ParamdirOptic()
    {
        bsun = true;
        bmeteo = false;
        bOpticFon = false;
        bOpticSolarRad = false;
        bOpticAtmos = false;
        bOpticAerozol = false;
        Sm=50.;
        sunelev=0.;
        flumL04=0.03;
        flumL05=0.05;
        flumL06=0.1;
        flumL07=0.19;
        flumL08=0.5;
        flumL09=0.5;
        az=0.;
        elev=90.;
        Dn=600.;
        sunaz=0.;
        elev_opticDir=90.;

    }
};

struct ParamRTR//!< данные наземного радиосредств наблюдения
{
    QString name;//!< название  средства
    double P;//!< мощность передатчика, ватт
    double F;//!< частота излучения, МГц
    double dF;//!< ширина спектра излучения, kГц
    double dA;//!< ширина диаграммы направленности, град
    int Type_S;//!< тип сигнала (0-непрерывный, 1 импульсный)
    double T;//!< длительность импульса,нс(если импульсный сигнал)
};

/*!
 * \brief данные наземного района  c объектом наблюдения ОЭС
 */
struct ParamregionOBJ//!< данные наземного района наблюдения
{
    QString name;//!< название  района
    double minlong;//!< минимальная долгота, град
    double maxlong;//!< максимальная долгота, град
    double minlat;//!< минимальная широта, град
    double maxlat;//!< максимальная широта, град
    QVector<ParamOBJOPTIC> vecOBJ;
    QVector<ParamRTR> vecPM;
    ParamregionOBJ()
    {
        name = "";
        minlong = 0.;
        maxlong = 360.;
        minlat = -90.;
        maxlat = 90.;
    }
};


/*!
 * \brief координаты объекта
 */
struct facilitypoint
{
    QString name;
    double lat;//!< широта  в град
    double lon;//!< долгота  в град
    double h;//! <высота в метрах
    facilitypoint()
    {
        lat = 0.;
        lon = 0.;
        h = 0.;
        name = "";

    }
};

/*!
 * \brief данные наземного комплекса поражения
 */
struct ParamGrBaseInter//!< данные наземного комплекса поражения
{
    Paramregion region;//!< название и координаты района дислокации комплекса
    facilitypoint point;//!< название и координаты комплекса
    double minelev;//!< минимальный угол места, град
    double maxelev;//!< максимальный угол места, град
    double minaz;//!< минимальный азимут, град
    double maxaz;//!< максимальный азимут, град
    double maxdist;//!< максимальная дальность, км
    double mindist;//!< минимальная дальность, км
    double tauselect;//!< время принятия решения, сек
    int type;//!< тип комплекса  !!!!!!!
    ParamGrBaseInter()
    {
        minelev = 15.;
        maxelev = 85.;
        minaz = 0.;
        maxaz = 90.;
        maxdist = 1500.;
        mindist = 0.;
        tauselect=41.;
        type=0;
    }
};

/*!
 * \brief данные БПЛА
 */
struct ParamGrBPLA//!< данные БПЛА
{

    facilitypoint point;//!< название и координаты БПЛА
    double V;//!< скорость, км/ч
    double maxH;//!< максимальная высота, км
    double maxdist;//!< максимальная дальность, км
    double maxTau;//!< максимальное время продолжительности полета, ч
    double taustart;//!< время подготовки, сек
    int type;//!< тип комплекса  !!!!!!!
    double EPR;//! ЭПР,м2
     ASDBsePar bsas;
    ParamGrBPLA()
    {
        V = 150.;
        maxH = 4.;
        maxTau = 24.;
        taustart = 90.;
        maxdist = 1500.;
              type=0;
    }
};

/*!
 * \brief данные ЗРК
 */
struct ParamZRV//!< данные ЗРК
{

    facilitypoint point;//!< название и координаты ЗРК
    QString name;
    double maxH;//!< максимальная высота, км
    double maxdist;//!< максимальная дальность, км
    double taus;//!< время подготовки, сек
    double fr;//!< частота, ГГЦ
    int type;//!< тип комплекса  !!!!!!!
    double EPR;//! ЭПР,м2

    ParamZRV()
    {

        maxH = 4.;

        taus = 90.;
        maxdist = 20.;
           type=0;
           EPR=0.1;
    }
};


/*!
 * \brief данные наземного комплекса управления
 */
struct ParamGrContrCentr//!< данные наземного комплекса управления
{
    Paramregion region;//!< название и координаты района дислокации комплекса
    facilitypoint point;//!< название и координаты комплекса
    double minelev;//!< минимальный угол места, град
    double speedsend;//!< максимальная скорость передачи, Гб/с
    double speedrec;//!< максимальная скорость приема,  Гб/с
    int CubK;//!< количество комплексов "КУБ-контур"
    int MA9;//!< количество комплексов "МА9"
    int TamB;//!< количество комплексов "Тамань-БАЗА"
    int MPRS;//!< количество комплексов "МПРС"
    int fazan;//!< количество комплексов "ФАЗАН"
    int tauMinZPV;//!< миниммальное время нахождения в зоне РВ, сек
    ParamGrContrCentr()
    {
        minelev = 7.;
        speedsend = 0.;
        speedrec = 0.;
        CubK = 0.;
        MA9 = 0.;
        TamB = 0.;
        MPRS=0.;
        fazan=0.;
        tauMinZPV=60;

    }

};

/*!
 * \brief данные наземного пункта приема(ППИ)
 */
struct ParamGrContrRec//!< данные наземного пункта приема(ППИ)
{
    Paramregion region;//!< название и координаты района дислокации комплекса
    facilitypoint point;//!< название и координаты комплекса
    double minelev;//!< минимальный угол места, град
    double speedsend;//!< максимальная скорость передачи, Гб/с
    double speedrec;//!< максимальная скорость приема,  Гб/с
    int tipe1;//!< количество комплексов OEP
    int tipe2;//!< количество комплексов PP
    int tipe3;//!< количество комплексов PLS
    int tauMinZPV;//!< миниммальное время нахождения в зоне РВ, сек
    ParamGrContrRec()
    {
        minelev = 7.;
        speedsend = 0.;
        speedrec = 0.;
        tipe1 = 0.;
        tipe2 = 0.;
        tipe3 = 0.;
        tauMinZPV=60;

    }

};
/*!
 * \brief Структура, содержащая параметры инспекции КА
 */

struct ASDParInspection
{
    ASDScKeplerInitData par_kep;
    double time_wait; //!< Время ожидания на опорной орбите
    double time_fly; //!< Время полета по переходной орбите
    double time_full_fly; //!< Время полного перелета
    double dV; //!< Величина управляющего импульса скорости
    bool resolve; //!< Является ли данная переменная решением ( по умолчанию - является (true))
    ASDParInspection()
    {
        resolve = true;
    }
};

/*!
 * \brief данные зоны обзора
 */


//! \brief Структура для сферических координат
struct ASDCoordSphere
{
    double azimuth; //!< Азимут, рад.
    double elevation; //!< Угол места, рад.
    double distance; //!< Расстояние, км.
};

struct ParamZone//
{
    ASDCoordSphere pointKA;//!<направление главной оси зоны обзора (азимут и угол места из источника, дальность)
    facilitypoint pointT;//!< название и координаты (широта, долгота, высота над поверхностью Земли) источника
    double minelev;//!< минимальный угол места, град
    double maxelev;//!< максимальный угол места, град
    double minaz;//!< минимальный азимут, град
    double maxaz;//!< максимальный азимут, град
    double maxdist;//!< максимальная дальность, км
    double mindist;//!< минимальная дальность, км
    QColor color;//!< цвет зоны действия
    ParamZone()
    {
        minelev = 0.;
        maxelev = 360.;
        minaz = 87.;
        maxaz = 89.;
        maxdist = 45000.;
        mindist = 0.;
        color = QColor(255,0,0,255);
    }
};

/*!
 * \brief Структура зоны радиовидимости
 */
struct ASDZoneVisible
{
    QDateTime timeBegin; //!< время входа в зону
    QDateTime timeEnd; //!< время выхода из зоны
    QDateTime timeBeginEngagement; //!< начало времени задействования
    QDateTime timeEndEngagement; //!< окончание времени задействования
    QVector <int> listTimeVizib; //!< время видимости от начала моделирования в секундах с шагом 5 сек
    QVector <int> listTimeEngagement; //!< время задействования от начала моделирования в секундах с шагом 5 сек
    int idKA; //!< номер КА
    int loop; //!< номер витка из всех
    int idOkik; //!< номер ОКИК
    int idVeh; //!< номер средства на этом Окик
    int idOperation; //!< номер операции
    int typeKisVeh; //!< тип КИС средства
    int typeKisKa; //!< тип КИС КА
    int loop_visible;//!< номер видимого витка расчитывается для данной операции 99-предпоследний, 100-последний
    int loop_last; //!< задается по умолчанию 0, если виток последний то 100, если предпоследний - то 99 и так далее
    int time_duration; //!< длительность операции в секундах
    int number; //!< порядковый номер зоны
    QString nameOkik; //!< название ОКИК
    QString nameVeh; //!< название средства
    QString nameOperation; //!< название операции
    QString nameKA; //!< название КА

    int dopAtribute; //!< дополнительный атрибут
    //! dop
    //!
    //!
    QVector <double> listVizibfac; //!< ценность информацци для объектов
    QVector <int> listposKA; //!< подспут. точки( номер квадрата)
    ASDZoneVisible()
    {
        loop_last = 0;
    }

};
/*!
 * \brief Перечисляемый тип данных, задающий типы операций, проводимых средствами НКУ
 */
enum NameOperation
{
    KPI = 0, //!< закладка командно-программной информации
    TMI = 1, //!<
    ITNP = 2 //!< измерение текущих навигационных параметров
};

/*!
 * \brief Структура операции управления
 */
struct OperationGCC
{
    NameOperation name; //!< название операции
    QString name_string; //!< название операции
    int time_duration; //!< длительность операции в секундах
    int idOperation; //!< номер операции
public:


    void defDuration()
    {
        if(name == KPI)
        {
            idOperation = 0;
            time_duration = 330;
            name_string = QString::fromUtf8("КПИ");
        }
        if(name == TMI)
        {
            idOperation = 1;
            time_duration = 200;
            name_string = QString::fromUtf8("ТМИ");
        }
        if(name == ITNP)
        {
            idOperation = 2;
            time_duration = 105;
            name_string = QString::fromUtf8("ИТНП");
        }
    }

};
/*!
 * \brief Имена типов средств ОКИК
 */
enum NameVehGCC
{
    KK = 0,
    MA9 = 1,
    TamanBasa = 2,
    KAMA = 3
};

/*!
 * \brief Структура средства наземного комплекса управления (ОКИК)
 */
class VehGrContrCentr
{



public:
    VehGrContrCentr()
    {

    }
    void defListOperation()
    {
        listOperation.clear();
        OperationGCC kpi,tmi,itnp;
        kpi.name = KPI;
        tmi.name = TMI;
        itnp.name = ITNP;

        kpi.defDuration();
        tmi.defDuration();
        itnp.defDuration();
        if(name == KK)
        {
            listOperation.append(kpi);
            typeVeh = 1;
            timePreparation = 900;
            name_veh = QString::fromUtf8("КК");

        }
        if(name == MA9)
        {
            listOperation.append(tmi);
            typeVeh = 1;
            timePreparation = 900;
            name_veh = QString::fromUtf8("МА9");
        }
        if(name == TamanBasa)
        {
            listOperation.append(kpi);
            listOperation.append(tmi);
            listOperation.append(itnp);
            typeVeh = 2;
            timePreparation = 900;
            name_veh = QString::fromUtf8("ТБ");
        }
        if(name == KAMA)
        {
            listOperation.append(itnp);
            typeVeh = 1;
            timePreparation = 900;
            name_veh = QString::fromUtf8("KAMA");
        }
    }

    VehGrContrCentr& setenable(const NameVehGCC &name_new)
    {
        name = name_new;

        defListOperation();
        return (*this);
    }

    NameVehGCC name; //!< название средства
    QVector <OperationGCC> listOperation; //!< выполняемых им список операций
    int typeVeh; //!< тип средства
    int idVeh; //!< номер средства
    int timePreparation; //!< время подготовки (в сек)
    QString name_veh; //!< название средства

};

/*!
 * \brief Структура, содержащая описание технологии проведения операции управления КА
 */
struct ASDTechOperation
{
    NameOperation nameOperation; //!< название операции
    QString name; //!< название операции
    int number_vizible_loop; //!< номера витков на одном из которых можно произвести операция
    int time_period; //!<требуемая периодичность выполнения операции в секундах
    ASDTechOperation()
    {
        time_period = 0;
        number_vizible_loop = -100;
    }
};

/*!
 * \brief Технология управления КА считываемая с базы данных
 */
struct ASDTechControl
{
    QString nameKA; //!< название КА
    int idKA; //!< идентификатор КА
    QVector <ASDTechOperation> technology; //!< технология работы с КА
};
/*!
 * \brief Структура, содержащая описание операции управления
 */

struct ASDOperationControl
{
    QString nameKA; //!< название КА
    int idKA; //!< идентификатор КА
    int idOperation;
    NameOperation nameOperation; //!< название операции
    int typeKis; //!< тип бортовой аппаратуры
    QString name_operation; //!< название операции
    int number_vizible_loop; //!< номера витков на одном из которых можно произвести операцию
    int number; //!< номер операции в общем списке
};

/*!
 * \brief Структура зон многкратного обзора
 */
struct ASDCollectiveZoneVisible
{
    QVector<ASDZoneVisible> list_zone; //!< список зон учавcтвующих в зоне многократного обзора
    QDateTime timeBeginEngagement; //!< начало времени задействования
    QDateTime timeEndEngagement; //!< окончание времени задействования
    QDateTime time_begin; //!< время начала многократного обзора
    QDateTime time_end; //!< время окончания многократного обзора
    QVector <int> listTimeVizib; //!< время видимости от начала моделирования в секундах с шагом 5 сек
    QVector <int> listTimeEngagement; //!< время задействования от начала моделирования в секундах с шагом 5 сек
    int loop_visible;//!< 1-первый, 2-второй, 3-третий, 9-предпоследний, 10-последний или 0-другой виток из видимых
    int loop; //!< номер витка
    int idKA; //!< номер КА

};

//!< Наземное средство
//struct SGroundVeh
//{
//    QString name; //!< название наземного средства
//    double latitude; //!< широта, рад
//    double longitude; //!< долгота, рад
//    double height; //!< высота, км
//    SGroundVeh()
//    {
//        latitude = 0;
//        longitude = 0;
//        height = 0;
//    }
//};
struct SGroundVeh
{
    QString name;
    int id;
    double latitude;
    double longitude;
    double height;
    int idRegion;
    ASDBsePar bsa;
    SGroundVeh()
    {
        latitude=0;
        longitude=0;
        height=0;
    }
};


//! \brief Перечисление содержит типы объектов 3D
enum TypeObject
{
    point3d,//!<точка
    line3d,//!<линия
    triangle3d,//!<треугольник
    poligon3d,//!<полигон
    sphere3d,//!<сфера
    partOfSphere3d,//!<сегмент сферы
    area3d,//!<четырехугольник на поверхности сферы
    quads3d,//!<четырехугольник на поверхности сферы
    text3d
};

/*!
* \brief Структура данных, характеризующих отображаемый объект в 3D
*/

struct object3d
{
    TypeObject m_TypeObject;//!<тип объекта
    QVector <float> m_coord;//!<вектор координат вершин объекта
    QVector <float> m_color;//!<вектор цветов вершин
    QVector <float> m_size;//!<вектор размеров вершин
    QVector <float> m_color_fill;//!<цвет заливки
    QVector <QString> icon;//!< иконка
    int m_pattern;//!<шаблон линий
    bool visible;//!<флаг отображения объекта
    bool earthObj;//!<флаг наземного стационарного объекта - вращение объекта вместе с Землей
    QVector <QString> name;//!<имя объекта


    //значения по-умолчанию
    //    object3d()
    //    {
    //        visible = true;
    //        m_pattern = 0xFFFF;
    //        m_color_fill.fill(255,4);
    //        m_size.fill(1,2);
    //        m_TypeObject = point3d;
    //    }
};




/*!
 * \brief  Cтруктура для формирования расписания входов и выходов в зону
 */
struct t_plan
{
    QDateTime begin_s;
    QDateTime end_s;
    int Nvit; //! < номер витка
    int type;//!< тип КА (1-низкоорбитальный, 2-ГЛОНАСС, 3-высокоорбитальный)
    int type_job;
    t_plan()
    {
        begin_s=QDateTime();
        end_s=QDateTime();
        Nvit=0;
        type=0;
        type_job=0;

    }
    ~t_plan()
    {
        memset(this,0,0);
    }

};

/*!
 * \brief  Cтруктура для формирования расписания входов и выходов в зону
 */
struct t_plan_P
{
    QDateTime time_beg;//!< дата и время входа в зону обнаружения
    QDateTime time_end;//!< дата и время выхода из зоны обнаружения
    double P0;//!< вероятность обнаружения
    double Pi;//!< вероятность идентификации
    int lobz;////!< 0-левая полоса; 1- правая полоса обзора
};
/*!
 * \brief  Cтруктура для формирования расписания входов и выходов в зону
 */
struct t_plan_h
{
    //     int type;//!< тип КА (1-низкоорбитальный, 2-ГЛОНАСС, 3-высокоорбитальный)
    //       double long_orb;//!< длина эллипса орбиты
    double begin_hs;//!< время(в часах от начало моделирования) входа в зону
    double end_hs;//!< время(в часах от начало моделирования) выхода из зоны
    int Nvit; //! < номер витка

};
/*!
 * \brief  Cтруктура для расчета итоговых показателей - глобальности и непрерывности управления
 */
struct t_plan_all
{
    t_plan plan;
    //       int type;//!< тип КА (1-низкоорбитальный, 2-ГЛОНАСС, 3-высокоорбитальный)
    double long_orb;//!< длина эллипса орбиты
    double long_way;//!< длина участка орбиты в зоне обзора средства
    //       double time_way;//!< время(в секундах) нахождения в зоне обзора средства


};
struct t_plan_Areas
{
    t_plan plan;
    double long_gamma;//!< угол крена
    double Areas;//!< площадь обзора района
    double time_way;//!< время(в секундах) нахождения в зоне обзора средства
    QVector<int> pointdata;//!< вектор элементарных площадок, попавших в зону обзора
};

/*!
 * \brief  Cтруктура для хранения непрерывности и глобальности управления
 */
struct t_visibility
{
    int KA;//!< идентификатор КА
    int type; //!< тип КА
    double nepr;//!< непрерывность
    double glob;//!< глобальность
};

/*!
 * \brief  Cтруктура для хранения протяженности орбиты в зоне обзора НКУ за один виток
 */
struct long_orb_vit
{
    int KA;//!< идентификатор КА
    int type; //!< тип КА
    double long_orb;//!< протяженность орбиты в зоне обзора НКУ за один виток
    int Nvit; //! < номер витка
};


struct RelativPos
{
    double distRel;
    double velRel;
    int time;
    QDateTime time_real;
};



struct ASDGBR
{
    QString name; //!< район дислокации
    facilitypoint point;//!< название и координаты комплекса
    Paramregion region; //!< название и координаты района дислокации комплекса
    double minelev;//!< минимальный угол места, рад
    double maxelev;//!< максимальный угол места, рад
    double minaz;//!< минимальный азимут, рад
    double maxaz;//!< максимальный азимут, рад
    double maxdist;//!< максимальная дальность, км
    double mindist;//!< минимальная дальность, км
    double tauselect;//!< время принятия решения, сек
    double esa;//!< ЭПР, м^2
    double sko_D; //! средняя квадратичная ошибка по дальности
    double sko_Azim; //! средняя квадратичная ошибка по азимуту
    double sko_Elev; //! средняя квадратичная ошибка по углу места
    QVector<ASDBsePar> equipment; //! параметры антенной системы
    int type; //1-РЛС, 3 - пункт ТМИ
    int id; //! уникальный номер
    ASDGBR():point(), name("              "), minelev(0.),
        maxelev(0.), minaz(0.), maxaz(0.), maxdist(10000000.), mindist(0.),
        tauselect(41.), type(1),sko_D(0.0001)
    {
    }
};


struct ASDService
{
    int idKa;
    int idKa_eq;
    int idVeh;
    int idVeh_eq;

    int idPoint;


    QString name_KA;
    QString name_KA_eq;
    QString name_Veh;
    QString name_Veh_eq;
    QString name_Point;

    double gainKA; //кнд КА по направлению средства
    double gainVeh; //кнд средства по напралению КА
    double power_input; //мощность на входе в приемник
    double probably; //вероятность обнаржуения сигнала
    double signal_noise; //сигнал-шум

};

struct ASDService2
{
    QString name_KA;
    QString name_KA_eq;
    QString name_Veh;
    QString name_Veh_eq;
    QString name_Region;
    QString name_KA2;

    double power_input; //мощность на входе в приемник
    QDateTime timeBegin; //начало интервала
    QDateTime timeEnd;//окончание интервала


};

struct ASDPurpose
{
    QString  id_sat;
    int norad;
    QDateTime dat_plan; //Дата формирования перечня на пред-варительное планирование
    double kon_prior; //Приоритет
    int id_typ_rcu; //1 - мониторинг; 2 - обслуживание
    QDateTime time_begin;
    QDateTime time_end;
};

typedef QMap<int, t_plan_Areas> mapTime_plan_Areas;
typedef QMap<int, t_plan> mapTime_plan;
typedef QMap<int, t_plan_h> mapTime_planh;
typedef QMap<int, t_plan_P> mapTime_planP;
typedef QMap<int, t_plan_all> mapTime_planall; //!< тип данных для увязки структуры <t_plan_all> с номером КА

template<typename T_vecStruct,typename typeID>
QVector<T_vecStruct>search_id(QVector<T_vecStruct>str,typeID T_vecStruct::*member,typeID id)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if(str[i].*member==id)
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2>
QVector<T_vecStruct>search_id(QVector<T_vecStruct>str,typeID1 T_vecStruct::*member1,typeID1 id1,typeID2 T_vecStruct::*member2,typeID2 id2)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1==id1)&&(str[i].*member2==id2))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3>
QVector<T_vecStruct>search_id(QVector<T_vecStruct>str,typeID1 T_vecStruct::*member1,typeID1 id1,typeID2 T_vecStruct::*member2,
                              typeID2 id2,typeID3 T_vecStruct::*member3,typeID3 id3)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1==id1)&&(str[i].*member2==id2)&&(str[i].*member3==id3))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3,typename typeID4>
QVector<T_vecStruct>search_id(QVector<T_vecStruct>str,typeID1 T_vecStruct::*member1,typeID1 id1,typeID2 T_vecStruct::*member2,
                              typeID2 id2,typeID3 T_vecStruct::*member3,typeID3 id3,typeID4 T_vecStruct::*member4,typeID4 id4)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1==id1)&&(str[i].*member2==id2)&&(str[i].*member3==id3)&&(str[i].*member4==id4))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3,typename typeID4,typename typeID5>
QVector<T_vecStruct>search_id(QVector<T_vecStruct>str,typeID1 T_vecStruct::*member1,typeID1 id1,typeID2 T_vecStruct::*member2,
                              typeID2 id2,typeID3 T_vecStruct::*member3,typeID3 id3,typeID4 T_vecStruct::*member4,typeID4 id4,
                              typeID5 T_vecStruct::*member5,typeID5 id5)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1==id1)&&(str[i].*member2==id2)&&(str[i].*member3==id3)&&(str[i].*member4==id4)&&(str[i].*member5==id5))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID>
QVector<T_vecStruct>remove_id(QVector<T_vecStruct>str,typeID T_vecStruct::*member,typeID id)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if(str[i].*member!=id)
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2>
QVector<T_vecStruct>remove_id(QVector<T_vecStruct>str,typeID1 T_vecStruct::*member1,typeID1 id1,
                              typeID2 T_vecStruct::*member2,typeID2 id2)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1!=id1)||(str[i].*member2!=id2))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3>
QVector<T_vecStruct>remove_id(QVector<T_vecStruct>str,
                              typeID1 T_vecStruct::*member1,typeID1 id1,
                              typeID2 T_vecStruct::*member2,typeID2 id2,
                              typeID3 T_vecStruct::*member3,typeID3 id3)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1!=id1)||(str[i].*member2!=id2)||(str[i].*member3!=id3))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3,typename typeID4>
QVector<T_vecStruct>remove_id(QVector<T_vecStruct>str,
                              typeID1 T_vecStruct::*member1,typeID1 id1,
                              typeID2 T_vecStruct::*member2,typeID2 id2,
                              typeID3 T_vecStruct::*member3,typeID3 id3,
                              typeID4 T_vecStruct::*member4,typeID4 id4)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1!=id1)||(str[i].*member2!=id2)||(str[i].*member3!=id3)||(str[i].*member4!=id4))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID1,typename typeID2,typename typeID3,typename typeID4,typename typeID5>
QVector<T_vecStruct>remove_id(QVector<T_vecStruct>str,
                              typeID1 T_vecStruct::*member1,typeID1 id1,
                              typeID2 T_vecStruct::*member2,typeID2 id2,
                              typeID3 T_vecStruct::*member3,typeID3 id3,
                              typeID4 T_vecStruct::*member4,typeID4 id4,
                              typeID5 T_vecStruct::*member5,typeID5 id5)
{
    QVector<T_vecStruct>str_new;
    for(int i=0;i<str.size();i++)
    {
        if((str[i].*member1!=id1)||(str[i].*member2!=id2)||(str[i].*member3!=id3)||(str[i].*member4!=id4)||(str[i].*member5!=id5))
            str_new.append(str[i]);
    }
    return str_new;
}
template<typename T_vecStruct,typename typeID>
int getNumber(QVector<T_vecStruct>str,typeID T_vecStruct::*member,typeID id)
{
    for(int i=0;i<str.size();i++)
    {
        if(str[i].*member==id)
            return i;
    }
    return-1;
}

// РУСЛАН !!!!!

//! \brief Структура координат баллистической ракеты на момент времени.
struct ASDInitCoord
{
    double x; //!< Координата x.
    double y; //!< Координата y.
    double z; //!< Координата z.
    double Vx;//!< Координата Vx.
    double Vy;//!< Координата Vy.
    double Vz;//!< Координата Vz.
    int number; //!< Позиция.
    QDateTime time; //!< Дата и время.
};

//! \brief Структура баллистической ракеты.
struct ASDRocket
{
    QString name; //!< Наименование БР
    QDateTime time_start; //!< Дата и время старта.
    QString name_start; //!< Наименование точки старта
    QString name_end; //!< Наименование точки падения
    double angle_cast; //!< Угол бросания, рад.
    double longitude_start; //!< Долгота точки старта, рад.
    double latitude_start; //!< Широта точки старта, рад.
    double longitude_end; //!< Долгота точки падения, рад.
    double latitude_end; //!< Широта точки падения, рад.
    QVector<ASDInitCoord> trassaRocket; //!< Массив координат баллистической ракеты с шагом секунда
    QMap<QDateTime, ASDInitCoord> map_time;
};





#endif // ASDTYPE_H
