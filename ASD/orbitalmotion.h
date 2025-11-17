/*!
 ******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: \file asdorbitalmotion.h.\n
 ** Описание: Содержит класс расчет движения космического объекта\n
 ** при различных начальных данных.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDCORBITMOTION_H
#define ASDCORBITMOTION_H

#include <math.h>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QVector>

#include "ASD/asdtype.h"
#include "ASD/noradtype.h"
#include "ASD/noradsdp4.h"
#include "ASD/noradsgp4.h"
#include "ASD/keplereq.h"
#include "ASD/noradeq.h"
#include "ASD/difeq.h"

/*!
 * \brief Класс производит расчет движения космического объекта
 *  при различных начальных данных.
 *
 */
class ASDOrbitalMotion
{
public:
	//! Конструктор по умолчанию.
	ASDOrbitalMotion();

	//! Деструктор по умолчанию.
	virtual ~ASDOrbitalMotion();

	//! Конструктор с исходными данными. Задаются с использованием структуры ASDScTleInitData.

	ASDOrbitalMotion(ASDScTleInitData tle);

	//! Конструктор с исходными данными.Задаются с использованием структуры ASDScStleInitData.
	ASDOrbitalMotion(ASDScStleInitData stle);

	//! Конструктор с  исходными данными.Задаются с использованием структуры ASDScKeplerInitData.
	ASDOrbitalMotion(ASDScKeplerInitData kep);

	//! Конструктор с исходными данными АГЭСК. Задаются с использованием структуры ASDScEciInitData.
	ASDOrbitalMotion(ASDScEciInitData ags);

	/*!
	 * \brief Возвращает вектор положения и скоростей в АГЭСК на ts сек от начального положения.
     * \param ts - todo время от начального положения (сек).
	 * \return возвращает вектор положения и скоростей в АГЭСК на ts сек от начального положения
     * \warning Размерность вектора равна 6, если исходные данные были не иницилизированы
	 * то возвращает вектор размерности 0.
	 */
        QVector<double> getPosition(double ts);

	/*!
	 * \brief Возвращает вектор положения и скоростей в АГЭСК на заданную дату и время dt.
	 * \param dt - todo заданное время.
	 * \return возвращает вектор положения и скоростей в АГЭСК на заданную дату и время dt.
	 */
        QVector<double> getPosition( QDateTime dt);

	/*!
	 * \brief Установить начальные данные.
	 * \param tle - исходные данные. Задаются с использованием структуры ASDScTleInitData.
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setBeginParam(ASDScTleInitData tle);

	/*!
	 * \brief Установить начальные данные.
	 *
	 * \param stle - исходные данные. Задаются с использованием структуры ASDScStleInitData.
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setBeginParam(ASDScStleInitData stle);

	/*!
	 * \brief Установить начальные данные.
	 *
	 * \param kep - исходные данные. Задаются с использованием структуры ASDScKeplerInitData.
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setBeginParam(ASDScKeplerInitData kep);

	/*!
	 * \brief Установить начальные данные.
	 *
	 * \param ags - исходные данные. Задаются с использованием структуры ASDScEciInitData.
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setBeginParam(ASDScEciInitData ags);

	/*!
	 * \brief Установить данные для системы ДУ.
	 *
	 * \param forcedan - данные для системы ДУ. Задаются с использованием структуры ASDFmcData
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setEquationOfParam(const ASDFmcData &forcedan);

	/*!
	 * \brief Установить тип модели движения (0-Kepler, 1- ДУ, 3- tle norad).
	 *
	 * \param typeIntegrat - тип модели движения (0-Kepler, 1- ДУ, 3- tle norad).
	 * \return todo 1 если установлены 0 если неустановлены.
	 */
	bool setIntegrateParam(int typeIntegrat);

	/*!
	 * \brief Получить юлианскую эпоху.
	 *
	 * \param year - год.
	 * \param day - день.
	 * \return юлианскую эпоху.
	 */
	double Jd(int year, double day);

	/*!
	 * \brief Получить год, месяц и день по юлианской дате
	 *
	 * \param jdate - юлианской дате
	 * \param pYear - год.
	 * \param pMon - месяц(1-12).
	 * \param pDOM - день (целая часть номер дня 1-31).
	 */
	void GetDateJD(double jdate, int *pYear, int *pMon /* = NULL */,
			double *pDOM /* = NULL */);
	/*!
	 * \brief getMjd получить юлианскую дату.
	 * \return юлианская дата.
	 */
	double getMjd() const
	{
		return m_jdEpoch;
	}

    void derivativeDescende(double *X, double *Y);
    void methodsRungeKutta(double stepIntegration, int n,	double* X);
    QVector<double> calcParametrs(double stepIntegration);

private:
        bool m_initData; //!< инициализация начальных условий.
        int m_typeIntegrat;//!< тип модели движения.
        double m_jdEpoch;//!< юлианская эпоха.
	//! Kepler
        ASDScKeplerInitData m_kep;//!< начальные данные в элементах Кеплера.
        ASDKeplerEq m_Kepmodel;//!<  модель движения в элементах Кеплера.
	//! ODU
        ASDDifEq* m_pEquationModel;//!  модель движения в ДУ.
        ASDScEciInitData m_ags;//!< начальные данные векторов положения и скорости в АГСК.
        QVector<double> m_x0;
	//! Norad
        ASDNoradEq *m_pNoradModel;//!  модель движения Norad.
        ASDScTleInitData m_tle;//!< начальные данные для модели Norad.
        bool isValidLineTLE(const QString& line);//!< Проверка исходных данных для модели Norad.
        void initVariablesNorad();//!< Инициализация исходных данных для модели Norad.
        double m_meanMotionRec;//!< среднее движение,рад/мин (для модели Norad).
        double m_aeAxisSemiMinorRec;//!< радиус малой полуоси, АЕ (для модели Norad).
        double m_aeAxisSemiMajorRec;//!< радиус большой полуоси, АЕ  (для модели Norad).
        double m_kmPerigeeRec;//!< высота перигея, км (для модели Norad).
        double m_kmApogeeRec;//!< высота апогея, км (для модели Norad).
        QDateTime m_curr_time;//!< Текушее время.

};

#endif //
