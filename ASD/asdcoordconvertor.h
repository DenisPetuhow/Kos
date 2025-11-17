/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdcoordconvertor.h.\n
 ** Описание: Файл содержит класс конвертирования координат объектов.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 23.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:
 **
 **
 *****************************************************************************/
#ifndef ASDCOORDCONVERTOR_H
#define ASDCOORDCONVERTOR_H
#include <QVector>
//#include <QMessageBox>
#include <QString>
#include <QDateTime>

#include <math.h>

#include "ASD/asdtype.h"


using namespace std;

struct ASDCurPos;

/*!
 * \brief Класс содержит методы конвертирования систем координат (СК).
 *
 * Класс работает со следующими системами координат:
 *
 * <b>Абсолютная геоцентрическая экваториальная система координат (АГЭСК).</b>
 * Начало  СК расположено в центре Земли. Ось Ox направлена в точку весеннего равноденствия.
 * Ось Oz вдоль оси вращения Земли в сторону северного полюса. Ось Oy дополняет до правой тройки.
 *
 * <b>Гринвичская система координат.</b>
 * Начало  СК расположено в центре Земли. Ось Ox направлена на нулевой меридиан и расположена
 * в плоскости экватора. Ось Oz вдоль оси вращения Земли в сторону северного полюса. Ось Oy
 * дополняет до правой тройки.
 *
 * <b>Топоцентрическая система координат.</b>
 * Начало  СК расположено в точке на поверхности земли и задаётся широтой, долготой и возвышением
 * точки над поверхностью Земли. Ось Oz направлена на северный полюс. Ось Оy направлена в зенит по
 * местной нормали к поверхности эллипсоида. Ось Ox дополняет до правой тройки. В данной СК
 * учтено полярное сжатие Земли.
 *
 * <b>Орбитальная неподвижная система координат.</b>
 * Начало  СК расположено в центре Земли. Ось Ox направлена в перигей орбиты (по вектору Лапласа).
 * Ось Oz направлена по вектору площадей. Ось Oy дополняет до правой тройки.
 *
 * <b>Орбитальная подвижная система координат.</b>
 * Начало  СК расположено  в центре Земли. Ось Ox направлена на космический объект.
 * Ось Oz направлена по вектору площадей. Ось Oy дополняет до правой тройки.
 *
 * <b>Приборная (инструментальная) система координат. </b>
 * Начало СК расположено в центре масс объекта. Ось Ох (n) направлена на центр масс Земли.
 * Ось Oz (b) противоположно направлена  вектору площадей. Ось Оу (t) дополняет до правой тройки (по ходу движения КА).
 *
 * <b>Связанная система координат. </b>
 * Начало СК расположено в центре масс объекта. Ось Ox направлена по оптической (электрической) оси аппаратуры.
 * Ось Oy коллинеарна большей стороне прямоугольной диаграммы аппаратуры. Ось Oz дополняет до правой тройки. *
 *
 * <b>Кеплерова система координат.</b>
 * СК представляет из себя совокупность кеплеровских элементов орбиты:
 * наклонение, прямое восхождение восходящего узла, аргумент широты перигея,
 * фокальный параметр, эксцентриситет, аргумент широты КА.
 *
 * <b>Стартовая система координат.</b>
 * Начало координат в точке старта. Ось Oy ориентирована в противоположном направлении линии отвеса.
 * Ось Ox лежит в плоскости местного горизонта и ориентирована относительно плоскости меридиана точки старта
 * (направления на север) с помощью угла А, называемого азимутом прицеливания.
 *
 * <b>Измерительная система координат.</b>
 * Начало координат в центре масс объекта. Ось Ox совпадает с радиусом вектором. Ось Oy в плоскости перпендикулярной плоскости местного горизонта.
 * Ось Oz дополняет до правой тройки.
 *
 * <b>Радиолокационная система координат. (полярная)</b>
 * Начало СК в точке стояния станции. Дальность, угол места, азимут объекта.
 * Дальность - расстояние от центра СК до объекта.
 * Угол места - угол между плоскостью горизонта и вектором на объект.
 * Азимут - угол
 *
 * <b> Вторая экаториальная сферическая система координат. Esp_2</b>
 *  Начало - в центрк масс Земли. Alfa - прямое восхождение объекта, угловое расстрояние по небесному экватору от точки весеннего равноденствия до меридиана объекта.
 *  Небесный экватор - плоскость, проходящая через центр Земли и ТВР, перпендикулярная, прямой направленной на полярную звезду. Gamma - склонение,
 *  угловое расстояние по меридиану от небесного экватора до объекта, r - радиус-вектор объекта
 */
