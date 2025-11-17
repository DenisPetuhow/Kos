#include "calcplan.h"
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_matrix.h>
//#include <gsl/gsl_odeiv2.h>
////#include "SunPosition.hpp"
//#include <gsl/gsl_odeiv.h>
//**************************** 29.06.2016 *********************************//
//
// Освещенность Солнца
//
//**************************** 29.06.2016 *********************************//
double sumf;
double sumtr;
bool intersectionRsphera (QVector<double> PosSun,QVector<double> Pos, const double Rsphere )
{
    QVector<double> u(3);
    QVector<double> v(3);

    u[0]=-PosSun[0];
    u[1]=-PosSun[1];
    u[2]=-PosSun[2];
    v[0]=Pos[0]-PosSun[0];
    v[1]=Pos[1]-PosSun[1];
    v[2]=Pos[2]-PosSun[2];
    double a=u[0]*u[0]+u[1]*u[1]+u[2]*u[2];
    double b=v[0]*u[0]+v[1]*u[1]+v[2]*u[2];
    double c=u[0]*u[0]+u[1]*u[1]+u[2]*u[2]-Rsphere*Rsphere;
    if(a==0)
    {

        if(c>0) return true;
        return false;
    }
    double d = b * b - a * c;
    if ( d < 0 ) return true;
    d = sqrt ( d );
    const double t1 = ( b - d ) / a;
    if ( t1 > 1 ) return true;
    const double t2 = ( b + d ) / a;
    if ( t2 < 0 ) return true;
    return false;

}
CalcPlan::CalcPlan(QObject* aparent) :
    QObject(aparent)

{
   // Q_D(CalcPlan);

m_fil="temp.dat";
qRegisterMetaType<t_plan>("t_plan");

//ptr=(std::tr1::shared_ptr<CalcPlan>) (this);

}
CalcPlan::~CalcPlan()
{
//m_orbitalVehicle.clear();
//// m_eathVehicle.clear();
//  // this->destroyed();
//  // ptr.reset();
//qDebug()<<"destroy Calcplan";
}

/*!
 * \brief Вычисление арксинуса. При значении аргумента, выходящем за пределы +/-1, он приравнивается граничному значению.
 * \param x аргумент
 * \return арксинус аргумента
 */
double spAsin1(double x)
{
    if (x > 1.0) x = 1.0;
    if (x < -1.0) x = -1.0;

    return asin(x);
}

/*!
 * \brief Вычисление арккосинуса. При значении аргумента, выходящем за пределы +/-1, он приравнивается граничному значению.
 * \param x аргумент
 * \return арккосинус аргумента
 */
double spAcos1(double x)
{
    if (x > 1.0) x = 1.0;
    if (x < -1.0) x = -1.0;

    return acos(x);
}


/*!
 * \brief Расчёт углового расстояния между двумя точками (географические координаты)
 * \param geo1 Первая точка
 * \param geo2 Вторая точка
 * \return Возвращаемое угловое расстояние, радиан
 */
double CalcPlan::geoDistance(const double lat1,const double lon1, const double lat2,const double lon2)
{
    float a = spAcos1(cos(lat1)*cos(fabs(lon1-lon2)));
    float A = M_PI_2;
    if (sin(a) != 0) {
        A = spAsin1(sin(lat1)/sin(a));
    }

    float cos_d = cos(lat2)*cos(a) + sin(lat2)*sin(a)*cos(M_PI_2 - A);
    return spAcos1(cos_d);
}

void CalcPlan::setDat(QVector<ASDOrbitalObjectPar> orbitalVehicle,
                      QVector<ParamGrBaseInter> eathVehicle, QDateTime startTime,
                      QDateTime endTime, int timestep)
{

    m_orbitalVehicle = orbitalVehicle;
    m_eathVehicle = eathVehicle;
    m_startTime = startTime;
    m_endTime = endTime;
    m_timestep = timestep;

}

