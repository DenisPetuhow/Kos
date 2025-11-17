/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Wei Yan - Chinese Academy of Sciences . 2009, 2010\n
 ** Файл: asdkeplereq.cpp.\n
 ** Описание: Класс производит некоторые полезные вычисления кеплеровской орбиты.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 2009 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#include "keplereq.h"

const double ASDKeplerEq::eps_mach = numeric_limits<double>::epsilon();
using namespace std;

QVector<double> ASDKeplerEq::State(double GM, const QVector<double>& Kep,
                                   double dt)
{

    // Keplerian elements at epoch
    const double a = Kep[0];
    const double e = Kep[1];
    const double i = Kep[2];
    const double Omega = Kep[3];
    const double omega = Kep[4];
    const double M0 = Kep[5];

    // Mean anomaly
    double M = M0 + sqrt(GM / (a * a * a)) * dt;
    M = Modulo(M, 2.0 * M_PI); // Mean anomaly


    // Eccentric anomaly

    double E = 0.;
    double cosE = 1.;
    double sinE = 0.;
    if (fabs(e)<1.e-4)
    {
        E = M;
        cosE = cos(E);
        sinE = sin(E);
    }
    else
    {
        E = EccentricAnomaly(M, e);
        cosE = cos(E);
        sinE = sin(E);
    }

    // Perifocal coordinates

    double fac = sqrt((1.0 - e) * (1.0 + e));

    double Rrrrrr = a * (1.0 - e * cosE); // Distance
    double V = sqrt(GM * a) / Rrrrrr; // Velocity

    QVector<double> r(3, 0.0), v(3, 0.0);
    r[0] = a * (cosE - e);
    r[1] = a * fac * sinE;
    r[2] = 0.0;

    v[0] = -V * sinE;
    v[1] = +V * fac * cosE;
    v[2] = 0.0;
    // Transformation to reference system (Gaussian vectors)
    //libmath::Matrix<double> PQW(3, 3, 0.0);
    QMatrix3x3 PQW;//=QGenericMatrix<3,3,0.0>;
    //PQW = ReferenceFrames::Rz(-Omega)
    //    * ReferenceFrames::Rx(-i)
    //    * ReferenceFrames::Rz(-omega);

    PQW = Rz(-Omega) * Rx(-i) * Rz(-omega);
    //r = PQW * r;
    QVector<double> tn(3);
    QVector<double> vn(3);
    tn[0] = PQW(0, 0) * r[0] + PQW(0, 1) * r[1] + PQW(0, 2) * r[2];
    tn[1] = PQW(1, 0) * r[0] + PQW(1, 1) * r[1] + PQW(1, 2) * r[2];
    tn[2] = PQW(2, 0) * r[0] + PQW(2, 1) * r[1] + PQW(2, 2) * r[2];
    //v = PQW * v;
    vn[0] = PQW(0, 0) * v[0] + PQW(0, 1) * v[1] + PQW(0, 2) * v[2];
    vn[1] = PQW(1, 0) * v[0] + PQW(1, 1) * v[1] + PQW(1, 2) * v[2];
    vn[2] = PQW(2, 0) * v[0] + PQW(2, 1) * v[1] + PQW(2, 2) * v[2];
    return Stack(tn, vn);

} // End of method 'ASDKeplerEq::State()'

// Rotate an r-matrix about the x-axis.
QMatrix3x3 ASDKeplerEq::Rx(const double& angle)
{
    const double s = sin(angle);
    const double c = cos(angle);

    const double a[9] =
    { 1, 0, 0, 0, c, s, 0, -s, c };

    QMatrix3x3 r;//=QGenericMatrix<3, 3, 0.0>;
    //r.copyDataTo(a);
    r(0, 0) = a[0];
    r(0, 1) = a[1];
    r(0, 2) = a[2];
    r(1, 0) = a[3];
    r(1, 1) = a[4];
    r(1, 2) = a[5];
    r(2, 0) = a[6];
    r(2, 1) = a[7];
    r(2, 2) = a[8];
    return r;
}

