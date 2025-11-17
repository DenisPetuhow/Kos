/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: rungekutta4.cpp.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания: 08.09.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#include "asdrungekutta4.h"

/* The classic Runge Kutta 4th Order Integration Algorithm.
 *
 * This routine integrates using a Runge Kutta 4th order algorithm
 * with a fixed step from the internal time to \a nextTime.
 *
 * @param nextTime   The time to integrate to.
 * @param stepSize   The amount time between internal
 *                   integration steps.
 */
void RungeKutta4::integrateTo(double nextTime, double stepSize)
{

	if (stepSize == 0)
	{
		stepSize = nextTime - currentTime;
	}

	bool done(false);
	int i;
	while (!done)
	{

		// Time steps
		double ctPlusDeltaT = currentTime + stepSize;
		double ctPlusHalfDeltaT = currentTime + (stepSize * 0.5);

		// k1
		for (i = 0; i < m_currentState.size(); ++i)
		{
			k1[i] = stepSize * derivative(currentTime, m_currentState, k1).at(i);

			tempy[i] = m_currentState[i] + (0.5 * k1[i]);
		}

		// k2
		for (i = 0; i < m_currentState.size(); ++i)
		{
			k2[i] = stepSize * derivative(ctPlusHalfDeltaT, tempy, k2).at(i);
			tempy[i] = m_currentState[i] + (0.5 * k2[i]);
		}
		// k3
		for (i = 0; i < m_currentState.size(); ++i)
			k3[i] = stepSize * derivative(ctPlusHalfDeltaT, tempy, k3).at(i);

		// k4
		for (i = 0; i < m_currentState.size(); ++i)
			k4[i] = stepSize * derivative(ctPlusDeltaT, tempy, k4).at(i);
		for (i = 0; i < m_currentState.size(); ++i)
			m_currentState[i] += (k1[i] + (2.0 * (k2[i] + k3[i])) + k4[i]) / 6.0;

		// If we are within m_teps of the goal time, we are done.
		if (fabs(currentTime + stepSize - nextTime) < m_teps)
		{
			done = true;
		}

		// If we are about to overstep, change the stepsize appropriately
		// to hit our target final time;
		if ((currentTime + stepSize) > nextTime)
		{
			stepSize = (nextTime - currentTime);
		}

		currentTime += stepSize;

	} // End of 'while (!done)...'

	currentTime = nextTime;

} // End of method 'RungeKutta4::integrateTo()'