QVector<double> CalcPlan::toTPS(QDateTime curr_time, QVector<double> posOrb,
                                QVector<double> posGBI)
{

    QVector<double> coord_gsc(6, 0);
    QVector<double> coord_gscp(6, 0);
    /*
     coord_gsc = ASDCoordConvertor::convAgescToGsc(posOrb, curr_time);
     coord_gscp = ASDCoordConvertor::convAgescToGsc(posOrb, curr_time);
     QVector<double> ASDCoordConvertor::convGscToTsc(coord_gsc,posGBI[0], posGBI[1], posGBI[2]);
     double lat, double lon, double h)

     posOrb=
     QVector<double> posGBIToAGS=

     double const WZ = 7.2921151467e-5;
     double alpha = WZ*t*60 + gsto;
     r_g[0] =  cos(alpha)*r[0] + sin(alpha)*r[1];
     r_g[1] = -sin(alpha)*r[0] + cos(alpha)*r[1];
     r_g[2] =  r[2];

     */
    return coord_gsc;
}
bool CalcPlan::iszoneOrb(QDateTime curr_time, QVector<double> posOrb,
                         QVector<double> posOrbfirst)
{
    bool to_return = false;


    return to_return;
}

bool CalcPlan::iszone(QDateTime curr_time, QVector<double> posOrb,
                      QVector<double> param, QVector<double> posGBI)
{
    bool to_returv = false;
    ASDCoordConvertor conv;
    //QVector<double> coord_tsc(6, 0);
    QVector<double> coord_scc(6, 0);
    //QVector<double> coord_gsc(6, 0);
    double Azim, Elev, r;
   double elmin =10*DEG_TO_RAD;
    // double elmin = param[0];
    // double elmax = M_PI/2.;
    // double azmin = 0;
    // double azmax = 2.*M_PI;
    //  double dist = (sqrt(posOrb[0]*posOrb[0]+posOrb[1]*posOrb[1]+posOrb[2]*posOrb[2])-6371.)/sin(elmin);
   // qApp->processEvents();
   // QDateTime curr_time1;
   // curr_time1 = curr_time;
    posGBI[2] = 0;

    //coord_scc = ASDCoordConvertor::convGscToSsc(
    //		ASDCoordConvertor::convAgescToGsc(posOrb, curr_time1), posGBI[0],
    //		posGBI[1], posGBI[2]);
    coord_scc = conv.convGscToSsc(conv.convAgescToGsc(posOrb,curr_time),posGBI[0],posGBI[1],0.0);
    if (coord_scc[1] > -100)
    {


        r = pow(coord_scc[0] * coord_scc[0] + coord_scc[1] * coord_scc[1]
                + coord_scc[2] * coord_scc[2], 0.5);
        Elev = conv.angle(coord_scc[1] / r, pow(coord_scc[0] * coord_scc[0]
                + coord_scc[2] * coord_scc[2], 0.5) / r);
        Azim= conv.angle(coord_scc[2]/ pow(coord_scc[0] * coord_scc[0]+ coord_scc[2] * coord_scc[2], 0.5),
                coord_scc[0]/ pow(coord_scc[0] * coord_scc[0]+ coord_scc[2] * coord_scc[2], 0.5));
        if(Elev>M_PI)
            Elev = 2*M_PI-Elev;

        if ((Azim) < 0)
            Azim += 2 * M_PI;


        if(elmin < Elev)
        {
ell=Elev;
            to_returv = true;
            return to_returv;
        }
        else
        {
            return false;
        }
    }

    return to_returv;
}

//

