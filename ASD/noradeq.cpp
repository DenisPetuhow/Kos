/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdnoradeq.cpp.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "noradeq.h"

const double QO = AE + 120.0 / EQUATOR_RAD;
const double Ss = AE + 78.0 / EQUATOR_RAD;
const double QOMS2T = pow((QO - Ss), 4); //(QO - S)^4 ER^4
const double GEOSYNC_ALT = 42241.892; // km
const double MIN_PER_DAY = 1440.0;

ASDNoradEq::ASDNoradEq(ASDScTleInitData& tle)
{
	m_tle = tle;
	init();
}

ASDNoradEq::~ASDNoradEq()
{
}

// Initialize()
// Perform the initialization of member variables, specifically the variables
// used by derived-class objects to calculate ECI coordinates.
void ASDNoradEq::init()
{
	m_satInc = m_tle.inclination;
	m_satEcc = m_tle.eccentr;

	m_cosio = cos(m_satInc);
	m_theta2 = m_cosio * m_cosio;
	m_x3thm1 = 3.0 * m_theta2 - 1.0;
	m_eosq = m_satEcc * m_satEcc;
	m_betao2 = 1.0 - m_eosq;
	m_betao = sqrt(m_betao2);

	// The "recovered" semi-minor axis and mean motion.


	double a1 = pow(XKE / m_tle.meanMotion, TWO_THRD);
	double temp = (1.5 * CK2 * (3.0 * sqr( cos(m_tle.inclination) ) - 1.0)
			/ pow(1.0 - sqr(m_tle.eccentr), 1.5));
	double delta1 = temp / sqr(a1);
	double a0 = a1 * (1.0 - delta1 * ((1.0 / 3.0) + delta1 * (1.0 + 134.0
			/ 81.0 * delta1)));
	double delta0 = temp / sqr(a0);

	double _meanMotionRec = m_tle.meanMotion / (1.0 + delta0);
	double _aeAxisSemiMinorRec = a0 / (1.0 - delta0);
	//  double _aeAxisSemiMajorRec = _aeAxisSemiMinorRec / sqrt( 1.0 - sqr(tle.eccentr) );
	//m_kmPerigeeRec       = EQUATOR_RAD * (_aeAxisSemiMajorRec * (1.0 - tle.eccentr) - AE);
	//m_kmApogeeRec        = EQUATOR_RAD * (_aeAxisSemiMajorRec * (1.0 + tle.eccentr) - AE);


	m_aodp = _aeAxisSemiMinorRec;
	m_xnodp = _meanMotionRec;

	//qDebug()<<"base init xn"<<m_xnodp<<"_aeAxisSemiMinorRec="<<_aeAxisSemiMinorRec;
	// For perigee below 156 km, the values of S and QOMS2T are altered.
	m_perigee = EQUATOR_RAD * (m_aodp * (1.0 - m_satEcc) - AE);

    m_s4 = Ss;
	m_qoms24 = QOMS2T;

	if (m_perigee < 156.0)
	{
		m_s4 = m_perigee - 78.0;

		if (m_perigee <= 98.0)
		{
			m_s4 = 20.0;
		}

		m_qoms24 = pow((120.0 - m_s4) * AE / EQUATOR_RAD, 4.0);
		m_s4 = m_s4 / EQUATOR_RAD + AE;
	}

	const double pinvsq = 1.0 / (m_aodp * m_aodp * m_betao2 * m_betao2);

	m_tsi = 1.0 / (m_aodp - m_s4);
	m_eta = m_aodp * m_satEcc * m_tsi;
	m_etasq = m_eta * m_eta;
	m_eeta = m_satEcc * m_eta;

	const double psisq = fabs(1.0 - m_etasq);

	m_coef = m_qoms24 * pow(m_tsi, 4.0);
	m_coef1 = m_coef / pow(psisq, 3.5);

	const double c2 = m_coef1 * m_xnodp * (m_aodp * (1.0 + 1.5 * m_etasq
			+ m_eeta * (4.0 + m_etasq)) + 0.75 * CK2 * m_tsi / psisq * m_x3thm1
			* (8.0 + 3.0 * m_etasq * (8.0 + m_etasq)));

	m_c1 = m_tle.bstar * c2;
	m_sinio = sin(m_satInc);

	const double a3ovk2 = -XJ3 / CK2 * pow(AE, 3.0);

	m_c3 = m_coef * m_tsi * a3ovk2 * m_xnodp * AE * m_sinio / m_satEcc;
	m_x1mth2 = 1.0 - m_theta2;
	m_c4 = 2.0 * m_xnodp * m_coef1 * m_aodp * m_betao2 * (m_eta * (2.0 + 0.5
			* m_etasq) + m_satEcc * (0.5 + 2.0 * m_etasq) - 2.0 * CK2 * m_tsi
			/ (m_aodp * psisq) * (-3.0 * m_x3thm1 * (1.0 - 2.0 * m_eeta
			+ m_etasq * (1.5 - 0.5 * m_eeta)) + 0.75 * m_x1mth2 * (2.0
			* m_etasq - m_eeta * (1.0 + m_etasq)) * cos(2.0 * m_tle.perigee)));

	const double theta4 = m_theta2 * m_theta2;
	const double temp1 = 3.0 * CK2 * pinvsq * m_xnodp;
	const double temp2 = temp1 * CK2 * pinvsq;
	const double temp3 = 1.25 * CK4 * pinvsq * pinvsq * m_xnodp;

	m_xmdot = m_xnodp + 0.5 * temp1 * m_betao * m_x3thm1 + 0.0625 * temp2
			* m_betao * (13.0 - 78.0 * m_theta2 + 137.0 * theta4);

	const double x1m5th = 1.0 - 5.0 * m_theta2;

	m_omgdot = -0.5 * temp1 * x1m5th + 0.0625 * temp2 * (7.0 - 114.0 * m_theta2
			+ 395.0 * theta4) + temp3 * (3.0 - 36.0 * m_theta2 + 49.0 * theta4);

	const double xhdot1 = -temp1 * m_cosio;

	m_xnodot = xhdot1 + (0.5 * temp2 * (4.0 - 19.0 * m_theta2) + 2.0 * temp3
			* (3.0 - 7.0 * m_theta2)) * m_cosio;
	m_xnodcf = 3.5 * m_betao2 * xhdot1 * m_c1;
	m_t2cof = 1.5 * m_c1;
	m_xlcof = 0.125 * a3ovk2 * m_sinio * (3.0 + 5.0 * m_cosio)
			/ (1.0 + m_cosio);
	m_aycof = 0.25 * a3ovk2 * m_sinio;
	m_x7thm1 = 7.0 * m_theta2 - 1.0;

}
QVector<double> ASDNoradEq::finalPosition(double incl, double omega,
		double e, double a, double xl, double xnode, double xn, double tsince)