class ASDCoordConvertor
{
public:

	//! Конструктор по умолчанию.
	ASDCoordConvertor();
	//! Деструктор по умолчанию.
	virtual ~ASDCoordConvertor();

	/*!
	 * \brief Перевод координат из АГЭСК в Гринвичскую систему координат.
	 *
     * Начало  СК расположено  в центре Земли. Ось Ox направлена в точку весеннего
     * \param coord - координаты в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 *  v<sub>y</sub>, v<sub>z</sub>).
     * \param time - международная дата и время.
	 * \return Значения координат в Гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convAgescToGsc(QVector<double> coord,
            QDateTime time);

    /*!
     * \brief Перевод координат второго объекта из орбитальной подвижной системы координат
     * в  орбитальную неподвижную систему координат первого объекта.
     *
     * \param coordVehicle - координаты первого объекта в орбитальной неподвижной системе координат как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \param coordTarget - координаты второго объекта в орбитальной подвижной системе координат первого объекта как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \return Значения координат второго объекта в орбитальной неподвижной системе координат первого объекта как вектор
     * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     */
    static QVector<double> convOpscToOscRelative(QVector<double> coordVehicle,
            QVector<double> coordTarget);

    /*!
     * * \brief Перевод координат второго объекта из орбитальной неподвижной СК
     * в АГЭСК первого объекта
     *
     * \param coordVehicle - координаты в АГЭСК первого объекта как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \param coordTarget - координаты в орбитальной неподвижной СК второго объекта как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \return Значения координат второго объекта в орбитальной неподвижной системе координат
     * первого объекта как вектор значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     */
    static QVector<double> convOscToAgescRelative(QVector<double> coordVehicle,
            QVector<double> coordTarget);