void CalcPlan::setfilName(QString sfil)
{
    m_fil=sfil;
}
void CalcPlan::getPlanf()
{

//QFile fil(m_fil);
//fil.open(QFile::WriteOnly);
//fil.open(QIODevice::WriteOnly | QIODevice::Unbuffered);

      //QDataStream out(&fil);


    int i = 0; // номер КА
    int j = 0; // номер средства

 t_plan plans;
    int dtp = (int) (100 / m_orbitalVehicle.size());
    //	qDebug() << "dtp=" << dtp;
    for (i = 0; i < m_orbitalVehicle.size(); i++)
    {
       // prgrun.setValue((i + 1) * dtp - 1);
        int pii=(i + 1) * dtp - 1;
      // emit progress(pii);
        //connect(this,valueChang(25),&prgrun);
       // qApp->processEvents();
       // QMap<int, t_plan> t_seans;
        sumf=0.;
        sumtr=0.;
        for (j = 0; j < m_eathVehicle.size(); j++)
        {
            QDateTime currtime = m_startTime;
            ASDOrbitalObjectPar posorb = m_orbitalVehicle.at(i);
            ParamGrBaseInter posBGI = m_eathVehicle.at(j);
            QDateTime aos;
            QDateTime los;
            //qDebug()<<"kep i l="<<posorb.kep.i<<posorb.kep.l;
            posorb.kep.i *= DEG_TO_RAD;
            posorb.kep.l *= DEG_TO_RAD;
            posorb.kep.omega *= DEG_TO_RAD;
            posorb.kep.u *= DEG_TO_RAD;
            //  t_seans.clear();
            while (currtime < m_endTime)
            {

                //  qDebug()<<"aos======"<<currtime;
                plans = search_AOS_LOS(currtime, posorb, posBGI, aos, los);
                //   qDebug()<<"aos======"<<currtime<<plans.begin_s<<plans.end_s;
                //  my_plan.begin_s=aos;
                //   my_plan.end_s=los;
                if (abs(plans.begin_s.secsTo(plans.end_s)) >=0)
                {

                    qint64 secs=plans.begin_s.secsTo(plans.end_s);
                    qint64 secn=m_startTime.secsTo(plans.begin_s);
                  //  out<<(qint32)i+1<<(qint32)j+1<<(qint64)secn<<(qint64)secs;
                    //	int d_t = currtime.secsTo(plans.end_s);
                    // int d_t1=currtime.secsTo(m_endTime);
                    // if(abs(d_t1)<60*60)
                    {
                        currtime = plans.end_s.addSecs(60 * 60);
                        // qDebug()<<"aosusll======"<<currtime<<plans.begin_s<<plans.end_s<<d_t;
                        //tMap.insertMulti(i+1,t_seans);
                    }
                    // else
                    // {
                    // currtime=QDateTime(m_endTime);
                    // }

                }
                else
                {
                    // qDebug()<<"end;;;="<<currtime<<plans.begin_s<<plans.end_s;
                    currtime = QDateTime(m_endTime);
                }

            }
        }

    }
    //fil.close();
}
QMap<int, mapTime_plan> CalcPlan::getPlan()
{

//QFile fil("sttr.dat");
//fil.open(QFile::WriteOnly);
//fil.open(QIODevice::WriteOnly | QIODevice::Unbuffered);

     // QDataStream out(&fil);

    QMap<int, mapTime_plan> tMap;
//    CProgressBar prgrun;
//    prgrun.show();
//    prgrun.setValue(1);
//    prgrun.setText(QObject::trUtf8("Составление расписания доступности ..."));
    //connect(this,valueChang(25),&prgrun);
    //qApp->processEvents();
    int i = 0; // номер КА
    int j = 0; // номер средства


    int dtp = (int) (100 / m_orbitalVehicle.size());
    //	qDebug() << "dtp=" << dtp;
    QDateTime currtime;
     QMap<int, t_plan> t_seans;
       t_plan plans;
       QDateTime aos;
       QDateTime los;
    for (i = 0; i < m_orbitalVehicle.size(); i++)
    {
       // prgrun.setValue((i + 1) * dtp - 1);
        int pii=(i + 1) * dtp - 1;
       emit progress(pii);
        //connect(this,valueChang(25),&prgrun);
       // qApp->processEvents();

        sumf=0.;
        sumtr=0.;
        t_seans.clear();
        for (j = 0; j < m_eathVehicle.size(); j++)
        {
             currtime = m_startTime;
            //ASDOrbitalObjectPar posorb = m_orbitalVehicle.at(i);
          //  ParamGrBaseInter posBGI = m_eathVehicle.at(j);

            //qDebug()<<"kep i l="<<posorb.kep.i<<posorb.kep.l;
            m_orbitalVehicle[i].kep.i *= DEG_TO_RAD;
            m_orbitalVehicle[i].kep.l *= DEG_TO_RAD;
            m_orbitalVehicle[i].kep.omega *= DEG_TO_RAD;
            m_orbitalVehicle[i].kep.u *= DEG_TO_RAD;
            //  t_seans.clear();
            while (currtime < m_endTime)
            {

                //  qDebug()<<"aos======"<<currtime;
                plans = search_AOS_LOS(currtime,  m_orbitalVehicle[i], m_eathVehicle.at(j), aos, los);
                //   qDebug()<<"aos======"<<currtime<<plans.begin_s<<plans.end_s;
                //  my_plan.begin_s=aos;
                //   my_plan.end_s=los;
                if (abs(plans.begin_s.secsTo(plans.end_s)) >=0)
                {
                    t_seans.insertMulti(j + 1, plans);
                  //  qint64 secs=plans.begin_s.secsTo(plans.end_s);
                 //   qint64 secn=m_startTime.secsTo(plans.begin_s);
                 //   out<<(qint32)i+1<<(qint32)j+1<<(qint64)secn<<(qint64)secs;
                    //	int d_t = currtime.secsTo(plans.end_s);
                    // int d_t1=currtime.secsTo(m_endTime);
                    // if(abs(d_t1)<60*60)
                    {
                        currtime = plans.end_s.addSecs(60 * 60);
                        // qDebug()<<"aosusll======"<<currtime<<plans.begin_s<<plans.end_s<<d_t;
                        //tMap.insertMulti(i+1,t_seans);
                    }
                    // else
                    // {
                    // currtime=QDateTime(m_endTime);
                    // }

                }
                else
                {
                    // qDebug()<<"end;;;="<<currtime<<plans.begin_s<<plans.end_s;
                    currtime = QDateTime(m_endTime);
                }

            }
//            if (t_seans.size() > 0)
//                tMap.insertMulti(i + 1, t_seans);
//            t_seans.clear();
        }

        tMap.insertMulti(i+1,t_seans);

    }
   // prgrun.close();
    // sumf=0.;
    //  sumtr=0.;
   // fil.close();
    t_seans.clear();
    qDebug()<<"ressss="<<tMap.size()<<t_seans.size();
    return tMap;
}
//