// Rotate an r-matrix about the y-axis.
QMatrix3x3 ASDKeplerEq::Ry(const double& angle)
{
    const double s = sin(angle);
    const double c = cos(angle);

    const double a[9] =
    { c, 0, -s, 0, 1, 0, s, 0, c };

    QMatrix3x3 r;//(3, 3, 0.0);
    r(0, 0) = a[0];
    r(0, 1) = a[1];
    r(0, 2) = a[2];
    r(1, 0) = a[3];
    r(1, 1) = a[4];
    r(1, 2) = a[5];
    r(2, 0) = a[6];
    r(2, 1) = a[7];
    r(2, 2) = a[8];

    return r;
}

// Rotate an r-matrix about the z-axis.
QMatrix3x3 ASDKeplerEq::Rz(const double& angle)
{
    const double s = sin(angle);
    const double c = cos(angle);

    double a[9] =
    { c, s, 0, -s, c, 0, 0, 0, 1 };

    QMatrix3x3 r;//(3, 3, 0.0);
    r(0, 0) = a[0];
    r(0, 1) = a[1];
    r(0, 2) = a[2];
    r(1, 0) = a[3];
    r(1, 1) = a[4];
    r(1, 2) = a[5];
    r(2, 0) = a[6];
    r(2, 1) = a[7];
    r(2, 2) = a[8];

    return r;
}

QVector<double> ASDKeplerEq::Elements_voz(double GM,
                                          const QVector<double>& Kep, double dt)
{
    // Keplerian elements at epoch
    double a = Kep[0];
    double e = Kep[1];
    double i = Kep[2];
    double Omega = Kep[3];
    double omega = Kep[4];
    double M0 = Kep[5];
    double T = getPeriod(Kep);
    double tau_vek=0.; //вековой уход времени прохожденния перигея
    if (fabs(e)<1.e-4)
    {
        omega = 0.;
        tau_vek =0.;
    }
    else
    {
        tau_vek = 1.5 * K2_EARTH / (K_EARTH * a * a * pow(1. - e * e, 2.)) * T * (1.
                                                                                  + 3. * e) * (1. - 3. * sin(i) * sin(i) * sin(omega) * sin(omega));
    }
    //Omega vek
    double Omega_vek = 3. * K2_EARTH * M_PI * cos(i) / (K_EARTH * pow(
                                                            (1. - e * e) * a, 2.));

    Omega += Omega_vek / T * dt;
    Omega = Modulo(Omega, 2.0 * M_PI);
    // Mean anomaly
    double M = M0 + sqrt(GM / (a * a * a)) * dt;
    //    M += - tau_vek / T * dt;
    M = Modulo(M, 2.0 * M_PI); // Mean anomaly


    //omega vek
    double omega_vek = 0.;
    if (fabs(e)>1.e-4)
        omega_vek =3. / 2. * K2_EARTH * M_PI / (K_EARTH * a * a * pow(1. - e * e, 2.))*(1.-5.*cos(i)*cos(i));
   // omega += omega_vek / T * dt;
    omega = Modulo(omega, 2.0 * M_PI);

    // Keplerian elements vector


    QVector<double> Kep1(6, 0.0);
    Kep1[0] = a;
    Kep1[1] = e;
    Kep1[2] = i;
    Kep1[3] = Omega;
    Kep1[4] = omega;
    Kep1[5] = M;

    return Kep1;

}

double ASDKeplerEq::EccentricAnomaly(double M, double e)
{
    const int maxit = 15;
    const double eps = 100.0 * eps_mach;

    // Variables
    int i = 0;
    double E, f;

    // Starting value

    M = Modulo(M, 2.0 * M_PI);
    if (e < 0.8)
        E = M;
    else
        E = M_PI;

    // Iteration
    do
    {
        f = E - e * sin(E) - M;
        E = E - f / (1.0 - e * cos(E));
        ++i;
        if (i == maxit)
        {
            cerr << " convergence problems in EccAnom" << endl;
            break;
        }
    } while (fabs(f) > eps);

    return E;

}

double ASDKeplerEq::TrueAnomaly(double M, double e)
{
    double E = EccentricAnomaly(M, e);

    double scta = sqrt(1.0 - e * e) * sin(E) / (1.0 - e * cos(E));
    double ccta = (cos(E) - e) / (1.0 - e * cos(E));

    return atan2(scta, ccta);
}

double ASDKeplerEq::MeanAnomaly(double cta, double e)
{
    double sinE = (sqrt(1.0 - e * e) * sin(cta)) / (1.0 + e * cos(cta));
    double cosE = (e + cos(cta)) / (1.0 + e * cos(cta));
    double E = atan2(sinE, cosE);

    return (E - e * sin(E));
}

