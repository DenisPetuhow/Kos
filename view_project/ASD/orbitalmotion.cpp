/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdorbitalmotion.cpp.\n
 ** Описание: Содержит класс расчет движения космического объекта\n
 ** при различных начальных данных.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "orbitalmotion.h"
#include <QDebug>
#define LITTLE_VALUE 1.e-6
#define M_PI		3.14159265358979323846
#define R_E 6371.0
#define MIN_PER_DAY 1440.0
#define sqr(x) (x*x)
#define M_2PI        (2 * M_PI)
#define DEG_PER_RAD (180.0 / M_PI)
#define RAD_PER_DEG (M_PI / 180.0)
#define deg2rad(x) (x * RAD_PER_DEG)
#define TLE_LINE_BYTES   (69)
#define TLE_EPOCH_YEAR_COL (18)
#define TLE_EPOCH_YEAR_LEN  (2)
#define TLE_EPOCH_COL      (20)
#define TLE_EPOCH_LEN      (12)
#define TLE_BSTAR_COL      (53)
#define TLE_BSTAR_LEN       (6)
#define TLE_BSTAR_EXP_COL  (59)
#define TLE_BSTAR_EXP_LEN   (2)
#define TLE_INCLIN_COL      (8)
#define TLE_INCLIN_LEN      (8)
#define TLE_RAAN_COL       (17)
#define TLE_RAAN_LEN        (8)
#define TLE_ECCENTR_COL    (26)
#define TLE_ECCENTR_LEN     (7)
#define TLE_PERIGEE_COL    (34)
#define TLE_PERIGEE_LEN     (8)
#define TLE_ANOMALY_COL    (43)
#define TLE_ANOMALY_LEN     (8)
#define TLE_MOTION_COL     (52)
#define TLE_MOTION_LEN     (11)
#define TLE_REVOL_COL      (63)
#define TLE_REVOL_LEN       (5)

using namespace std;

ASDOrbitalMotion::ASDOrbitalMotion()

{
    //memset(&m_tle, 0, sizeof(m_tle));
    m_typeIntegrat = 0;
    m_pNoradModel = 0;
    m_initData = false;
    //memset(&m_kep, 0, sizeof(m_kep));
    //memset(&m_ags, 0, sizeof(m_ags));
    m_x0.resize(6);
}
ASDOrbitalMotion::~ASDOrbitalMotion()
{
    //memset(&m_tle, 0, sizeof(m_tle));
    // if ( m_pNoradModel ) delete m_pNoradModel;
}

//! конструктор с исходными данными tle norad(структура)
ASDOrbitalMotion::ASDOrbitalMotion(ASDScTleInitData tle)
{

}

//! конструктор с исходными данными tle norad(название +2-x строчник)
ASDOrbitalMotion::ASDOrbitalMotion(ASDScStleInitData stle)
{
    bool ok;
    ok = setBeginParam(stle);
    if (!ok)
    {
        //qDebug()()<<"error dan";
    }
}

//! конструктор с  исходными данными Kepler
ASDOrbitalMotion::ASDOrbitalMotion(ASDScKeplerInitData kep)
{
    m_kep = kep;
    m_curr_time = kep.t_epoch;
    m_typeIntegrat = 0;
    m_initData = true;
}

//! конструктор с исходными данными АГЭСК
ASDOrbitalMotion::ASDOrbitalMotion(ASDScEciInitData ags)
{
    //qDebug()()<<"ags init";
    m_ags = ags;
    m_curr_time = ags.t_epoch;
    //qDebug()()<<"ags init";
    m_typeIntegrat = 1;
    m_initData = true;
}

bool ASDOrbitalMotion::setBeginParam(ASDScTleInitData tle)
{
    m_tle = tle;
    initVariablesNorad();
    m_typeIntegrat = 2;
    m_initData = true;
    return true;
}

