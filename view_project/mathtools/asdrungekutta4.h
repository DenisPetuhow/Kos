/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: rungekutta4.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания: 08.09.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include <math.h>

#include <QVector>


/*!
 * \brief В этом классе реализован классический алгоритм Рунге-Кутты 4-го - 5-го порядка.
 *
 * This function integrates by applying a 4th order Runge Kutta
 * algorithm multiple times. This provides two benefits. First, an
 * estimate of the truncation error is returned. Second, the multiple
 * 4th order estimates are combined to produce the 5th order estimate.
 *
 * nextTime   The time to integrate to.
 * error      The Matrix of estimated integration error
 *                   (one for each element).
 * stepSize   The amount time between internal.
 *                   integration steps.
 */

class RungeKutta4
{
public:

	/*!
	 * \brief Конструктор.
	 *
	 * \param initalState - вектор начальных условий.
	 * \param initialTime - начальное время.
	 * \param timeEpsilon - точность вычислений.
	 */
	RungeKutta4(const QVector<double>& initialState, double initialTime = 0,
			double timeEpsilon = 1e-18) :
		m_currentState(initialState), currentTime(initialTime),
				m_teps(timeEpsilon), m_M(initialState.size()), m_N(1), k1(m_M), k2(m_M),
				k3(m_M), k4(m_M), yn(m_M), tempy(m_M)
	{
	}
	;

	/*!
	 * \brief Интегрирование.
	 *
	 * \param nextTime - время интегрирования.
	 * \param stepSize - шаг интегрирования.
	 */
	void integrateTo(double nextTime, double stepSize = 0);

	/*!
	 * \brief Виртуальная функция вычисления производных интегрирования.
	 *
	 * \param time - время.
	 * \param inState - начальные данные на момент time.
	 * \param inStateDot - производные  для начальных условий inState .
	 * \return \todo a reference to \a inStateDot.
	 */
	virtual QVector<double>& derivative(long double time,
			const QVector<double>& inState, QVector<double>& inStateDot) = 0;

	/*!
	 *  \brief Возвращает текущее время
	 *
	 *  \return Текущее время.
	 */
	double getTime(void)
	{
		return currentTime;
	}

	/*!
	 * \brief Возвращает текущий ветор данных.
	 *
	 * \return Текущий вектор данных.
	 */
	const QVector<double>& getState(void)
	{
		return m_currentState;
	}

protected:

	//! Текущее время.
	double currentTime;

	//! Текущий вектор данных \todo описать структуру.
	QVector<double> m_currentState;

	double m_teps; //!< Ошибка вычислений.
	int m_M; //!< Количество строк матрицы данных.
	int m_N; //!< Количество столбцов матрицы данных.
private:

	RungeKutta4(const RungeKutta4& cloneDonor);

	RungeKutta4& operator=(const RungeKutta4& right);

	QVector<double> k1, k2, k3, k4, yn, tempy;

}; // End of class 'RungeKutta4'

#endif // RUNGEKUTTA4_H
