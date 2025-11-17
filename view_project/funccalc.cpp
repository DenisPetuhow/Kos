#include "funccalc.h"
#include "ASD/SunPosition.hpp"
#include <QDebug>
QMap<QDateTime, int> SortPlan(QMap<int, mapTime_plan> plan, QVector<Paramregion> reg,QDateTime m_begTime ,QDateTime m_endTime ,double elevSun)
{
    QMap<int, double> t_per;
    QMap<QDateTime, int> return_rez;
    QMap<int, t_plan> tseans;
    SunPosition sun;
    
    QDateTime time;
    double Elev_sun;

    QMap<int, mapTime_plan>::Iterator it3 = plan.begin();
    for (; it3 != plan.end(); ++it3)
    {
        tseans = it3.value();

        QMap<int, t_plan>::Iterator it2 = tseans.begin();
        for (; it2 != tseans.end(); ++it2)
        {
            t_plan dts = it2.value();

            t_per.insertMulti(it2.key(), m_begTime.secsTo(dts.begin_s) / 3600.);
        }
    }//



    for (int jk = 0; jk < reg.size(); ++jk)
    {

        QList<double> per;
        QMap<int, double>::Iterator itp= t_per.find(jk);
        while(itp !=t_per.end()&&(itp.key() == jk))

        {

            per.append(itp.value());
            ++itp;
        }
        // sort
        double per_s=0.;
        if (per.size() > 1)
        {
            qSort(per.begin(), per.end());

            QList<double>::iterator p,p_e;
           // qDebug()<<"test per size old="<< per.size();
            p_e=per.end();
            p = per.begin();
            //        for (p = per.begin(); p != p_e; p++)
            while(p!=p_e)

                //for(int jj=0;jj<per.size();++jj)
            {
                double par = *p;

                time = m_begTime.addSecs((int)(par*3600));
                QVector <double> sun_coord = sun.getPosition(time); //  в АГЭСК
                QVector <double> sun_gsc = ASDCoordConvertor::convAgescToGsc(sun_coord,time.addSecs(10800));
                QVector <double> sun_start = ASDCoordConvertor::convGscToSsc(sun_gsc,reg[jk].maxlat*DEG_TO_RAD,reg[jk].maxlong*DEG_TO_RAD,0);
                double r_sun = pow(sun_start[0] * sun_start[0] + sun_start[1] * sun_start[1]
                        + sun_start[2] * sun_start[2], 0.5);
               // qDebug()<<"sun time= "<<time<<"sun el="<<Elev_sun*RAD_TO_DEG<<elevSun<<par<<per.at(per.size()-1)<<"size="<<per.size();
                if(sun_start[1]>-2000) //Если солнце над горизонтом
                {
                    Elev_sun = asin(sun_start[1] / r_sun);
                    if(Elev_sun>M_PI)
                        Elev_sun = 2*M_PI-Elev_sun;

                    if(Elev_sun<elevSun*DEG_TO_RAD)
                    {// проверка сколько градусов солнце над горизонтом.)
                        qDebug()<<"del--evvvvvv"<<par<<time<<Elev_sun*RAD_TO_DEG;
                        if( per.contains(par)) per.erase(p);
                        p_e=per.end();
                    }
                    //del

                }
                else
                {
                   // qDebug()<<"del--"<<par<<time<<Elev_sun*RAD_TO_DEG;
                    if( per.contains(par))
                    {
                        per.erase(p);

                    }
                }

                p_e=per.end();
                if(p<p_e) ++p;
            }
            per_s += per.at(0);
            qDebug()<<"test per size new="<< per.size();
            QDateTime timp= m_begTime.addSecs((int)(per.at(0)*3600));
            return_rez.insert(timp,jk);
            for (int i = 1; i < per.size(); ++i)
            {
                timp= m_begTime.addSecs((int)(per.at(i)*3600));
                return_rez.insert(timp,jk);
                per_s += per.at(i) - per.at(i - 1);
            }
            per_s /= per.size();
           // qDebug()<<"reg="<<reg.at(jk).name<<"per sun="<<per_s;

        }

    }//end for region


    // end Периодичность наблюдения


    return return_rez;

}