    /*!
	 * \brief Перевод координат из АГЭСК в Топоцентрическую систему координат.
	 *
     * \param coord - координаты в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 * v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в Гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convAgescToTsc(QVector<double> coord,
            QDateTime time, double lat, double lon, double h);

	/*!
     * \brief Перевод координат из АГЭСК в орбитальную неподвижную систему координат.
	 *
	 * \param coord - координаты в АГЭСК как ветор значений (x, y, z, v<sub>x</sub>,
	 * v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат в орбитальной системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convAgescToOsc(QVector<double> coord);

	/*!
	 * * \brief Перевод координат второго объекта
	 * в орбитальную систему координат первого объекта
	 *
	 * \param coordVehicle - координаты в АГЭСК первого объекта как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param coordTarget - координаты в АГЭСК второго объекта как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат второго объекта в орбитальной неподвижной системе координат
	 * первого объекта как вектор значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convAgescToOscRelative(QVector<double> coordVehicle,
			QVector<double> coordTarget);

	/*!
	 * \brief Перевод координат из неподвижной орбитальной системы координат
	 *  в орбитальную подвижную систему координат.
	 *
	 * \param coord - координаты в неподвижной орбитальной системе координат первого объекта
	 * как вектор значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат в орбитальной подвижной системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convOscToOpsc(QVector<double> coord);

	/*!
	 * \brief Перевод координат второго объекта из орбитальной неподвижной системы координат
     * в  орбитальную подвижную систему координат первого объекта.
	 *
	 * \param coordVehicle - координаты первого объекта в орбитальной неподвижной системе координат как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param coordTarget - координаты второго объекта в орбитальной неподвижной системе координат первого объекта как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат второго объекта в орбитальной подвижной системе координат первого объекта как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convOscToOpscRelative(QVector<double> coordVehicle,
			QVector<double> coordTarget);


	/*!
	 * \brief Перевод координат второго объекта из АГЭСК координат
	 * в  орбитальную подвижную систему координа первого объекта.
	 *
	 * \param coordVehicle - координаты первого объекта в АГЭСК как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param coordTarget - координаты второго объекта в АГЭСК как вектор значений
	 * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат второго объекта в орбитальной подвижной системе координат первого объекта как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convAgescToOpscRelative(
			QVector<double> coordVehicle, QVector<double> coordTarget);

	/*!
     * \brief Перевод координат второго обьета из орбитальной подвижной системы координат
     * первого обьекта
     * \param coordVehicle - координаты первого объекта в АГЭСК как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \param coordTarget - координаты второго объекта в орбитальной подвижной СК как вектор значений
     * (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
     * \return координаты второго обьекта в АГЭСК
     */
    static QVector<double> convOpscToAgescRelative(
            QVector<double> coordVehicle, QVector<double> coordTarget);
	/*!
	 * \brief Перевод координат из АГЭСК в Кеплерову систем координат.
	 *
	 * Для круговой орбиты аргумент широты перигея считается равным нулю.
	 * Для экваториальный орбиты аргумент широты перигея и орбитального средтсва
	 * отсчитывается от оси Ox АГЭСК.
	 * Прямое восхождение восходящего узла для экваториальных орбит равно нулю.
     * \param coord - координаты в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 * v<sub>y</sub>, v<sub>z</sub>).
	 * \return Значения координат в Кеплеровой системе координат как вектор значений
	 * (наклонение, прямое восхождение восходящего узла, аргумент широты перигея,
     * фокальный параметр, эксцентриситет, аргумент широты КА).
	 */
    static QVector<double> convAgescToKsc(QVector<double> coord, double GR = K_EARTH);

	/*!
	 * \brief Перевод координат из Гринвичской системе координат в АГЭСК.
	 *
	 * \param coord - координаты в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 * v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \return Значения координат в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 *  v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convGscToAgesc(QVector<double> coord,
            QDateTime time);

	/*!
	 * \brief Перевод координат из Гринвичской системы координат в Топоцентрическую
	 * системы координат.
	 *
	 * \param coord - координаты в Гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в топоцентрической системе координат как
	 * вектор значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convGscToTsc(QVector<double> coord, double lat,
			double lon, double h);

	/*!
	 * \brief Перевод координат из гринвичской системы координат в орбитальную систему координат.
	 *
	 * \param coord - координаты в гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \return Значения координат в орбитальной системе координат как
	 * вектор значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convGscToOsc(QVector<double> coord,
            QDateTime time);

	/*!
	 * \brief Перевод координат из Гринвичской системы координат в Кеплерову систему координат.
	 *
	 * \param coord - координаты в гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \return Значения координат в Кеплеровой системе координат как вектор значений
	 * (наклонение, прямое восхождение восходящего узла, аргумент широты перигея,
     * фокальный параметр, эксцентриситет, аргумент широты КА).
	 */
	static QVector<double> convGscToKsc(QVector<double> coord,
            QDateTime time);

	/*!
	 * \brief Перевод координат из Топоцентрической системы координат в АГЭСК.
	 *
	 * \param coord - координаты в топоцентрической системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 * v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convTscToAgesc(QVector<double> coord,
            QDateTime time, double lat, double lon, double h);

	/*!
	 * \brief Перевод координат из Топоцентрической системы координат в Гринвичскую систему координат.
	 *
	 * \param coord - координаты в топоцентрической системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в Гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convTscToGsc(QVector<double> coord, double lat,
			double lon, double h);

    /*!
     * \brief Перевод координат из орбитальной подвижной системы координат в приборную СК.
     * \param radius - расстояние между центром орбитальной подвижной СК и приборной СК.
     * \param coordVehicle - координаты объекта в орбитальной подвижной СК.
     * \return координаты объекта в приборной СК.
     */
    static QVector<double> convOpscToIsc(double radius, QVector<double> coordTarget);