// функция расчета координат

//int func (double t, const double y[], double f[],void *params)
//{
//    (void)(t); /* avoid unused parameter warning */
//    //double mu = *(double *)params;
//    //f[0] = y[1];
//    //f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);

//    //

//    double r;


//    // радиус;
//    r = pow(pow(y[0], 2) + pow(y[1], 2) + pow(y[2], 2), 0.5);

//    f[0] = y[3];
//    f[1] = y[4];
//    f[2] = y[5];

//    f[3] = -K_EARTH / pow(r, 3) * y[0] - 1.5 * K2_EARTH / pow(r,
//                                                              4) * (5 * pow(y[2] / r, 2) - 1) * y[0] / r;
//    f[4] = -K_EARTH / pow(r, 3) * y[1] - 1.5 * K2_EARTH / pow(r,
//                                                              4) * (5 * pow(y[2] / r, 2) - 1) * y[1] / r;
//    f[5] = -K_EARTH / pow(r, 3) * y[2] - 1.5 * K2_EARTH / pow(r,
//                                                              4) * (5 * pow(y[2] / r, 2) - 3) * y[2] / r;



//    return GSL_SUCCESS;
//}


// функция установка матрицы
//int jac (double t, const double y[], double *dfdy,double dfdt[], void *params)
//{
//    (void)(t); /* avoid unused parameter warning */
//    double mu = *(double *)params;
//    //gsl_matrix_view dfdy_mat
//    //= gsl_matrix_view_array (dfdy, 2, 2);
//    //gsl_matrix * m = &dfdy_mat.matrix;
//    //gsl_matrix_set (m, 0, 0, 0.0);
//    //gsl_matrix_set (m, 0, 1, 1.0);
//    //gsl_matrix_set (m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
//    //gsl_matrix_set (m, 1, 1, -mu*(y[0]*y[0] - 1.0));
//    //dfdt[0] = 0.0;
//    //dfdt[1] = 0.0;
//    gsl_matrix_view dfdy_mat= gsl_matrix_view_array (dfdy, 6, 6);
//    gsl_matrix * m = &dfdy_mat.matrix;
//    //0
//    gsl_matrix_set (m, 0, 0, 0.0);
//    gsl_matrix_set (m, 0, 1, 0.0);
//    gsl_matrix_set (m, 0, 2, 0.0);
//    gsl_matrix_set (m, 0, 3, 1.0);
//    gsl_matrix_set (m, 0, 4, 0.0);
//    gsl_matrix_set (m, 0, 5, 1.0);


