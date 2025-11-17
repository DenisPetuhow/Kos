/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdmatrix3x3.h.\n
 ** Описание: В файле содержится класс для работы с матрицей 3х3.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 04.09.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDMATRIX3X3_H
#define ASDMATRIX3X3_H

#include <math.h>

#include <QVector>
#include <QGenericMatrix>

/*!
 * \brief Производный класс от класса QGenericMatrix.
 */
class ASDMatrix3x3: public QGenericMatrix<3, 3, qreal>
{
public:
	//! \brief Конструктор по умолчанию.
	ASDMatrix3x3();

	//! \brief Деструктор по умолчанию.
	~ASDMatrix3x3();

	/*!
	 * \brief Умножение матрицы на QVector.
	 *
	 * \param factor - исходны вектор.
	 * \return Вектор полученный в результате умножения.
	 */
	QVector<double> &operator*(QVector<double> factor);

	/*!
	 * \brief Умножение матрицы на число.
	 *
	 * \param factor - исходны вектор.
	 * \return Матрицу полученную в результате умножения.
	 */
	ASDMatrix3x3 &operator*(double factor);

	/*!
	 * \brief Транспонирование матрицы.
	 *
	 * \param rm - исходная матрица.
	 * \return Матрицу полученную в результате транспонирования.
	 */
	QMatrix3x3 transpose(const QMatrix3x3 rm);

	/*!
	 * \brief Вычисление матрицы поворота относительно координатных осей.
	 *
	 * \param angle - угол поворота
	 * \param axis - номер оси поворота.
	 * \return Матрица поворота.
	 */
	QMatrix3x3 rotation(double angle, int axis);

	/*!
	 * \brief Инверсия матрицы.
	 *
	 * \param m - исходная матрица
	 * \return Матрица полученная в результате инверсии.
	 */
	QMatrix3x3 inverse(QMatrix3x3 m);

	/*! \brief Вычисление определителя матрицы.
	 *
	 * \param m - исходная матрица.
	 * \return Определитель матрицы.
	 */
	double determinant(QMatrix3x3 m);
private:
};

#endif // ASDMATRIX3X3_H