    /*!
     * \brief Перевод координат из приборной СК в орбитальную подвижную СК.
     * \param radius - расстояние между центром орбитальной подвижной СК и приборной СК.
     * \param coordVehicle - координаты объекта в приборной СК.
     * \return координаты объекта в орбитальной подвижной СК.
     */
    static QVector<double> convIscToOpsc(double radius, QVector<double> coordTarget);


    /*!
     * \brief Перевод координат из приборной СК в связанную СК
     * \param coordTarget - координаты объекта в приборной СК
     * \param angle - углы поворота между СК (тангаж, рыскание, крен)
     * \return координаты объекта в связанной СК
     */
    static QVector<double> convIscToConSc(QVector<double> coordTarget, ASDAngleMounting angle);

    /*!
     * \brief Перевод координат из связанной  СК в приборную СК
     * \param coordTarget - координаты объекта в связанной СК
     * \param angle - углы поворота между СК (тангаж, рыскание, крен)
     * \return координаты объекта в приборной СК
     */
    static QVector<double> convConScToIsc(QVector<double> coordTarget, ASDAngleMounting angle);

    /*!
     * \brief Перевод координат из Топоцентрической системе координат в Орбитальную системе координат.

	 * \param coord - координаты в топоцентрической системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в орбитальной системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convTscToOsc(QVector<double> coord,
            QDateTime time, double lat, double lon, double h);

	/*!
	 * \brief Перевод координат из Топоцентрической системы координат в Кеплерову систему координат.
	 *
	 * \param coord - координаты в топоцентрической системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 * \param timeMoscow - московская дата и время.
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в Кеплеровой системе координат как вектор значений
	 * (наклонение, прямое восхождение восходящего узла, аргумент широты перигея,
     * фокальный параметр, эксцентриситет, аргумент широты КА).
	 */
	static QVector<double> convTscToKsc(QVector<double> coord,
            QDateTime time, double lat, double lon, double h);

	/*!
	 * \brief Перевод координат из Кеплеровой системы координат в АГЭСК.
	 *
	 * \param coord - координаты в Кеплеровой системе координат как вектор
	 * значений (наклонение, прямое восхождение восходящего узла, аргумент широты
     * перигея, фокальный параметр, эксцентриситет, аргумент широты КА).
	 * \return Значения координат в АГЭСК как вектор значений (x, y, z, v<sub>x</sub>,
	 *  v<sub>y</sub>, v<sub>z</sub>).
	 */
    static QVector<double> convKscToAgesc(QVector<double> coord, double GR = K_EARTH);

	/*!
	 * \brief Перевод координат из Кеплеровой системы координат в Гринвичскую систему координат.
	 *
	 * \param coord - координаты в Кеплеровой системе координат как вектор
	 * значений (наклонение, прямое восхождение восходящего узла, аргумент широты
     * перигея, фокальный параметр, эксцентриситет, аргумент широты КА).
     * \param time - дата и время.
	 * \return Значения координат в Гринвичской системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
    static QVector<double> convKscToGsc(QVector<double> coord,
            QDateTime time);

	/*!
	 * \brief Перевод координат из Кеплеровой системы координат в Топоцентрическую систеу координат.
	 *
	 * \param coord - координаты в Кеплеровой системе координат как вектор
	 * значений (наклонение, прямое восхождение восходящего узла, аргумент широты
     * перигея, фокальный параметр, эксцентриситет, аргумент широты КА).
	 * \param timeMoscow - московская дата и время.
	 * \param lat - широта.
	 * \param lon - долгота.
	 * \param h - высота.
	 * \return Значения координат в топоцентрической системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convKscToTsc(QVector<double> coord,
			QDateTime timeMoscow, double lat, double lon, double h);

	/*!
	 * \brief Перевод координат из Кеплеровой системы координат в Орбитальную
	 * систему координат.
	 *
	 * \param coord - координаты в Кеплеровой системе координат как вектор
	 * значений (наклонение, прямое восхождение восходящего узла, аргумент широты
     * перигея, фокальный параметр, эксцентриситет, аргумент широты КА).
	 * \return Значения координат в орбитальной системе координат как вектор
	 * значений (x, y, z, v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>).
	 */
	static QVector<double> convKscToOsc(QVector<double> coord);