//    //1
//    gsl_matrix_set (m, 1, 0, 0.0);
//    gsl_matrix_set (m, 1, 1, 0.0);
//    gsl_matrix_set (m, 1, 2, 0.0);
//    gsl_matrix_set (m, 1, 3, 1.0);
//    gsl_matrix_set (m, 1, 4, 0.0);
//    gsl_matrix_set (m, 1, 5, 1.0);

//    //2
//    gsl_matrix_set (m, 2, 0, 0.0);
//    gsl_matrix_set (m, 2, 1, 0.0);
//    gsl_matrix_set (m, 2, 2, 0.0);
//    gsl_matrix_set (m, 2, 3, 1.0);
//    gsl_matrix_set (m, 2, 4, 0.0);
//    gsl_matrix_set (m, 2, 5, 1.0);

//    //3
//    gsl_matrix_set (m, 3, 0, 0.0);
//    gsl_matrix_set (m, 3, 1, 0.0);
//    gsl_matrix_set (m, 3, 2, 0.0);
//    gsl_matrix_set (m, 3, 3, 1.0);
//    gsl_matrix_set (m, 3, 4, 0.0);
//    gsl_matrix_set (m, 3, 5, 1.0);

//    //4
//    gsl_matrix_set (m, 4, 0, 0.0);
//    gsl_matrix_set (m, 4, 1, 0.0);
//    gsl_matrix_set (m, 4, 2, 0.0);
//    gsl_matrix_set (m, 4, 3, 1.0);
//    gsl_matrix_set (m, 4, 4, 0.0);
//    gsl_matrix_set (m, 4, 5, 1.0);

//    //5
//    gsl_matrix_set (m, 5, 0, 0.0);
//    gsl_matrix_set (m, 5, 1, 0.0);
//    gsl_matrix_set (m, 5, 2, 0.0);
//    gsl_matrix_set (m, 5, 3, 1.0);
//    gsl_matrix_set (m, 5, 4, 0.0);
//    gsl_matrix_set (m, 5, 5, 1.0);
//    //



//    //  gsl_matrix_set (m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
//    // gsl_matrix_set (m, 1, 1, -mu*(y[0]*y[0] - 1.0));
//    dfdt[0] = 0.0;
//    dfdt[1] = 0.0;
//    dfdt[2] = 0.0;
//    dfdt[3] = 0.0;
//    dfdt[4] = 0.0;
//    dfdt[5] = 0.0;

