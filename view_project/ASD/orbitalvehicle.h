/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdorbitalvehicle.h.\n
 ** Описание: Содержит класс для инициализации орбитального средства.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDORBITALVEHICLE_H
#define ASDORBITALVEHICLE_H
#include <QVector>

#include "ASD/asdcoordconvertor.h"
#include "ASD/asdtype.h"
#include "ASD/orbitalmotion.h"
#include "ASD/mobilezone.h"

/*!
 * \brief Базовый класс для инициализации орбитального средства.
 */

class ASDOrbitalVehicle
{
public:
	//! Конструктор по умолчанию
	ASDOrbitalVehicle();

	/*!
	 * \brief Конструктор с исходными данными.
	 *
	 * \param obj - исходные данные. Задаются с использованием структуры ASDOrbitalObjectPar
	 */
	ASDOrbitalVehicle(ASDOrbitalObjectPar obj);

	//! Установить начальные данные OrbitalObject
	bool setInitParam(ASDOrbitalObjectPar obj);


	/*!
	 * \brief Задает начальное время.
	 *
	 * \param initTime - дата и время.
	 * \return код ошибки todo какие ошибки?
	 */
	int setInitTime(QDateTime initTime);

	/*!
	 * \brief Расчитывает координаты в требуемой системе координат
	 * по заданному типу прогноза на заданный интервал времени.
	 *
	 * \param period - время и дата к которой осуществляется прогноз.
	 * \param sc - тип системы координат.
	 * \param timeStep - шаг интегрирования по времени.
	 * \return вектор с координатами КС через заданный интервал в заданной системе координат.
	 */
    QVector<double> getCurrPos(QDateTime period, SystemCoord sc = AGESC);

	/*!
	 * \brief Возращает текущее значение времени и даты.
	 *
	 * \return текущее значение времени и даты.
	 */
	QDateTime getCurrTime();

	/*!
	 * \brief Устанавливает отслеживаемый вектор состояния.
	 *
	 * \param x - вектор  состояния(true- отслеживать, false-не отслеживать).
	 * todo Максимальный размер вектор состояния равно 6 (вектор положения и скорости)
	 * + m_pMobileServZone.size()(размер списка подвижных зон )
	 * + 3(cпуск(x,y,z)))
	 * По умолчанию!!!!!!
	 * размер вектора 6(вектор положения и скорости)
	 * \return
	 */
	bool setDerivatives(QVector<bool>& x);

	/*!
	 * \brief Определяет изменение вектора состояния.
	 *
	 * \param t - дата и время.
	 * \return конечный вектор изменение состояния.
	 * По умолчанию!!!!!!
	 * размер вектора = 6 (вектор положения и скорости)
	 * для включения других данных необходимо вызвать
	 * setDerivatives() и установить флаги в true.
	 */
	QVector<double> getDerivatives(QDateTime t);

	/*!
	 * \brief Устанавливает параметры пассивного участка.
	 *
	 * \param tp - дата и время.
	 * \param param - структура массогабаритных параметров.
	 */
	bool setDescend(const QDateTime tp, ASDDescendPar param);

	/*!
	 * \brief Получить точку приземления.
	 *
	 * \return координаты точки в Гринвич.(x,y,z)(м)
	 */
	QVector<double> getDescendPoint();

	/*!
	 * \brief Добавить подвижную зоны.
	 *
	 * \param szone - подвижная зона обслуживания.
	 * \return todo
	 */
	bool addMobileServZone(ASDMobileZone szone);

	//	bool chekPointInZone(libmath::Vector<double> coordPoint, SystemCoord scPoint);

	/*!
	 * \brief Определяет попадение точечного объекта в зону обзора КА.
	 *
	 * \param coordPoint - координаты объекта должны быть заданы в АГЭСК
	 * \param m_sone - подвижная зона.
	 * \return todo
	 */
	bool chekPointInMobZone(QVector<double> coordPoint, ASDMobileZone m_sone);
    ASDOrbitalObjectPar m_ParamOrbitalObject;
protected:
	//! Изменить состояние
	void resetState();

	//! Bектор флагов (отслеживаемый вектор состояния)
	QVector<bool> m_vecDer;

	//! Ссылка на орбитальное движение
	ASDOrbitalMotion* m_pOrbitMotion;

	//! Тип модели интегрирования
	int m_typeIntegrat;

	//! Параметры пассивного участока
	ASDDescendPar m_paramDescend;

	//! Время участка спуска .
	QDateTime m_datetimeDescend;

	//! подвижная зона обслуживания
	ASDMobileZone* m_pMobileServZone;

	//! Список  подвижных зон обслуживания
	QList<ASDMobileZone*> m_plMobileServZone;

	//! Начальные параметры космического объекта


	//!  Вектор состояния  6+n(m_pMobileServZone.size()+m_pStillServZone.size()+3(cпуск(x,y,z)))
	QVector<double> m_r; //!< Позиция(x,y,z)
	QVector<double> m_v; //!< Скорость(vx,vy,vz)
	QVector<double> m_p; //!< n динамические параметры
	QVector<double> objInitPos; //!< Координаты начального положения КС.
	QDateTime objInitTime; //!< Дата и время начального положения КС.
	QDateTime m_objCurrTime; //!< Дата и время текущего положения КС.

private:

};

#endif // ORBITALVEHICLE_H
