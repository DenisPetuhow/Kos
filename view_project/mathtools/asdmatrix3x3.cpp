/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdmatrix3x3.cpp.\n
 ** Описание: В файле содержится класс для работы с матрицей 3х3.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 04.09.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "asdmatrix3x3.h"

ASDMatrix3x3::ASDMatrix3x3()
{
}

ASDMatrix3x3::~ASDMatrix3x3()
{

}

QVector<double> &ASDMatrix3x3::operator*(QVector<double> factor)
{
	QVector<double> result(3);
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			result[row] += (data())[row, col] * factor[col];
	return result;
}

ASDMatrix3x3 &ASDMatrix3x3::operator*(double factor)
{
	ASDMatrix3x3 result;
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			result(row, col) = (data())[row, col] * factor;
	return result;
}

// Транспонирование
QMatrix3x3 ASDMatrix3x3::transpose(const QMatrix3x3 m)
{
	QMatrix3x3 temp;
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			temp(j, i) = m(i, j);
	return temp;
}

// Поворот оси 1,2,3
QMatrix3x3 ASDMatrix3x3::rotation(double angle, int axis)
{
	QMatrix3x3 toReturn;
	if (axis < 1 || axis > 3)
	{
		//MatrixException e("Invalid axis (must be 1,2, or 3)");
		//throw(e);
		return toReturn;
	}

	int i1 = axis - 1;
	int i2 = (i1 + 1) % 3;
	int i3 = (i2 + 1) % 3;
	toReturn(i1, i1) = 1.0;
	toReturn(i2, i2) = toReturn(i3, i3) = cos(angle);
	toReturn(i3, i2) = -(toReturn(i2, i3) = sin(angle));

	return toReturn;
}

//инверсия
QMatrix3x3 ASDMatrix3x3::inverse(QMatrix3x3 m)
{
	double s = determinant(m);
	// zero div may happen
	s = 1 / s;
	// alias-safe way.
	QMatrix3x3 t;
	t(0, 0) = (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) * s;
	t(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * s;
	t(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * s;
	t(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * s;
	t(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * s;
	t(1, 2) = (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) * s;
	t(2, 0) = (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)) * s;
	t(2, 1) = (m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1)) * s;
	t(2, 2) = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * s;

	return t;
}

//детерминат
double ASDMatrix3x3::determinant(QMatrix3x3 m)
{
	return m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) - m(0, 1) * (m(1,
			0) * m(2, 2) - m(2, 0) * m(1, 2)) + m(0, 2) * (m(1, 0) * m(2, 1)
			- m(2, 0) * m(1, 1));
}

