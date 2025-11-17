/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdorbitalvehicle.cpp.\n
 ** Описание: Содержит класс для инициализации орбитального средства.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "orbitalvehicle.h"

ASDOrbitalVehicle::ASDOrbitalVehicle()
{
    m_pOrbitMotion = new ASDOrbitalMotion();

    // m_initData=false;
    //    m_pOrbitMotion = 0;
    m_typeIntegrat = 0;// тип модели интегрирования
    //memset(&m_paramDescend, 0, sizeof(m_paramDescend));
    m_pMobileServZone = 0;
    m_plMobileServZone.clear();

    //m_ParamOrbitalObject;
    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)
    m_p.resize(0); // n динамические параметры
    m_vecDer.resize(6);

}
ASDOrbitalVehicle::ASDOrbitalVehicle(ASDOrbitalObjectPar obj)
{
    m_ParamOrbitalObject = obj;
    m_pOrbitMotion = new ASDOrbitalMotion();

    if (obj.type_dat == 0)
    {
        objInitTime = obj.kep.t_epoch;
        m_pOrbitMotion->setBeginParam(obj.kep);
        m_pOrbitMotion->setIntegrateParam(0);
    }
    if (obj.type_dat == 1)
    {
        objInitTime = obj.ags.t_epoch;
        m_pOrbitMotion->setBeginParam(obj.ags);
        m_pOrbitMotion->setIntegrateParam(1);
    }
    if (obj.type_dat == 2)
    {
        m_pOrbitMotion->setBeginParam(obj.stle);
        m_pOrbitMotion->setIntegrateParam(2);
        double jdate = m_pOrbitMotion->getMjd();
        int pYear, pMon;
        double pDOM;
        m_pOrbitMotion->GetDateJD(jdate, &pYear, &pMon /* = NULL */, &pDOM /* = NULL */);
        QDate dat;
        dat.setDate(pYear, pMon, (int) (pDOM));
        objInitTime.setDate(dat);
        QTime tim(0,0);
        int secs = (int) ((pDOM - (int) (pDOM)) * 86400);
        tim.addSecs(secs);
        objInitTime.setTime(tim);
        m_objCurrTime = objInitTime;
    }
    QVector<double> xx(6, 0.0);
    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)

    xx = m_pOrbitMotion->getPosition(0.);
    if(xx.size()==0)
    {m_r.clear();
        m_v.clear();

}else {

       m_r[0] = xx[0];
       m_r[1] = xx[1];
       m_r[2] = xx[2];
       m_v[0] = xx[3];
       m_v[1] = xx[4];
       m_v[2] = xx[5];

}

}

bool ASDOrbitalVehicle::setInitParam(ASDOrbitalObjectPar obj)
{
    m_ParamOrbitalObject = obj;
    if (obj.type_dat == 0)
    {
        objInitTime = obj.kep.t_epoch;
        m_pOrbitMotion->setBeginParam(obj.kep);
        m_pOrbitMotion->setIntegrateParam(0);
    }
    if (obj.type_dat == 1)
    {
        objInitTime = obj.ags.t_epoch;
        m_pOrbitMotion->setBeginParam(obj.ags);
        m_pOrbitMotion->setIntegrateParam(1);
    }
    if (obj.type_dat == 2)
    {
        m_pOrbitMotion->setBeginParam(obj.stle);
        m_pOrbitMotion->setIntegrateParam(2);
        double jdate = m_pOrbitMotion->getMjd();
        int pYear, pMon;
        double pDOM;
        m_pOrbitMotion->GetDateJD(jdate, &pYear, &pMon /* = NULL */, &pDOM /* = NULL */);
        QDate dat;
        dat.setDate(pYear, pMon, (int) (pDOM));
        objInitTime.setDate(dat);
        QTime tim(0,0);
        int secs = (int) ((pDOM - (int) (pDOM)) * 86400);
        tim.addSecs(secs);
        objInitTime.setTime(tim);
        m_objCurrTime = objInitTime;
    }
    QVector<double> xx(6, 0.0);
    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)
    xx = m_pOrbitMotion->getPosition(0.);
    m_r[0] = xx[0];
    m_r[1] = xx[1];
    m_r[2] = xx[2];
    m_v[0] = xx[3];
    m_v[1] = xx[4];
    m_v[2] = xx[5];

    // m_r.resize(3, 0.0); // Позиция(x,y,z)
    // m_v.resize(3, 0.0); // скорость(vx,vy,vz)
    int bsaSize = obj.bsa.size();
    m_plMobileServZone.clear();
    for (int i = 0; i < bsaSize; ++i)
    {
        m_pMobileServZone = new ASDMobileZone(obj.bsa.at(i).gamma,
                                              obj.bsa.at(i).pitch, obj.bsa.at(i).yaw);
        m_plMobileServZone.append(m_pMobileServZone);
    }

    m_p.resize(bsaSize); // n динамические параметры

    m_vecDer.resize(6);
    return true;
}

void ASDOrbitalVehicle::resetState()
{

    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)
    m_plMobileServZone.clear();
    m_p.resize(0); // n динамические параметры
    m_vecDer.resize(6);
}

