/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Wei Yan - Chinese Academy of Sciences . 2009, 2010\n
 ** Файл: asdkeplereq.h.\n
 ** Описание: Класс производит вычисления кеплеровской орбиты.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 2009 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef  ASDKEPLEREQ_H_
#define  ASDKEPLEREQ_H_

#include <limits.h>
#include <limits>
#include <iostream>
#include <math.h>

#include <QGenericMatrix>
#include <QVector>

#include "ASD/asdtype.h"

using namespace std;

/*!
 * \brief Класс производит некоторые полезные вычисления кеплеровской орбиты.
 *
 */

class ASDKeplerEq
{
public:

	//! Конструктор по умолчанию.
	ASDKeplerEq()
	{
	}
	;

	//! Деструктор по умолчанию.
	~ASDKeplerEq()
	{
	}
	;

	/*!
	 * \brief Вычисление положения КА по элементам Кеплера для
	 * эллиптических орбит.
	 *
	 * \param GM - гравитационная констатнта.
	 * \param Kep - вектор размерности 6 элементов Кеплера (a e i OMG omg M).
	 * \param dt - время эпохи.
	 * \return Вектор размерности 6 ,положения и скорости КА.
	 *
	 * \warning Большая полусь a=Kep(0), время dt и констатнта GM
	 * должны определены в одной системе.
	 */
	static QVector<double> State(double GM, const QVector<double>& Kep,
			double dt);

	/*!
	 * \brief Вычисление элементов Кеплера для эллиптических орбит
	 * с учетом возмущений ДВУ.
	 *
	 * \param GM - гравитационная константа.
	 * \param Kep - вектор размерности 6 ,положения и скорости КА.
	 * \param dt - время эпохи.
	 * \return Вектор размерности 6 элементов Кеплера (a e i OMG omg M).
	 *
	 * \warning Большая полусь a=Kep(0), время dt и констатнта GM
	 * должны определены в одной системе.
	 */
	static QVector<double> Elements_voz(double GM, const QVector<double>& Kep,
			double dt);

	/*!
	 * \brief Вычисляет кеплеровские элементы орбиты по двум радиус-векторам и связанными с ними моментами времени.
	 * Решение задачи Элера-Ламберта для эллиптических орбит.
	 *
	 * \param Mjda - время заданное в Модифицированной Юлианской Дате.
	 * \param Mjdb - время заданное в Модифицированной Юлианской Дате.
	 * \param ra - радиус-вектор во время Mjda.
	 * \param rb - радиус-вектор во время Mjdb.
	 * \return Кеплеровские элементы (a, e, я, Омега, омега, M) во время Mjda.
	 *
	 * \warning Функция не может использоваться с векторами, описывающими круговую или
	 *  экваториальную орбиту.
	 */
	static QVector<double> Elements(double Mjda, double Mjdb, const QVector<
			double>& ra, const QVector<double>& rb);

	/*!
	 * \brief Вычисляет эксцентрическую аномалию для эллиптических орбит.
	 *
	 * \param M - средняя аномалия [рад].
	 * \param e - эксцентриситет орбиты [0,1].
	 * \return Эксцентрическая аномалия [рад].
	 */
	static double EccentricAnomaly(double M, double e);

	/*!
	 * \brief Вычисляет истинную аномалию для эллиптических орбит.
	 *
	 * \param M - средняя аномалия в [рад].
	 * \param e - эксцентриситет орбиты [0,1].
	 * \return Истинная аномалия [рад].
	 */
	static double TrueAnomaly(double M, double e);

	/*!
	 * \brief Вычисляет среднюю аномалию для эллиптических орбит.
	 *
	 * \param cta - истиная аномалия [рад].
	 * \param e - эксцентриситет орбиты [0,1].
	 * \return Средняя аномалия [рад].
	 */
	static double MeanAnomaly(double cta, double e);

	/*!
	 * \brief Вычисляет период орбиты.
	 *
	 * \param Kep - кеплеровские элементы.
	 * \return Период орбиты.
	 */
	static double getPeriod(const QVector<double>& Kep);

	/*!
	 * \brief Возвращиет радиус апогея.
	 *
	 * \param Kep - кеплеровские элементы.
	 * \return Радиус апогея.
	 */
	static double getApogee(const QVector<double>& Kep);

	/*!
	 * \brief Вычисляет радиус перигея.
	 *
	 * \param Kep - кеплеровские элементы.
	 * \return Радиус перигея.
	 */
	static double getPerigee(const QVector<double>& Kep);

	/*!
	 * \brief Вычисляет истинную аномалию.
	 *
	 * \param coord - вектор координат объекта в орбитальной неподвижной СК (x,y,z,Vx,Vy,Vz).
	 * \return Истинная аномалия.
	 */
	static double TrueAnomaly(QVector<double> coord);

	/*!
	 * \brief Вычисляет фокальный параметр.
	 *
	 * \param coord - вектор координат объекта в орбитальной неподвижной СК (x,y,z,Vx,Vy,Vz).
	 * \return Фокальный параметр.
	 */
	static double FocalParameter(QVector<double> coord);

	/*!
	 * \brief Вычисляет экцентриситет.
	 *
	 * \param coord - вектор координат объекта в орбитальной неподвижной СК (x,y,z,Vx,Vy,Vz).
	 * \return Экцентриситет.
	 */
	static double Eccentricity(QVector<double> coord);

private:

	/*!
	 * \brief Вычисляет треугольное сектором отношение из двух радиус-векторов и промежуточное время.
	 *
	 * \param r_a - позиция во время t_a.
	 * \param r_b - позиция во время t_b.
	 * \param tau - нормализованное время (sqrt (GM) * (t_a-t_b)).
	 * \return Треугольное сектором отношение.
	 */
	static double FindEta(const QVector<double>& r_a,
			const QVector<double>& r_b, double tau);

	/*!
	 * \brief Вычисляет дробную часть числа (y = x-[x])
	 *
	 * \param x - число.
	 * \return Дробная часть числа x.
	 */
	static double Frac(double x)
	{
		return x - floor(x);
	}
	;

	/*!
	 * \brief x mod y
	 *
	 * \param x
	 * \param y
	 * \return
	 */
	static double Modulo(double x, double y)
	{
		return y * Frac(x / y);
	}

	/*!
	 * \brief Локальная функция для использования FindEta ().
	 *
	 * \param eta
	 * \param m
	 * \param l
	 * \return
	 */
	static double F(double eta, double m, double l);

	/*!
	 * \brief Соединяет два вектора.
	 *
	 * \param r - первый вектор.
	 * \param v - второй вектор.
	 * \return Соединенный вектор.
	 */
	static QVector<double> Stack(QVector<double> r, QVector<double> v);

	/*!
	 * \brief Вычисление матрицы поворота вокруг осей.
	 *
	 * \param angle    угол поворота [rad].
	 * \return Матрицу поворота.
	 */
	static QMatrix3x3 Rx(const double& angle);
	static QMatrix3x3 Ry(const double& angle);
	static QMatrix3x3 Rz(const double& angle);

private:

	//! Числовые пределы.
	static const double eps_mach; // = numeric_limits<double>::epsilon();

};

#endif

