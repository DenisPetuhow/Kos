/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asddifeq.cpp.\n
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
#include "difeq.h"


QVector<double> ASDDifEq::derivative(const QVector<double> inState)
{
    double r;

    QVector<double> inStateDot(6,0);
	// радиус;
	r = pow(pow(inState[0], 2) + pow(inState[1], 2) + pow(inState[2], 2), 0.5);

	inStateDot[0] = inState[3];
	inStateDot[1] = inState[4];
	inStateDot[2] = inState[5];

	inStateDot[3] = -K_EARTH / pow(r, 3) * inState[0] - 1.5 * K2_EARTH / pow(r,
			4) * (5 * pow(inState[2] / r, 2) - 1) * inState[0] / r;
	inStateDot[4] = -K_EARTH / pow(r, 3) * inState[1] - 1.5 * K2_EARTH / pow(r,
			4) * (5 * pow(inState[2] / r, 2) - 1) * inState[1] / r;
	inStateDot[5] = -K_EARTH / pow(r, 3) * inState[2] - 1.5 * K2_EARTH / pow(r,
			4) * (5 * pow(inState[2] / r, 2) - 3) * inState[2] / r;

	return inStateDot;

}