//    return GSL_SUCCESS;
//}



/*!
 * \brief Поиск моментов времени AOS и LOS
 * \param startTime Время, прошедшее с TLE эпохи, с которого будут начаты вычисления, в секундах
 * \param site Местоположение на земле, относительно которого вычисляется положение спутника
 * \param aos, los - Следующее после startTime моменты времени AOS и LOS, в секундах с TLE эпохи
 * \param threshold - Пороговое значения для угла места (минимальный угол), в радианах
 */

t_plan CalcPlan::search_AOS_LOS(QDateTime startTime, ASDOrbitalObjectPar obj,
                                ParamGrBaseInter posBGI, QDateTime aos, QDateTime los)

{

    bool viz;
qApp->processEvents();
  //  QVector<t_plan> t_timeVisibility;
    t_plan plans;
    t_plan planse;
    QDateTime curr_time0 = startTime;
    aos = m_endTime.addDays(1);
    los = m_endTime.addDays(1);
    planse.begin_s = m_endTime;
    planse.end_s = m_endTime;
    viz = false;
    QVector<double> pos(6);
    ASDOrbitalMotion OrbitMotion;
    QVector<double> posGBIv;
    posGBIv.resize(3);
    QVector<double> param;
    param.resize(5);
     bool tozon =false;

    // qDebug()<<"aaaaaaa===="<<startTime<<curr_time0<<m_endTime;
    while (curr_time0 < m_endTime)
    {


        if (obj.type_dat == 0)

        {

            OrbitMotion.setBeginParam(obj.kep);
            OrbitMotion.setIntegrateParam(0);

        }
        if (obj.type_dat == 1)
        {
            obj.forcedan.grvModel = 0;
            OrbitMotion.setBeginParam(obj.ags);
            OrbitMotion.setEquationOfParam(obj.forcedan);
            OrbitMotion.setIntegrateParam(1);

        }
        if (obj.type_dat == 2)
        {
            OrbitMotion.setBeginParam(obj.stle);
            OrbitMotion.setIntegrateParam(2);

        }

        pos = OrbitMotion.getPosition(curr_time0);






        param[0] = posBGI.minelev * DEG_TO_RAD;
        param[1] = posBGI.maxelev * DEG_TO_RAD;
        param[2] = posBGI.minaz * DEG_TO_RAD;
        param[3] = posBGI.maxaz * DEG_TO_RAD;
        param[4] = posBGI.maxdist;

        posGBIv[0] = posBGI.point.lat * DEG_TO_RAD;
        posGBIv[1] = posBGI.point.lon * DEG_TO_RAD;
        posGBIv[2] = 0.;		//objGBI.point.h;
         tozon = iszone(curr_time0, pos, param, posGBIv);

        if (tozon)
        {
            if (viz == false)
            {

                aos = curr_time0;
              //  qDebug()<<"1 v="<<ell*RAD_TO_DEG<<udal*RAD_TO_DEG<< posBGI.minelev;
                plans.begin_s = curr_time0;
                // t_timeVisibility.append(plans);
                viz = true;
                //curr_time0=curr_time0.addSecs(1);

            }
            curr_time0 = curr_time0.addSecs(15);

        }
        else
        {
            if (viz == true)
            {
                los = curr_time0;
                // qDebug()<<"tz=return"<<curr_time0<<aos<<los;
                plans.end_s = curr_time0;
                //t_timeVisibility.append(plans);
                return plans;

            }
            curr_time0 = curr_time0.addSecs(35);


        }
        curr_time0=curr_time0.addSecs(15);
        // qDebug()<<"tz=qqqqq"<<curr_time0<<aos<<los;

    }
    if(viz==true)
      {
        planse.begin_s = startTime;
        planse.end_s = curr_time0;
      }
    // qDebug()<<"t_timeVisibility="<<t_timeVisibility.size();
    return planse;
}