bool ASDOrbitalMotion::setBeginParam(ASDScStleInitData stle)
{

    bool ok = false;
    QString lineTLE = stle.firstString;
    //lineTLE.replace("  ","");
    QStringList str=lineTLE.split(" ");
    str.removeOne("");
    str.removeOne("");
    str.removeOne("");
    str.removeOne("");
    str.removeOne("");
    str.removeOne("");
    QStringList::Iterator iter;
    for(iter=str.begin();iter!=str.end();++iter)
    {
        QString istr=QString((*iter));
        //  qDebug()<<"iter,,,  ="<<istr<<istr.size();
        if(istr.size()==0)
        {
            str.erase(iter);

        }
    }
    // qDebug()<<"tke 1="<<str.size();

    // qDebug()<<"srt=="<<str.size()<<str.at(0)<<str.at(1)<<str.at(2)<<str.at(3)<<str.at(4)<<str.at(5)<<str.at(6)<<str.at(7)<<str.at(8);
    // qDebug()<<"sr=="<<stle.firstString<<lineTLE.mid(TLE_EPOCH_YEAR_COL, TLE_EPOCH_YEAR_LEN);
    //   qDebug()<<"sr 2=="<<stle.secondString;
    if (!lineTLE.isEmpty() && isValidLineTLE(lineTLE))
    {
        m_tle.epochYear
                = lineTLE.mid(TLE_EPOCH_YEAR_COL, TLE_EPOCH_YEAR_LEN).toUInt(
                    &ok);
        if(str.size()>=4)
        {QString sttg=str.at(3);
            m_tle.epochYear=sttg.left(2).toInt(&ok);
        }

        if (m_tle.epochYear < 57)
        {
            m_tle.epochYear += 2000;
        }
        else
        {
            m_tle.epochYear += 1900;
        }
        m_tle.epochDay
                = lineTLE.mid(TLE_EPOCH_COL, TLE_EPOCH_LEN).toDouble(&ok);

        if(str.size()>=4)
        {QString sttg=str.at(3);
            m_tle.epochDay=sttg.right(12).toDouble(&ok);
        }
        m_tle.bstar = (lineTLE.mid(TLE_BSTAR_COL, 1) + "." + lineTLE.mid(
                           TLE_BSTAR_COL + 1, TLE_BSTAR_LEN - 1) + "E" + lineTLE.mid(
                           TLE_BSTAR_EXP_COL, TLE_BSTAR_EXP_LEN)).toDouble(&ok);


        if(str.size()>=6)
        {QString sttg=str.at(6);
            //  qDebug()<<"bstar="<<str.at(6)<<sttg.left(1)<<sttg.mid(0, 5)<<  "E" <<sttg.mid(5, 2);

            m_tle.bstar=((sttg.left(1)+ "." + sttg.mid(0, 5) + "E" + sttg.mid(5, 2)).toDouble(&ok));
        }

    }
    else
    {
        ok = false;
        m_initData = false;
        //    qDebug()<<"nnnnnnnn";
        return ok;
    }
    lineTLE = stle.secondString;
    QStringList str2=lineTLE.split(" ");
    //qDebug()<<"tke 2="<<str2.size();
    str2.removeOne("");
    //qDebug()<<"tke 2="<<str2.size();
    str2.removeOne("");
    str2.removeOne("");
    str2.removeOne("");
    //qDebug()<<"tke 2="<<str2.size();

    str2.removeOne("");
    //qDebug()<<"tke 2="<<str2.size();
    if(str2.size()>8)
    {
        QStringList::Iterator iter;
        for(iter=str2.begin();iter!=str2.end();++iter)
        {
            QString istr=QString((*iter));
            //     qDebug()<<"iter="<<istr<<istr.size();
            if(istr.size()==0)
            {
                str2.erase(iter);

            }
        }

    }
    //qDebug()<<"tke 2 rem="<<str2.size();
    // qDebug()<<"srt 2=="<<str2.size()<<str2.at(0)<<str2.at(1)<<str2.at(2)<<str2.at(3)<<str2.at(4)<<str.at(5);
    if (!lineTLE.isEmpty() && isValidLineTLE(lineTLE))
    {
        //  qDebug()<<"3"<<str2.at(2);

        m_tle.inclination = deg2rad( lineTLE.mid( TLE_INCLIN_COL,
                                                  TLE_INCLIN_LEN ).toDouble(&ok) );
        if(str2.size()>6)
        {
            QString sttgi= str2.at(2);
            m_tle.inclination = deg2rad(sttgi.toDouble(&ok));

        }

        m_tle.raan = deg2rad( lineTLE.mid( TLE_RAAN_COL,
                                           TLE_RAAN_LEN ).toDouble(&ok) );
        if(str2.size()>6)
        {
            QString sttgr= str2.at(3);
            m_tle.raan = deg2rad(sttgr.toDouble(&ok));

        }

        m_tle.eccentr
                = ("0." + lineTLE.mid(TLE_ECCENTR_COL, TLE_ECCENTR_LEN)).toDouble(
                    &ok);
        if(str2.size()>6)
        {
            QString sttge= str2.at(4);
            m_tle.eccentr = ("0." + sttge).toDouble(&ok);

        }

        m_tle.perigee = deg2rad( lineTLE.mid( TLE_PERIGEE_COL,
                                              TLE_PERIGEE_LEN ).toDouble(&ok) );
        if(str2.size()>6)
        {
            QString sttgp= str2.at(5);
            m_tle.perigee = deg2rad( sttgp.toDouble(&ok));

        }

        m_tle.meanAnomaly = deg2rad( lineTLE.mid( TLE_ANOMALY_COL,
                                                  TLE_ANOMALY_LEN ).toDouble(&ok) );
        double _meanMotion =
                lineTLE.mid(TLE_MOTION_COL, TLE_MOTION_LEN).toDouble(&ok);
        //  qDebug()<<"_meanMotion = "<<_meanMotion<<lineTLE.mid(TLE_MOTION_COL, TLE_MOTION_LEN)<<"ss="<<str2.at(7);
        if(str2.size()>6)
        {
            QString sttg2= str2.at(7);
            _meanMotion =sttg2.toDouble(&ok);

        }

        m_tle.meanMotion = _meanMotion * M_2PI / MIN_PER_DAY;
        m_tle.revolNumber = lineTLE.mid(TLE_REVOL_COL, TLE_REVOL_LEN).toUInt(
                    &ok);
    }
    else
    {
        ok = false;
        m_initData = false;
        return ok;
    }
    initVariablesNorad();
    m_typeIntegrat = 2;
    m_initData = true;
    return true;
}
//! выбор SGP4/SDP4 модели; заполнение переменных, расчитанных по TLE
void ASDOrbitalMotion::initVariablesNorad()
{
    // if(m_initData==false) return;
    m_jdEpoch = Jd(m_tle.epochYear, m_tle.epochDay);
    //  qDebug()<<"norad dat ="<<m_jdEpoch<<m_tle.epochYear<<m_tle.epochDay;

    /* Period > 225 minutes is deep space => SDP4*/
    double a1 = pow(XKE / m_tle.meanMotion, TWO_THRD);
    double temp = (1.5 * CK2 * (3.0 * sqr( cos(m_tle.inclination) ) - 1.0)
                   / pow(1.0 - sqr(m_tle.eccentr), 1.5));
    double delta1 = temp / sqr(a1);
    double a0 = a1 * (1.0 - delta1 * ((1.0 / 3.0) + delta1 * (1.0 + 134.0
                                                              / 81.0 * delta1)));
    double delta0 = temp / sqr(a0);

    m_meanMotionRec = m_tle.meanMotion / (1.0 + delta0);
    m_aeAxisSemiMinorRec = a0 / (1.0 - delta0);
    m_aeAxisSemiMajorRec = m_aeAxisSemiMinorRec
            / sqrt(1.0 - sqr(m_tle.eccentr));
    m_kmPerigeeRec = EQUATOR_RAD * (m_aeAxisSemiMajorRec
                                    * (1.0 - m_tle.eccentr) - AE);
    m_kmApogeeRec = EQUATOR_RAD * (m_aeAxisSemiMajorRec * (1.0 + m_tle.eccentr)
                                   - AE);
    //    qDebug()<<"norad t="<<M_2PI / m_meanMotionRec;
    //    qDebug()<<"norad a="<<a0<<EQUATOR_RAD<<delta0<<m_kmPerigeeRec-6371.0;
    //    qDebug()<<"norad t="<< m_meanMotionRec;
    // m_tle.bstar=0.;
    //   qDebug()<<"norad tle bs="<< m_tle.bstar;
    //    qDebug()<<"norad tle e="<< m_tle.eccentr;
    //    qDebug()<<"norad tle dd="<< m_tle.epochDay;
    //    qDebug()<<"norad tle gg="<< m_tle.epochYear;
    //    qDebug()<<"norad tle i="<< m_tle.inclination*180./M_PI;
    //    qDebug()<<"norad tle M="<< m_tle.meanAnomaly*180./M_PI;
    //    qDebug()<<"norad tle per="<< m_tle.perigee*180./M_PI;
    //    qDebug()<<"norad tle l="<< m_tle.raan*180./M_PI;

    //    qDebug()<<"norad tle per="<< M_2PI /m_meanMotionRec   ;
    //    qDebug()<<"norad tle ap rkm="<< m_kmApogeeRec   ;
    if (M_2PI / m_meanMotionRec >= 225.0)
    {
        m_pNoradModel = new (std::nothrow) ASDNoradSDP4(m_tle);
    }
    else
    {
        m_pNoradModel = new (std::nothrow) ASDNoradSGP4(m_tle);
    }
}