	/*!
	 * \brief Перевод координат из Стартовой системы координат в Гринвичскую
	 * систему координат.
	 *
	 * \param coord - координаты в Стартовой системе координат как вектор
	 * значений (v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>, x, y, z).
	 * \param lat - геоцентрическая широта.
	 * \param lon - долгота.
	 * \param A - азимут пуска.
	 * \return Значения координат в гринвичской системе координат как
	 * вектор значений (v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>, x, y, z).
	 */
	static QVector<double> convSscToGsc(QVector<double> coord, double lat,
			double lon, double A);

	/*!
	 * \brief Перевод координат из Гринвичской системы координат в Стартовую
	 * систему координат.
	 *
	 * \param coord - координаты в Гринвичской системе координат как вектор
	 * значений (v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>, x, y, z).
	 * \param lat - геоцентрическая широта.
	 * \param lon - долгота.
	 * \param A - азимут пуска.
	 * \return Значения координат в стартовой системе координат как
	 * вектор значений (v<sub>x</sub>, v<sub>y</sub>, v<sub>z</sub>, x, y, z).
	 */
	static QVector<double> convGscToSsc(QVector<double> coord, double lat,
			double lon, double A);

	/*!
     * \brief Вычисляет значение угла по синусу и косинусу от 0 до 2PI
	 *
	 * \param t_sin - значение синуса.
	 * \param t_cos - значение косинуса.
	 * \return -значение угла в рад.
	 */
	static double angle(double t_sin, double t_cos);

	/*!
	 * \brief Расчет зведного времени.
	 *
	 * \param timeMoscow - московская дата и время.
	 * \return Звезное время в радианах.
	 */
    static double compSiderealTime(const QDateTime time);

    /*!
     * \brief Расчет юлианской даты
     * \param time
     * \return дни + время
     */
    static double UD(const QDateTime time);

    /*!
     * \brief Расчет модифицированной юлианской даты
     * \param time
     * \return дни + время
     */
    static double MUD(const QDateTime time);

	/*!
	 * \brief расчет местного времени, без деления на временные зоны
	 * \param time - время на меридиане Гринвича
	 * \param lon - долгота объекта
	 * \return возращает местное время
	 */
	static QDateTime calcLocalTime(const QDateTime time, const double lon);

	/*!
	 * \brief Перевод параметров относительного движения в кеплеровские элементы орбиты
	 *
	 * \param pos - структура параметров текущего положения объекта относительно точки старта.
	 * \param time_start - время старта (московское)
	 * \param lat - широта точки старта
	 * \param lon - долгота точки старта
	 * \param A - азимут стрельбы
	 * \return Значения координат в Кеплеровой системе координат как вектор значений
	 * (наклонение, прямое восхождение восходящего узла, аргумент широты перигея,
     * фокальный параметр, эксцентриситет, аргумент широты КА).
	 */
	static QVector<double> convParamActSiteToAgesc(ASDCurPos pos,
			QDateTime time_start, double lat, double lon, double A);

	/*!
	 * \brief Перевод из географических координат обьекта в ГРСК
	 * \param lat - широта
	 * \param lon - долгота
     * \return - координаты обьекта  (x, y, z)
	 */
    static QVector<double> convGeoToGsc(double lat, double lon, double h, double r_planet = R_EARTH);

    /*!
     * \brief Перевод из Гринвича в Геодезическую систему координат
     * \param coord - координаты обьекта в Гринвиче (x, y, z)
     * \return - возращает вектор (широта, долгота, высота) [рад, рад, км]
     */
    static QVector<double> convGscToGeo(QVector <double> coord);  

