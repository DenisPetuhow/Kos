/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdnoradeq.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDNORADEQ_H
#define ASDNORADEQ_H

#include <QDebug>
#include <QVector>

#include "ASD/asdtype.h"
#include "ASD/noradtype.h"

/*!
 * \brief Базовый класс для вычисления положения КА по модели NORAD
 */

class ASDNoradEq
{
public:
	//! Конструктор
	ASDNoradEq(ASDScTleInitData&);

	//! Деструктор
	virtual ~ASDNoradEq();

	/*!
	 * Возвращает вектор положения и скоростей в АГЭСК на tsince мин от начального положения
	 *
	 * \param tsince
	 * \return Возвращает вектор положения и скоростей в АГЭСК на tsince мин от начального положения
	 *
	 * \warning Размерность вектора равна 6, если исходные данные были не иницилизированы
	 * то возвращает вектор размерности 0
	 */
	virtual QVector<double> getPosition(double tsince) = 0;

protected:
	//! Вычисление финальной позиции
	QVector<double> finalPosition(double incl, double omega, double e,
			double a, double xl, double xnode, double xn, double tsince);

	//! Структура с 2х-строчными элементами NORAD
	ASDScTleInitData m_tle;

	// Орбитальные параметры
	double m_satInc; //! Наклонение орбиты
	double m_satEcc; //! Эксцентриситет орбиты

	// Глобальные переменные
	double m_cosio;
	double m_theta2;
	double m_x3thm1;
	double m_eosq;
	double m_betao2;
	double m_betao;
	double m_aodp;
	double m_xnodp;
	double m_s4;
	double m_qoms24;
	double m_perigee;
	double m_tsi;
	double m_eta;
	double m_etasq;
	double m_eeta;
	double m_coef;
	double m_coef1;
	double m_c1;
	double m_c2;
	double m_c3;
	double m_c4;
	double m_sinio;
	double m_a3ovk2;
	double m_x1mth2;
	double m_xmdot;
	double m_omgdot;
	double m_xhdot1;
	double m_xnodot;
	double m_xnodcf;
	double m_t2cof;
	double m_xlcof;
	double m_aycof;
	double m_x7thm1;

private:
	void init();

};

#endif // ASDNORADEQ_H