bool ASDOrbitalMotion::setBeginParam(ASDScKeplerInitData kep)
{
    m_kep = kep;
    m_typeIntegrat = 0;
    m_curr_time = kep.t_epoch;
    m_initData = true;
    return true;
}

bool ASDOrbitalMotion::setBeginParam(ASDScEciInitData ags)
{
    m_curr_time = ags.t_epoch;
    m_ags = ags;
    m_initData = true;
    m_typeIntegrat = 1;
    m_x0.resize(6);

    return true;
}
//! Установить данные для системы ДУ
bool ASDOrbitalMotion::setEquationOfParam(const ASDFmcData &forcedan)
{

    return true;
}
//! Установить тип модели движения (0-Kepler, 1- ДУ, 2- tle norad)
bool ASDOrbitalMotion::setIntegrateParam(int typeIntegrat)
{
    //qDebug()()<<"int=="<<typeIntegrat;
    m_typeIntegrat = typeIntegrat;
    if (m_typeIntegrat == 0)
    {
        //qDebug()()<<"kepl''''' ";
        //		m_jdEpoch = m_kep.t_epoch;
        double day=m_kep.t_epoch.date().dayOfYear()+(
                    m_kep.t_epoch.time().hour()*3600+
                    m_kep.t_epoch.time().minute()*60+
                    m_kep.t_epoch.time().second())/86400.;

        m_jdEpoch=Jd(m_kep.t_epoch.date().year(),day);

        return true;
    }
    if (m_typeIntegrat == 1)
    {
        m_x0.resize(6);
        if (m_pEquationModel )
        {   m_x0[0]=m_ags.x;
            m_x0[1]=m_ags.y;
            m_x0[2]=m_ags.z;
            m_x0[3]=m_ags.vx;
            m_x0[4]=m_ags.vy;
            m_x0[5]=m_ags.vz;

            double day=m_ags.t_epoch.date().dayOfYear()+(
                        m_ags.t_epoch.time().hour()*3600+
                        m_ags.t_epoch.time().minute()*60+
                        m_ags.t_epoch.time().second())/86400.;

            m_jdEpoch=Jd(m_ags.t_epoch.date().year(),day);

            // m_jdEpoch=m_ags.t_epoch;
            //qDebug()()<<"init data=eeeeeeq"<<m_ags.x;

        }
    }
    if (m_typeIntegrat == 2)
    {
        m_jdEpoch = Jd(m_tle.epochYear, m_tle.epochDay);

    }

    // }
    return true;
}
//! проверка контрольной суммы строки TLE
bool ASDOrbitalMotion::isValidLineTLE(const QString& line)
{
    int cs = 0;
    for (uint i = 0; i < uint(line.length()) - 1; i++)
    {
        if (line[i].isDigit())
        {
            cs += line[i].digitValue();
        }
        else if (line[i] == '-')
        {
            cs++;
        }
    }
    cs %= 10;//последняя цифра получившейся суммы

    return (cs == line[line.length() - 1].digitValue());
}

