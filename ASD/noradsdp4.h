/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdnoradsdp4.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDNORADSDP4_H
#define ASDNORADSDP4_H

#include <QDebug>

#include "noradtype.h"
#include "noradeq.h"

/*!
 * \brief Производный класс от ASDNoradEq для вычисления положения КА по модели NORAD
 * с периодами обращения более 225 мин
 */
class ASDNoradSDP4: public ASDNoradEq
{
public:
	/*!
	 * \brief Конструктор.
	 *
	 * \param tle - начальные условия КА TLE телеграммА.
	 */
	ASDNoradSDP4(ASDScTleInitData &tle);

	//! Деструктор по умолчанию.
	virtual ~ASDNoradSDP4();

	/*!
	 * Возвращает вектор положения и скоростей в АГЭСК на tsince мин от начального положения.
	 *
	 * \param tsince
	 * \return
	 *
	 * \warning Размерность вектора равна 6, если исходные данные были не иницилизированы
	 * то возвращает вектор размерности 0.
	 */
        QVector<double> getPosition(double tsince);

protected:
	/*!
	 * \brief Инициализация переменных для расчета возмущений.
	 *
	 * \param eosq
	 * \param sinio
	 * \param cosio
	 * \param m_betao
	 * \param m_aodp
	 * \param m_theta2
	 * \param m_sing
	 * \param m_cosg
	 * \param m_betao2
	 * \param xmdot
	 * \param omgdot
	 * \param xnodott
	 * \return
	 */
	bool DeepInit(double *eosq, double *sinio, double *cosio, double *m_betao,
			double *m_aodp, double *m_theta2, double *m_sing, double *m_cosg,
			double *m_betao2, double *xmdot, double *omgdot, double *xnodott);

	/*!
	 *
	 * \param xmdf
	 * \param omgadf
	 * \param xnode
	 * \param emm
	 * \param xincc
	 * \param xnn
	 * \param tsince
	 * \return
	 */
	bool DeepSecular(double *xmdf, double *omgadf, double *xnode, double *emm,
			double *xincc, double *xnn, double *tsince);

	/*!
	 *
	 * \param pxndot
	 * \param pxnddt
	 * \param pxldot
	 * \return
	 */
	bool DeepCalcDotTerms(double *pxndot, double *pxnddt, double *pxldot);

	/*!
	 *
	 * \param pxndot
	 * \param pxnddt
	 * \param pxldot
	 * \param delt
	 */
	void DeepCalcIntegrator(double *pxndot, double *pxnddt, double *pxldot,
			const double &delt);

	/*!
	 *
	 * \param e
	 * \param xincc
	 * \param omgadf
	 * \param xnode
	 * \param xmam
	 * \return
	 */
	bool DeepPeriodics(double *e, double *xincc, double *omgadf, double *xnode,
			double *xmam);

	double m_sing;
	double m_cosg;

	// Переменные для инициализации расчетов
	double eqsq;
	double siniq;
	double cosiq;
	double rteqsq;
	double ao;
	double cosq2;
	double sinomo;
	double cosomo;
	double bsq;
	double xlldot;
	double omgdt;
	double xnodot;

	double xll;
	double omgasm;
	double xnodes;
	double _em;
	double xinc;
	double xn;
	double t;

	double dp_e3;
	double dp_ee2;
	double dp_savtsn;
	double dp_se2;
	double dp_se3;
	double dp_sgh2;
	double dp_sgh3;
	double dp_sgh4;
	double dp_sghs;
	double dp_sh2;
	double dp_sh3;
	double dp_si2;
	double dp_si3;
	double dp_sl2;
	double dp_sl3;
	double dp_sl4;
	double dp_xgh2;
	double dp_xgh3;
	double dp_xgh4;
	double dp_xh2;
	double dp_xh3;
	double dp_xi2;
	double dp_xi3;
	double dp_xl2;
	double dp_xl3;
	double dp_xl4;
	double dp_xqncl;
	double dp_zmol;
	double dp_zmos;

	double dp_atime;
	double dp_d2201;
	double dp_d2211;
	double dp_d3210;
	double dp_d3222;
	double dp_d4410;
	double dp_d4422;
	double dp_d5220;
	double dp_d5232;
	double dp_d5421;
	double dp_d5433;
	double dp_del1;
	double dp_del2;
	double dp_del3;
	double dp_fasx2;
	double dp_fasx4;
	double dp_fasx6;
	double dp_omegaq;
	double dp_sse;
	double dp_ssg;
	double dp_ssh;
	double dp_ssi;
	double dp_ssl;
	double dp_step2;
	double dp_stepn;
	double dp_stepp;
	double dp_thgr;
	double dp_xfact;
	double dp_xlamo;
	double dp_xli;
	double dp_xni;

	bool dp_iresfl;
	bool dp_isynfl;

	double dpi_c;
	double dpi_ctem;
	double dpi_day;
	double dpi_gam;
	double dpi_stem;
	double dpi_xnodce;
	double dpi_zcosgl;
	double dpi_zcoshl;
	double dpi_zcosil;
	double dpi_zsingl;
	double dpi_zsinhl;
	double dpi_zsinil;
	double dpi_zx;
	double dpi_zy;

	double m_c5;
	double m_omgcof;
	double m_xmcof;
	double m_delmo;
	double m_sinmo;
};

#endif // ASDNORADSDP4_H
