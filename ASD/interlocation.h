/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdinterlocation.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#ifndef ASDINTERLOCATION_H
#define ASDINTERLOCATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#include <QVector>

#include "ASD/asdtype.h"
#include "ASD/asddatum.h"
#include "ASD/asdcoordconvertor.h"
#include "mathtools/asdmatrix3x3.h"
#include "mathtools/asdfunc.h"

/*!
 * \brief Класс, определяющий взаимное положение.
 *
 * Начало координат - в центре масс Земли.
 * Координаты задаются в метрах либо в Гринвичской СК (x, y, z), либо тройкой
 * (широта, долгота, высота), гринвичскому меридиану соответствует долгота 0 градусов.
 */
class ASDInterLocation
{
public:
	/*!
	 * \brief Конструктор по умолчанию. Создает недействительное положение.
	 */
	ASDInterLocation() :
		m_xyz(3, 0.0), m_currentDatum(WGS84)
	{
	}

	//! Конструктор копирования.
	ASDInterLocation(const ASDInterLocation& pos) :
		m_xyz(pos.getXYZ()), m_currentDatum(pos.getDatum())
	{
	}

	/*!
	 * \brief Конструктор с параметрами.
	 *
     * \param rx - компонент x, в километрах.
     * \param ry - компонент y, в километрах.
     * \param rz - компонент z, в километрах.
	 * \param c_dat - датум, используемый для отображения положения.
	 */
	ASDInterLocation(const double& rx, const double& ry, const double& rz,
			const CDatum& c_dat = WGS84);

	//! Деструктор по умолчанию.
	virtual ~ASDInterLocation()
	{
	}

	// Операторы
	/*!
	 * \brief Сумма двух положений.
	 *
	 * \param right - position to be added.
	 */
	ASDInterLocation operator+(ASDInterLocation right) const;

	/*!
	 * \brief Разница двух положений.
	 *
	 * \param right - position to do be substracted.
	 */
	ASDInterLocation operator-(ASDInterLocation right) const;

	/*!
	 * \brief Создает копию объекта положение.
	 *
	 * \param right - объект для копирования.
	 */
	ASDInterLocation& operator=(ASDInterLocation right);

	/*!
	 * \brief Сравнение положений.
	 *
	 * \param right - position to make the comparison.
	 * \return Returns 'true' if they are the same, and 'false' otherwise.
	 */
	bool operator==(ASDInterLocation right) const;

	/*!
	 * \brief Метод для изменения положения и ассоциированного с ним датума.
	 *
     * \param rx - компонент x, в километрах.
     * \param ry - компонент y, в километрах.
     * \param rz - компонент z, в километрах.
	 * \param n_dat - датум для нового положения.
	 */
	ASDInterLocation& setXYZ(const double& rx, const double& ry,
			const double& rz, const CDatum& n_dat = WGS84);

	/*!
	 * \brief Метод для изменения положения и ассоциированного с ним
	 * датума (координаты в виде вектора).
	 *
	 * \param vect - положение в 3-координатной системе, в метрах.
	 * \param n_dat - датум для нового положения.
	 */
	ASDInterLocation& setXYZ(const QVector<double>& vect, const CDatum& n_dat =
			WGS84);

	/*!
	 * \brief Метод для изменения положения с использованием широты, долготы и высоты.
	 *
     * \param lat - широта в радианах.
     * \param lon - долгота в радианах.
     * \param alt - высота в километрах.
	 * \param n_dat - используемый датум.
	 */
	ASDInterLocation& setLLA(const double& lat, const double& lon,
			const double& alt, const CDatum& n_dat);

	/*!
	 * \brief Метод для изменения положения с использованием широты, долготы
	 * и высоты (в виде вектора)
	 *
     * \param LLA - вектор, содержащий широту (рад), долготу (рад) и высоту (км).
	 * \param n_dat  - используемый датум.
	 */
	ASDInterLocation& setLLA(const QVector<double>& LLA, const CDatum& n_dat);

	/*!
	 * \brief Метод, задающий координату X.
	 *
	 * \param x - значение координаты X.
	 */
	ASDInterLocation& setX(const double& x);

	//! \brief Метод, возвращающий координату X.
	double getX() const
	{
		return m_xyz[0];
	}

	/*!
	 * \brief Метод, задающий координату Y.
	 *
	 * \param y - значение координаты Y.
	 */
	ASDInterLocation& setY(const double& y);

	//! \brief Метод, возвращающий координату Y.
	double getY() const
	{
		return m_xyz[1];
	}

	/*!
	 * \brief Метод, задающий координату Z.
	 *
	 * \param z - значение координаты Z.
	 */
	ASDInterLocation& setZ(const double& z);

	//! \brief Метод, возвращающий координату Z.
	double getZ() const
	{
		return m_xyz[2];
	}

	/*!
	 * \brief Метод для конвертации положения из текущего в новый датум
	 *
	 * \param n_dat - новый датум
	 */
	ASDInterLocation& setDatum(const CDatum& n_dat);

	/*!
	 * \brief Вращение вокруг оси X.
	 *
     * \param bet - угол вращения вокруг оси X, в радианах.
	 */
	ASDInterLocation& rotateX(const double& beta);

