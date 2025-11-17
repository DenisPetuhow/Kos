/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdmobilezone.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDMOBILEZONE_H
#define ASDMOBILEZONE_H

#include <math.h>

#include <QVector>
#include <QDateTime>

#include "ASD/asdcoordconvertor.h"
#include "ASD/asdtype.h"
#include "ASD/interlocation.h"



/*!
 * \brief Класс подвижная зона обслуживания
 *
 * Содержит методы, позволяющие определить, попадают ли в задаваемую зону обзора
 * космические аппараты и наземные средства. Зона обзора задается двумя углами,
 * определяющими ее направление относительно осей орбитальной подвижной СК и углом полураствора
 */
class ASDMobileZone
{
public:
	/// Конструктор по умолчанию. Задает нулевые значения
	ASDMobileZone() :
        m_gamma(0.0), m_tangage(0.0), m_yaw(0.0), m_roll(0.0)
	{
	}

    /*! Конструктор для конусной зоны
	 *
     * \param gamma   - угол полураствора, рад
     * \param tangage - угол тангажа, рад
     * \param yaw     - угол рыскания, рад
	 */
    ASDMobileZone(double gamma, double tangage, double yaw):
        m_gamma(gamma), m_tangage(tangage), m_yaw(yaw), m_type(konuas)
	{

	}

    /*!
     * \brief Конструктор для пирамидной зоны
     * \param deltaV - угол раствора по вертикали (для прямоугольника в основании зоны обзора), рад
     * \param deltaH - угол раствора по горизонтали (для прямоугольника в основании зоны обзора).
     * \param tangage - угол тангажа, рад
     * \param yaw     - угол рыскания, рад
     * \param roll    - угол крена, рад
     */
    ASDMobileZone(double deltaV, double deltaH, double tangage, double yaw, double roll):
        m_deltaV(deltaV), m_deltaH(deltaH), m_tangage(tangage), m_yaw(yaw),
        m_roll(roll), m_type(pyramid)
    {

    }

	/// Деструктор
	virtual ~ASDMobileZone()
	{
	}

	//Операторы

	/*!
	 * \brief Устанавливает значения полей данных
     * \param gamma   - угол полураствора, рад
     * \param tangage - угол тангажа, рад
     * \param yaw     - угол рыскания, рад
	 */
    ASDMobileZone& setData(double gamma, double tangage, double yaw);

    /*!
     * \brief Устанавливает значения полей данных
     * \param deltaV - угол раствора по вертикали (для прямоугольника в основании зоны обзора), рад
     * \param deltaH - угол раствора по горизонтали (для прямоугольника в основании зоны обзора).
     * \param tangage - угол тангажа, рад
     * \param yaw     - угол рыскания, рад
     * \param roll    - угол крена, рад
     */
    ASDMobileZone& setData(double deltaV, double deltaH, double tangage, double yaw, double roll);

	/*!
	 * \brief Метод, задающий угол полураствора
	 *
	 * \param gamma    значение угла полураствора
	 */
	ASDMobileZone& setGamma(double gamma);

	/*!
	 * \brief Метод, задающий установочный угол в горизонтальной плоскости
	 *
     * \param tangage    значение установочного угла в горизонтальной плоскости
	 */
    ASDMobileZone& setTangage(double tangage);

    /*!
     * \brief Метод, задающий установочный угол в плоскости отвеса
     *
     * \param yaw    значение установочного угла в плоскости отвеса
     */
    ASDMobileZone& setYaw(double yaw);
	/*!
	 * \brief Метод, задающий установочный угол в плоскости отвеса
	 *
     * \param roll    значение установочного угла в плоскости отвеса
	 */
    ASDMobileZone& setRoll(double roll);


	/// Возвращает угол полураствора
	double getGamma() const
	{
		return m_gamma;
	}

    /// Возвращает угол тангажа, рад
    double getTangage() const
	{
        return m_tangage;
	}

    /// Возвращает угол рыскания, рад
    double getYaw() const
    {
        return m_yaw;
    }

    /// Возвращает угол крена, рад
    double getRoll() const
	{
        return m_roll;
	}

	/*!
     * \brief Определяет, находится ли один космический аппарат в зоне обзора другого.
	 *
     * \param vehicle - Координаты КА для которого задана зона обзора (АГЭСК).
	 * \param target - Координаты КА, нахождение котороге в зоне обзора определяет метод (АГЭСК).
	 * \return true если КА находится в зоне обзора, false - в противном случае.
	 */
    bool isSpacecraftInZone(QVector<double> vehicle, QVector<double> target);

	/*!
	 * \brief Определяет, находится ли точка на поверхности Земли в зоне обзора КА.
	 *        Рельеф местности не учитывается.
	 *
	 * \param current - Координаты КА для которого задана зона обзора (АГЭСК).
     * \param lla - Координаты точки на земной поверхности (широта, долгота, высота).
     * \param time - Международное время
	 * \return true если точка находится в зоне обзора, false - в противном случае.
	 */
	bool isEarthPointInZone(QVector<double> current, QVector<double> lla,
            QDateTime time);

private:
    double m_gamma;   //!< угол полураствора, рад
    double m_tangage; //!< угол тангажа, рад
    double m_yaw;     //!< угол рыскания, рад
    double m_roll;    //!< угол крена, рад
    double m_deltaV;  //!< угол раствора по вертикали (для прямоугольника в основании зоны обзора), рад
    double m_deltaH;  //!< угол раствора по горизонтали (для прямоугольника в основании зоны обзора), рад
    TypeZoneObserv m_type; //!< тип зоны обзора
};

#endif // ASDMOBILEZONE_H
