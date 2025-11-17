/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asddifeq.h.\n
 ** Описание: Содержит класс моделирования движения орбитального объекта в модели
 **  с ДУ.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#ifndef ASDDIFEQ_H
#define ASDDIFEQ_H

#include <math.h>

#include <QVector>

#include "ASD/asdtype.h"
#include "ASD/asdrungekutta4.h"

/*!
 * \brief Класс для моделирования движения орбитального объекта в модели с ДУ.
 */
class ASDDifEq: public RungeKutta4
{
public:

	/*!
	 * \brief Конструктор.
	 *
	 * \param initialState - начальный вектор переменных интегрирования.
	 * \param initialTime - начальное время интегрирования (сек).
	 * \param step - шаг интегрирования (сек).
	 */
	ASDDifEq(const QVector<double>& initialState, double initialTime = 0,
			double timeEpsilon = 1e-18) :
		RungeKutta4(initialState, initialTime, timeEpsilon)
	{
	}
	;

	/*!
	 * \brief Определение метода вычисления правых частей ДУ. Вычисление производных.
	 *
	 * \param time - время интегрирования (сек).
	 * \param inState - матрица переменных интегрирования.
	 */
    virtual QVector<double> derivative(const QVector<double> inState);


};

#endif // ASDDIFEQ_H