double ASDKeplerEq::FindEta(const QVector<double>& r_a,
                            const QVector<double>& r_b, double tau)
{
    // Constants

    const int maxit = 30;
    const double delta = 100.0 * eps_mach;

    // Variables
    double kappa, m, l, s_a, s_b, eta_min, eta1, eta2, F1, F2, d_eta;

    // Auxiliary quantities
    s_a = sqrt(r_a[0] * r_a[0] + r_a[1] * r_a[1] + r_a[2] * r_a[2]);
    s_b = sqrt(r_b[0] * r_b[0] + r_b[1] * r_b[1] + r_b[2] * r_b[2]);
    double ddd = (r_a[0] * r_b[0] + r_a[1] * r_b[1] + r_a[2] * r_b[2]);

    kappa = sqrt(2.0 * (s_a * s_b + ddd));

    m = tau * tau / pow(kappa, 3);
    l = (s_a + s_b) / (2.0 * kappa) - 0.5;

    eta_min = sqrt(m / (l + 1.0));

    // Start with Hansen's approximation
    eta2 = (12.0 + 10.0 * sqrt(1.0 + (44.0 / 9.0) * m / (l + 5.0 / 6.0)))
            / 22.0;
    eta1 = eta2 + 0.1;

    // Secant method

    F1 = F(eta1, m, l);
    F2 = F(eta2, m, l);

    int i = 0;

    while (fabs(F2 - F1) > delta)
    {
        d_eta = -F2 * (eta2 - eta1) / (F2 - F1);
        eta1 = eta2;
        F1 = F2;
        while (eta2 + d_eta <= eta_min)
            d_eta *= 0.5;
        eta2 += d_eta;
        F2 = F(eta2, m, l);
        ++i;

        if (i == maxit)
        {
            cerr << "WARNING: Convergence problems in FindEta" << endl;
            break;
        }
    }

    return eta2;
}

QVector<double> ASDKeplerEq::Stack(QVector<double> r, QVector<double> v)
{
    const int n = r.size() + v.size();
    QVector<double> rv(n, 0.0);

    for (int i = 0; i < n; i++)
    {
        if (i < r.size())
        {
            rv[i] = r[i];
        }
        else
        {
            rv[i] = v[i - r.size()];
        }
    }

    return rv;
}