double ASDOrbitalMotion::Jd(int year, double day)
{
    double temp = 0.;

    year--;
    // static const double TJ2000 = 2451545.;

    // Centuries are not leap years unless they divide by 400
    int A = (year / 100);
    int B = 2 - A + (A / 4);

    double NewYears = (int) (365.25 * year) + (int) (30.6001 * 14) + 1720994.5
            + B; // 1720994.5 = Oct 30, year -1

    temp = NewYears + day;
    return temp;

}
QVector<double> ASDOrbitalMotion::getPosition(double ts)
{
    //qDebug()()<<"m_initData";
    QVector<double> pos(6, 0.0);
    if (m_initData == false)
    {
        //eror
        //qDebug()()<<"init data=null";
        pos.resize(0);
        return pos;
    }
    //libmath::Vector<double> pos(6,0.0);
    //kepler
    if (m_typeIntegrat == 0)
    {
        //m_Kepmodel
        //if(m_kep.a!=0)
        {
            QVector<double> kep(6);
            QVector<double> kepl(6);
            kep[0] = m_kep.a;
            kep[1] = m_kep.e;
            kep[2] = m_kep.i;
            kep[3] = m_kep.l;
            kep[4] = m_kep.omega;

            double cta = m_kep.u - kep[4];


            /** Computes the true anomaly for elliptic orbits
                 * @param cta  True anomaly in [rad]
                 * @param e    Eccentricity of the orbit [0,1]
                 * @return     Mean anomaly in [rad]
                 */
            double M = ASDKeplerEq::MeanAnomaly(cta, kep[1]);

            //M=cta;
            kep[5] = fmod2p(M);
            if(kep[1]==0)
            {
                kep[5]= m_kep.u;
                kep[4] =0.;
            }
            double dt=0.;
            kepl=ASDKeplerEq::Elements_voz(K_EARTH,kep,ts);
            pos = ASDKeplerEq::State(K_EARTH, kepl, dt);

        }

    }
    // ags
    if (m_typeIntegrat == 1)
    {
        if (m_pEquationModel )
        {
            double mas[6];
            for(int z= 0; z<6; z++)
                mas[z]= m_x0[z];

            int i=0;
            while(i!=ts)
            {
                methodsRungeKutta(1., 6, mas);
                i++;
            }
            for(int z= 0; z<6; z++)
                m_x0[z]= mas[z];
            pos = m_x0;

        }

    }
    // tle;
    if (m_typeIntegrat == 2)
    {

        if (m_pNoradModel)
        {
            double tsince = ts / 60.;
            pos = m_pNoradModel->getPosition(tsince);

        }
    }

    return pos;
}