	/*!
	 * \brief Вращение вокруг оси Y.
	 *
     * \param beta - угол вращения вокруг оси Y, в радианах.
	 */
	ASDInterLocation& rotateY(const double& beta);

	/*!
	 * \brief Вращение вокруг оси Z.
	 *
     * \param beta - угол вращения вокруг оси Z, в радианах.
	 */
	ASDInterLocation& rotateZ(const double& beta);

	//! \brief Возвращает плоложение, отраженное относительно оси X.
	ASDInterLocation& reflectX();

	//! \brief Возвращает плоложение, отраженное относительно оси Y.
	ASDInterLocation& reflectY();

	//! \brief Возвращает плоложение, отраженное относительно оси Y.
	ASDInterLocation& reflectZ();

	//! \brief Возвращает используемый датум.
	CDatum getDatum() const
	{
		return m_currentDatum;
	}

	//! \brief Возврващает положение в системе координат XYZ в виде вектора.
	QVector<double> getXYZ() const
	{
		return m_xyz;
	}

	/*!
	 * \brief Возвращает вектор с широтой долготой и высотой,
     *  широта и долгота в радианах.
	 */
	QVector<double> getLLA() const;

	/*!
	 * \brief Возвращает расстояние между двумя точками на поверхности Земли
	 *  вычисленное по методу Андуайе.
	 *
	 * \param pos - точка, для которой необходимо расчитать расстояние относительно текущей.
	 *
	 * \return Значения:
     *    \li Vector(0)  расстояние, в километрах.
     *    \li Vector(1)  ошибка, в километрах.
	 */
	QVector<double> getDistance(const ASDInterLocation& pos) const;

	/*!
	 * \brief Метод, возвращающий радиус кривизны Земли.
	 *
     * \param lat - широта точки (рад).
	 */
	double getN(const double& lat) const;

	/*!
	 * \brief Метод преобразования положения заданной точки относительно текущей
	 *  из Гринвичской системы координат в локальную.
	 *
	 * \param pos - положение точки.
	 */
	QVector<double> fromECEFtoNEU(const ASDInterLocation& pos) const;

	/*!
     * \brief Метод, возвращающий угол места указанной точки (град).
	 *
	 * \param pos - положение точки.
	 */
	double getElevation(const ASDInterLocation& pos) const;

	/*!
	 * \brief Метод, возвращающий азимут указанной точки.
	 *
	 * \param pos - position of the target.
	 */
	double getAzimuth(const ASDInterLocation& pos) const;

	//! \brief Метод, возвращающий расстояние до горизонта по прямой.
	double getStraightHoriz() const;

	//! \brief Метод, возвращающий расстояние до горизонта по кривой.
	double getCurveHoriz() const;

	/*!
	 * \brief Метод, возвращающий скалярное произведение двух положений.
	 *
	 * \param b - положение, используемое для вычисления произведения.
	 */
	double getDot(const ASDInterLocation& b) const;

	/*!
	 * \brief Метод, возвращающий расстояние между двумя точками, заданными векторами в прмоугольной СК.
	 *
	 * \param a
	 * \param b - положение, используемое для вычисления произведения.
	 */
	static double calculateDistance(QVector<double> a, QVector<double> b);

	/*!
	 * \brief Метод, возвращающий единичный вектор, направленный на заданную точку.
	 *
	 * \param currentGrinvich - координаты точки, направление от которой расчитывается.
	 * \param targetGrinvich - координаты точки, на которую направлен вектор.
	 */
	static QVector<double> calculateDirectionNormal(
			QVector<double> currentGrinvich, QVector<double> targetGrinvich);

    /*!
     * \brief Метод расчета сферических координат относительного расположения обьектов. (надо еще проверить)
     *
     * \param coordVehicle - Координаты обьекта(x,y,z) в АГЭСК.
     * \param coordTarget - Координаты цели(x,y,z) в АГЭСК.
     * \return структуру сферических координат цели относительно объекта
     */
    static ASDCoordSphere calcSphereCoord(QVector<double> coordVehicle, QVector<double> coordTarget);

    /*!
     * \brief Расчитывает координаты пересечение прямой проходящей через две точки с Землей
     * \param coord0 - координаты первой точки прямой
     * \param coord1 - координаты второй точки прямой
     * \return координаты точки пересечения прямой со сферой
     */
    static QVector <double> calcInterLineWithEarth(QVector<double> coord0,QVector<double> coord1);
private:
    //! Положение в системе координат XYZ, в километрах
	QVector<double> m_xyz;

	//! Датум, используемый для отображения текущей позиции
	CDatum m_currentDatum;
};

/*!
 * \brief Функция преобразования угла из градусов (дробных)
 *  в градусы, минуты и секунды.
 *
 * \param angle   угол для преобразования.
 * \return возвращает значения:
 *    \li Vector(0)  градусы
 *    \li Vector(1)  угловые минуты
 *    \li Vector(2)  угловые секунды
 *
 * \warning Знак присваивается старшему ненулевому возвращаемому значению.
 */
QVector<double> degreesToDMS(const double angle);

#endif   // ASDINTERLOCATION_H