//EciPoint &eci)
{
        QVector<double> pos(6, 0.0);
	if ((e * e) > 1.0)
	{
		// error in satellite data
		pos.resize(0);
		return pos;
		// qDebug()<<"e="<<e;
	}

	double beta = sqrt(1.0 - e * e);

	// Long period periodics
	double axn = e * cos(omega);
	double temp = 1.0 / (a * beta * beta);
	double xll = temp * m_xlcof * axn;
	double aynl = temp * m_aycof;
	double xlt = xl + xll;
	double ayn = e * sin(omega) + aynl;

	// Solve Kepler's Equation

	double capu = fmod2p(xlt - xnode);
	double temp2 = capu;
	double temp3 = 0.0;
	double temp4 = 0.0;
	double temp5 = 0.0;
	double temp6 = 0.0;
	double sinepw = 0.0;
	double cosepw = 0.0;
	bool fDone = false;

	for (int i = 1; (i <= 10) && !fDone; i++)
	{
		sinepw = sin(temp2);
		cosepw = cos(temp2);
		temp3 = axn * sinepw;
		temp4 = ayn * cosepw;
		temp5 = axn * cosepw;
		temp6 = ayn * sinepw;

		double epw = (capu - temp4 + temp3 - temp2) / (1.0 - temp5 - temp6)
				+ temp2;

		if (fabs(epw - temp2) <= 1.0e-06)
		{
			fDone = true;
		}
		else
		{
			temp2 = epw;
		}
	}

	// Short period preliminary quantities
	double ecose = temp5 + temp6;
	double esine = temp3 - temp4;
	double elsq = axn * axn + ayn * ayn;
	temp = 1.0 - elsq;
	double pl = a * temp;
	double r = a * (1.0 - ecose);
	double temp1 = 1.0 / r;
	double rdot = XKE * sqrt(a) * esine * temp1;
	double rfdot = XKE * sqrt(pl) * temp1;
	temp2 = a * temp1;
	double betal = sqrt(temp);
	temp3 = 1.0 / (1.0 + betal);
	double cosu = temp2 * (cosepw - axn + ayn * esine * temp3);
	double sinu = temp2 * (sinepw - ayn - axn * esine * temp3);
	double u = atan2(sinu, cosu);
	double sin2u = 2.0 * sinu * cosu;
	double cos2u = 2.0 * cosu * cosu - 1.0;

	temp = 1.0 / pl;
	temp1 = CK2 * temp;
	temp2 = temp1 * temp;

	// Update for short periodics
	double rk = r * (1.0 - 1.5 * temp2 * betal * m_x3thm1) + 0.5 * temp1
			* m_x1mth2 * cos2u;
	double uk = u - 0.25 * temp2 * m_x7thm1 * sin2u;
	double xnodek = xnode + 1.5 * temp2 * m_cosio * sin2u;
	double xinck = incl + 1.5 * temp2 * m_cosio * m_sinio * cos2u;
	double rdotk = rdot - xn * temp1 * m_x1mth2 * sin2u;
	double rfdotk = rfdot + xn * temp1 * (m_x1mth2 * cos2u + 1.5 * m_x3thm1);

	// Orientation vectors
	double sinuk = sin(uk);
	double cosuk = cos(uk);
	double sinik = sin(xinck);
	double cosik = cos(xinck);
	double sinnok = sin(xnodek);
	double cosnok = cos(xnodek);
	double xmx = -sinnok * cosik;
	double xmy = cosnok * cosik;
	double ux = xmx * sinuk + cosnok * cosuk;
	double uy = xmy * sinuk + sinnok * cosuk;
	double uz = sinik * sinuk;
	double vx = xmx * cosuk - cosnok * sinuk;
	double vy = xmy * cosuk - sinnok * sinuk;
	double vz = sinik * cosuk;

	// Position
	double x = rk * ux;
	double y = rk * uy;
	double z = rk * uz;

	//EciCoord vecPos(x, y, z);

	// Validate on altitude
	double r_a = sqrt(x * x + y * y + z * z);
	double altKm = (r_a * (EQUATOR_RAD / AE));
	//qDebug()<<"alt orb sgp4="<<altKm<<r_a<<rk;
	if ((altKm < EQUATOR_RAD) || (altKm > (2 * GEOSYNC_ALT)))
		return pos;

	// Velocity
	double xdot = rdotk * ux + rfdotk * vx;
	double ydot = rdotk * uy + rfdotk * vy;
	double zdot = rdotk * uz + rfdotk * vz;

	//EciCoord vecVel(xdot, ydot, zdot);

	//JullianDate gmt = _sat.epoch();
	//gmt.addMin(tsince);

	//vecPos.mul( EQUATOR_RAD / AE );
	//vecVel.mul( (EQUATOR_RAD / AE) * (MIN_PER_DAY / 86400) );
        pos[4] = ydot * ((EQUATOR_RAD / AE) * (MIN_PER_DAY / 86400));
        pos[5] = zdot * ((EQUATOR_RAD / AE) * (MIN_PER_DAY / 86400));
	//eci = EciPoint(vecPos, vecVel, gmt);
        pos[0] = x * EQUATOR_RAD / AE;
        pos[1] = y * EQUATOR_RAD / AE;
        pos[2] = z * EQUATOR_RAD / AE;
        pos[3] = xdot * ((EQUATOR_RAD / AE) * (MIN_PER_DAY / 86400));

	return pos;
}