QVector<double> ASDOrbitalMotion::getPosition(QDateTime dt)
{
    double tsince;
    QVector<double> pos(6, 0.0);
    if (m_initData == false)
    {

        pos.resize(0);
        return pos;
    }
    if(m_typeIntegrat == 2)
    {
        QTime time = dt.time();
        double day = dt.date().dayOfYear() + (time.hour() + (time.minute()
                                                             + ((time.second() + (time.msec() / 1000.0)) / 60.0)) / 60.0) / 24.0;

        double mid = Jd(dt.date().year(), day);

        tsince = (mid - m_jdEpoch) * MIN_PER_DAY;
    }

    else
    {
        tsince=m_curr_time.secsTo(dt)/60.;
        if(m_typeIntegrat == 1)
        {
            m_curr_time = dt;
        }

    }


    pos = getPosition(tsince*60.);


    return pos;

}



/*!
 * \brief derivativeDescende правые части для спуска в АГСК
 * \param X - значение.
 * \param Y - производная X.
 */
void ASDOrbitalMotion::derivativeDescende(double *X, double *Y)
{
    double r;

    // радиус;
    r = pow(pow(X[0], 2) + pow(X[1], 2) + pow(X[2], 2), 0.5);

    Y[0] = X[3];
    Y[1] = X[4];
    Y[2] = X[5];
    Y[3] = -K_EARTH / pow(r, 3) * X[0] - 1.5 * K2_EARTH / pow(r, 4) * (5 * pow(X[2] / r, 2) - 1) * X[0] / r;
    Y[4] = -K_EARTH / pow(r, 3) * X[1] - 1.5 * K2_EARTH / pow(r, 4) * (5 * pow(X[2] / r, 2) - 1) * X[1] / r;
    Y[5] = -K_EARTH / pow(r, 3) * X[2] - 1.5 * K2_EARTH / pow(r, 4) * (5 * pow(X[2] / r, 2) - 3) * X[2] / r;
}