    /*!
     * \brief Расчет угловой дальности
     * \param lat1  - широта первой точки
     * \param long1 - долгота первой точки
     * \param lat2  - широта второй точки
     * \param long2 - долгота второй точки
     * \return - угловая дальность
     */
    static double calcAngulDist(double lat1, double long1, double lat2, double long2);

    /*!
     * \brief Перевод из связанной системы координат в стартовую
     * \param angle - структура, содержащая углы тангажа, рыскания и крена
     * \param coord - координаты объекта в скоростной системе координат
     * \(центры систем координат считается что совпадают с ц.м. объекта)
     * \return - координаты объекта в стартовой системе координат
     */
    static QVector <double> convRscToSsc(ASDAngleMounting angle, QVector<double> coord);

    /*!
     * \brief Перевод из скоростной в стартовую систему координат (центры систем координат совпадают с ц.м. обьекта)
     * \param angle_vel - угол наклона вектора скорости к линии местного горизонта
     * \param angle_side - боковой угол
     * \param coord - координаты обьекта в стартовой системе координат
     * \return
     */
    static QVector <double> convVscToSsc(double angle_vel, double angle_side, QVector<double> coord);

    /*!
     * \brief Перевод из географической широты в геодезическую широту
     * \param latGeog - географическая широта, рад
     * \return - геодезическая широта, рад
     */
    static double convLatGeogToGeod(double latGeog);
    
    /*!
     * \brief Перевод из геодезической широты в географическую широту
     * \param latGeog - геодезическая широта, рад
     * \return - географическая широта, рад
     */
    static double convGeodToGeog(double latGeod);
    /*!
     * \brief Расчитывает азимут направления от первой точки ко второй (считает от 0 до M_PI)
     * \param latitude_1 - широта 1 точки (рад)
     * \param longitude_1 - долгота 1 точки (рад)
     * \param latitude_2 - широта 2 точки (рад)
     * \param longitude_2 -долгота 2 точки (рад)
     * \return азимут (рад)
     */
    static double calcAzimuth(double latitude_1, double longitude_1, double latitude_2, double longitude_2, double delta_time);


    /*!
     * \brief Вращение вокруг оси X.
     *
     * \param bet - угол вращения вокруг оси X, в радианах.
     * \return азимут (рад)
     */
    static QVector<double> rotateX(QVector<double> coord, const double& beta);

    /*!
     * \brief Вращение вокруг оси Y.
     *
     * \param beta - угол вращения вокруг оси Y, в радианах.
     * \return азимут (рад)
     */
    static QVector<double> rotateY(QVector<double> coord, const double& beta);

    /*!
     * \brief Вращение вокруг оси Z.
     *
     * \param beta - угол вращения вокруг оси Z, в радианах.
     * \return азимут (рад)
     */
    static QVector<double> rotateZ(QVector<double> coord, const double& beta);

    /*!
     * \brief Расчет азимута и угла места
     * \param coord_AGSK - координаты объекта в АГЭСК
     * \param latitude - широта станции
     * \param longitude - долгота станции
     * \param time - время
     * \return воозращает азимут, угол места в рад, дальность в км
     */
    static QVector<double> calcAzimuth_Elevetion(QVector<double> coord_AGSK, double latitude, double longitude, QDateTime time);

    /*!
     * \brief Перевод из стартовой СК в радиолокационную СК
     * \param coord - координаты объекта в ССК
     * \return дальность, азимут, угол места
     */
    static QVector<double> convSscToRlsc(QVector<double> coord_Ssc);

    static QVector<double> convIzmToGsc(QVector<double> coord, double latitude, double longitude, double height, double r, double azimuth, double elevetion);

//    static QVector<double> convAgescToEsp2(QVector<double> coord);

//    static QVector<double> convEsp2ToAgesc(QVector<double> coord_Ssc);

private:

};

#endif // ASDCOORDCONVERTOR_H