QVector<double> ASDKeplerEq::Elements(double Mjda, double Mjdb, const QVector<
                                      double>& ra, const QVector<double>& rb)
{

    // Variables
    double a, e, i, Omega, omega, M;

    // Calculate vector r_0 (fraction of r_b perpendicular to r_a)
    // and the magnitudes of r_a,r_b and r_0

    double s_a = sqrt(ra[0] * ra[0] + ra[1] * ra[1] + ra[2] * ra[2]);
    QVector<double> e_a(3, 0.0);
    e_a[0] = ra[0] / s_a;
    e_a[1] = ra[1] / s_a;
    e_a[2] = ra[2] / s_a;
    double s_b = sqrt(rb[0] * rb[0] + rb[1] * rb[1] + rb[2] * rb[2]);
    double fac = (rb[0] * e_a[0] + rb[1] * e_a[1] + rb[2] * e_a[2]);//dot(rb, e_a);
    QVector<double> r_0(3, 0.0);
    r_0[0] = rb[0] - fac * e_a[0];
    r_0[1] = rb[1] - fac * e_a[1];
    r_0[2] = rb[2] - fac * e_a[2];
    double s_0 = sqrt(r_0[0] * r_0[0] + r_0[1] * r_0[1] + r_0[2] * r_0[2]);
    QVector<double> e_0(3, 0.0);// = r_0 / s_0;
    e_0[0] = r_0[0] / s_0;
    e_0[1] = r_0[1] / s_0;
    e_0[2] = r_0[2] / s_0;

    // Inclination and ascending node

    QVector<double> W(3, 0.0);
    //= cross(e_a, e_0);

    W[0] = e_a[1] * e_0[2] - e_a[2] * e_0[1];
    W[1] = e_a[2] * e_0[0] - e_a[0] * e_0[2];
    W[2] = e_a[0] * e_0[1] - e_a[1] * e_0[0];
    Omega = atan2(W[0], -W[1]); // Long. ascend. node
    Omega = Modulo(Omega, 2.0 * M_PI);
    i = atan2(sqrt(W[0] * W[0] + W[1] * W[1]), W[2]); // Inclination

    double u(0.0);
    if (i == 0.0)
        u = atan2(ra[1], ra[0]);
    else
        u = atan2(+e_a[2], -e_a[0] * W[1] + e_a[1] * W[0]);

    // Semilatus rectum

    double tau = sqrt(K_EARTH) * 86400.0 * fabs(Mjdb - Mjda);
    double eta = FindEta(ra, rb, tau);
    double p = pow(s_a * s_0 * eta / tau, 2);

    // Eccentricity, true anomaly and argument of perihelion

    double cos_dnu = fac / s_b;
    double sin_dnu = s_0 / s_b;

    double ecos_nu = p / s_a - 1.0;
    double esin_nu = (ecos_nu * cos_dnu - (p / s_b - 1.0)) / sin_dnu;

    e = sqrt(ecos_nu * ecos_nu + esin_nu * esin_nu);
    double nu = atan2(esin_nu, ecos_nu);

    omega = Modulo(u - nu, 2.0 * M_PI);

    // Perihelion distance, semimajor axis and mean motion

    a = p / (1.0 - e * e);
    double n = sqrt(K_EARTH / fabs(a * a * a));

    // Mean anomaly and time of perihelion passage

    if (e < 1.0)
    {
        double E =
                atan2(sqrt((1.0 - e) * (1.0 + e)) * esin_nu, ecos_nu + e * e);
        M = Modulo(E - e * sin(E), 2.0 * M_PI);
    }
    else
    {
        double sinhH = sqrt((e - 1.0) * (e + 1.0)) * esin_nu
                / (e + e * ecos_nu);
        M = e * sinhH - log(sinhH + sqrt(1.0 + sinhH * sinhH));
    }

    // Keplerian elements vector

    QVector<double> Kep(6, 0.0);
    Kep[0] = a;
    Kep[1] = e;
    Kep[2] = i;
    Kep[3] = Omega;
    Kep[4] = omega;
    Kep[5] = M;

    return Kep;

}

double ASDKeplerEq::F(double eta, double m, double l)
{

    const double eps = 100.0 * eps_mach;

    double w, W, a, n, g;

    w = m / (eta * eta) - l;

    if (fabs(w) < 0.1)
    {
        W = a = 4.0 / 3.0;
        n = 0.0;
        do
        {
            n += 1.0;
            a *= w * (n + 2.0) / (n + 1.5);
            W += a;
        } while (fabs(a) >= eps);
    }
    else
    {
        if (w > 0.0)
        {
            g = 2.0 * asin(sqrt(w));
            W = (2.0 * g - sin(2.0 * g)) / pow(sin(g), 3);
        }
        else
        {
            g = 2.0 * log(sqrt(-w) + sqrt(1.0 - w)); // =2.0*arsinh(sqrt(-w))
            W = (sinh(2.0 * g) - 2.0 * g) / pow(sinh(g), 3);
        }
    }

    return (1.0 - eta + (w + l) * W);

} // End of function F


double ASDKeplerEq::getPeriod(const QVector<double>& Kep)
{
    const double n = sqrt(K_EARTH / pow(Kep[0], 3));
    return 2.0 * M_PI / n;
}

double ASDKeplerEq::getApogee(const QVector<double>& Kep)
{
    // p =  a*(1-e*e)
    double p = Kep[0] * (1.0 - Kep[1] * Kep[1]);
    return p / (1 - Kep[1]);
}

double ASDKeplerEq::getPerigee(const QVector<double>& Kep)
{
    // p =  a*(1-e*e)
    double p = Kep[0] * (1.0 - Kep[1] * Kep[1]);

    return p / (1 + Kep[1]);
}

double ASDKeplerEq::TrueAnomaly(QVector<double> coord)
{
    return atan2(coord.value(1), coord.value(0));
}

double ASDKeplerEq::FocalParameter(QVector<double> coord)
{
    return (K_EARTH * pow(sin(TrueAnomaly(coord)), 2)) / pow(coord.value(4), 2);
}

double ASDKeplerEq::Eccentricity(QVector<double> coord)
{

    return coord.value(4) * sin(TrueAnomaly(coord)) / coord.value(4) - cos(
                TrueAnomaly(coord));
}