void ASDOrbitalMotion::methodsRungeKutta(double stepIntegration, int n,	double* X)
{

    static double A[25], B[25], C[25];
    double h2, q;
    int i;

    h2 = stepIntegration / 2.0;

    derivativeDescende(X, B);

    for (i = 0; i < n; i++)
    {
        C[i] = B[i] * h2;
        A[i] = X[i] + C[i];
    }

    derivativeDescende(A, B);
    for (i = 0; i < n; i++)
    {
        q = B[i] * h2;
        A[i] = X[i] + q;
        C[i] = C[i] + q + q;
    }
    derivativeDescende(A, B);
    for (i = 0; i < n; i++)
    {
        q = B[i] * stepIntegration;
        A[i] = X[i] + q;
        C[i] = C[i] + q;
    }

    derivativeDescende(A, B);
    for (i = 0; i < n; i++)
    {
        X[i] = X[i] + (C[i] + B[i] * h2) / 3.0;
        //  m_x[i] = X[i];
    }
}
//////////////////////////////////////////////////////////////////////////////
// getComponent()
// Return requested components of date.
// Year : Includes the century.
// Month: 1..12
// Day  : 1..31 including fractional part
void ASDOrbitalMotion::GetDateJD(double jdate,int    *pYear,
                                 int    *pMon  /* = NULL */,
                                 double *pDOM  /* = NULL */)
{


    double jdAdj = jdate + 0.5;
    int    Z     = (int)jdAdj;  // integer part
    double F     = jdAdj - Z;   // fractional part
    double alpha = (int)((Z - 1867216.25) / 36524.25);
    double A     = Z + 1 + alpha - (int)(alpha / 4.0);
    double B     = A + 1524.0;
    int    C     = (int)((B - 122.1) / 365.25);
    int    D     = (int)(C * 365.25);
    int    E     = (int)((B - D) / 30.6001);

    double DOM   = B - D - (int)(E * 30.6001) + F;
    int    month = (E < 13.5) ? (E - 1) : (E - 13);
    int    year  = (month > 2.5) ? (C - 4716) : (C - 4715);

    *pYear = year;

    if (pMon != NULL)
    {
        *pMon = month;
    }

    if (pDOM != NULL)
    {
        *pDOM = DOM;
    }
}