void CalcPlan::SolarPosition(int doy, double hod, double& lat, double& lon)
{
    //double DEG_TO_RAD = 1.7453292519943e-2;
    //double RAD_TO_DEG = 57.295779513082;

    lat = sin(23.5*DEG_TO_RAD)*sin(2.*M_PI*double(doy-83)/365.25);
    lat = lat / ::sqrt(1.0-lat*lat);
    lat = RAD_TO_DEG*atan(lat);
    lon = 180.0 - hod*15.0;
    return;
}
//void CalcPlan::Sunrise(double lat, double lon, double ht, int doy, double& rise, double& sets)

//{
//    //double DEG_TO_RAD = 1.7453292519943e-2;
//    // double RAD_TO_DEG = 57.295779513082;

//    const double DEG_TO_HRS=(24.0/360.0); // should this be sidereal day?
//    double sunlat,sunlon,hod;

//    // find the position of the sun
//    hod = 0;
//    SolarPosition(doy, hod, sunlat, sunlon);

//    double x = -1 * tan(sunlat*DEG_TO_RAD) * tan(lat*DEG_TO_RAD);
//    if(x <= -1.0 || x >= 1.0) {
//        rise = sets = -999;
//        return;
//    }
//    x = acos(x) * RAD_TO_DEG;

//    rise = DEG_TO_HRS * (sunlon - lon - x);
//    sets  = DEG_TO_HRS * (sunlon - lon + x);

//    // adjust for height above sea level
//    double dht=0,radius=6371000.;
//    dht = 24.0*acos(radius/(radius+ht))/(2.*M_PI);
//    rise -= dht;
//    sets += dht;

//    while(rise <  0) rise += 24;
//    while(rise >= 24) rise -= 24;
//    while(sets <  0) sets += 24;
//    while(sets >= 24) sets -= 24;
//    return;

//}

/* norad const*/

/*
 int peri=(int)(2*M_PI*sqrt(eci2.pos.r*eci2.pos.r*eci2.pos.r/398600.44));
 tmp=nac_vr;
 //qDebug() <<"pri="<<peri<<"vr="<<tmp.toString("dd.MM.yyyy-hh:mm:ss");
 ras1:orbit_grup->search_AOS_LOS( tmp, recv,eci2,
 aos,  los, 0.);

 //qDebug() << "aos="<<aos.toAscii()<<"los="<<los.toAscii()<<"ttttt="<<tmp.toString("dd.MM.yyyy-hh:mm:ss");
 str=(punkt_grup->list_punkt.at(j).koord.name)+"  "+
 orbit_grup->list_ka.at(i).name+"начало "+aos+" окончание "+los;
 seans.append(str.toLocal8Bit());


 //qDebug() << c1->toUnicode(str);
 if(tmp<con_vr)
 {
 tmp=tmp.addSecs(peri-600);
 goto ras1;
 }
 */


//**************************** 04.12.2010 *********************************//
//
//                  Пересечение отрезка и шара
//
//**************************** 04.12.2010 *********************************//
/*
Def<Segment3d> intersection ( const Segment3d & seg, const Sphere3d & sphere )
{
    Def<Segment3d> res;
    const Vector3d u = sphere.o - seg.a;
    const Vector3d v = seg.b - seg.a;
    const double a = v * v;
    const double b = v * u;
    const double c = u * u - sphere.r * sphere.r;
    if ( a == 0 )
    {
        return c > 0 ? res : seg;
    }
    double d = b * b - a * c;
    if ( d < 0 ) return res;
    d = sqrt ( d );
    const double t1 = ( b - d ) / a;
    if ( t1 > 1 ) return res;
    const double t2 = ( b + d ) / a;
    if ( t2 < 0 ) return res;
    res.a = t1 > 0 ? seg.a + t1 * v : seg.a;
    res.b = t2 < 1 ? seg.a + t2 * v : seg.b;
    res.isDef = true;
    return res;
}
*/