bool ASDOrbitalVehicle::chekPointInMobZone(QVector<double> coordPoint,
                                           ASDMobileZone m_sone)
{

    QVector<double> t_coordPoint;
    if (coordPoint.size() < 3)
        return false;
    if (coordPoint.size() == 3)
    {
        t_coordPoint.resize(6);
        t_coordPoint[0] = coordPoint[0];
        t_coordPoint[1] = coordPoint[1];
        t_coordPoint[2] = coordPoint[2];
        t_coordPoint[3] = 0;
        t_coordPoint[4] = 0;
        t_coordPoint[5] = 0;
    }
    if (coordPoint.size() == 6)
    {
        t_coordPoint.resize(6);
        t_coordPoint[0] = coordPoint[0];
        t_coordPoint[1] = coordPoint[1];
        t_coordPoint[2] = coordPoint[2];
        t_coordPoint[3] = coordPoint[3];
        t_coordPoint[4] = coordPoint[4];
        t_coordPoint[5] = coordPoint[5];
    }

    //t_coordPoint = ASDCoordConvertor::convAgescToOscRelative(:convertToAgesc(t_coordPoint, m_objCurrTime, scPoint);
    QVector<double> xx;
    xx.append(m_r[0] * 1000);
    xx.append(m_r[1] * 1000);
    xx.append(m_r[2] * 1000);
    return true;
    //	return m_sone.isSpacecraftInZone(xx, t_coordPoint, m_objCurrTime);
    // // m_zone.isSpacecraftInArea(m_r,t_coordPoint,m_objCurrTime);


}
//void ASDOrbitalVehicle::setZoneParam(double gamma, double alfaMounting, double etaMounting)
//{

//}

//bool ASDOrbitalVehicle::addStillServZone(ASDStillZone szone)
//{
//    m_plStillServZone.append(&szone);
//    return true;

//}
bool ASDOrbitalVehicle::addMobileServZone(ASDMobileZone mzone)
{
    m_plMobileServZone.append(&mzone);
    return true;
}
bool ASDOrbitalVehicle::setDescend(const QDateTime tp, ASDDescendPar param)
{

}
QVector<double> ASDOrbitalVehicle::getDerivatives(QDateTime t)
{
    //m_vecDer.resize(6,true);

}
bool ASDOrbitalVehicle::setDerivatives(QVector<bool>& x)
{
    int vecSize = x.size();
    m_vecDer.resize(vecSize);
    for (int i = 0; i < vecSize; ++i)
    {
        if (x[i] == true)
            m_vecDer[i] = true;
        if (x[i] == false)
            m_vecDer[i] = false;
    }

}
QDateTime ASDOrbitalVehicle::getCurrTime()
{
    return m_objCurrTime;
}

QVector<double> ASDOrbitalVehicle::getCurrPos(QDateTime period,
                                              SystemCoord sc)
{
    QVector<double> xx(6, 0.0);
    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)
        xx = m_pOrbitMotion->getPosition(period);
        if(xx.size()==0)
        {m_r.clear();
            m_v.clear();
             QVector<double> x0(6, 0.0);
            return x0;

    }else {
        m_r[0] = xx[0];
        m_r[1] = xx[1];
        m_r[2] = xx[2];
        m_v[0] = xx[3];
        m_v[1] = xx[4];
        m_v[2] = xx[5];
        m_objCurrTime = period;
    ASDCoordConvertor con;
    QVector<double> pos;
    pos.append(m_r[0]);
    pos.append(m_r[1]);
    pos.append(m_r[2]);
    pos.append(m_v[0]);
    pos.append(m_v[1]);
    pos.append(m_v[2]);
    // objPosForecast(tfc, period, timeStep);
    switch (sc)
    {
    case AGESC:
        return m_r+m_v;
        break;
    case GSC:
    {
        QVector<double> pos_1 = con.convAgescToGsc(pos, m_objCurrTime);
        xx[0] = pos_1[0];
        xx[1] = pos_1[1];
        xx[2] = pos_1[2];
        m_r[0] = xx[0];
        m_r[1] = xx[1];
        m_r[2] = xx[2];

        return m_r+m_v;
        break;
    }
    case KepSC:
    {
        return ASDCoordConvertor::convAgescToKsc(m_r+m_v);
    }
        break;
    default:
    {
        //QMessageBox box;
        // box.about(0, QString::fromUtf8("Ошибка"), QString::fromUtf8(
        //       "Введена не корректная система координат"));
        return m_r+m_v; //! TODO должен возращать код ошибки
    }

    }
        }

}
int ASDOrbitalVehicle::setInitTime(QDateTime initTime)
{
    QVector<double> xx(6, 0.0);
    m_r.resize(3); // Позиция(x,y,z)
    m_v.resize(3); // скорость(vx,vy,vz)
    xx = m_pOrbitMotion->getPosition(initTime);
    m_r[0] = xx[0];
    m_r[1] = xx[1];
    m_r[2] = xx[2];
    m_v[0] = xx[3];
    m_v[1] = xx[4];
    m_v[2] = xx[5];
    m_objCurrTime = initTime;

}
//  int ASDOrbitalVehicle::setInitPos(libmath::Vector<double> coord, QDateTime initTime, SystemCoord sc)
//   {


//   }
