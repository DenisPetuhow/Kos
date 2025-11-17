#ifndef CALC_BPLA_PLAN_H
#define CALC_BPLA_PLAN_H
#include "ASD/asdtype.h"
#include "QPointF"
#include <QFile>
#include <QObject>
#include <QCoreApplication>
#include "math.h"
#include "qdebug.h"
#include "ASD/asdcoordconvertor.h"
#include "ASD/orbitalvehicle.h"

struct t_plan_bpla
{
    QDateTime time;
    ASDOrbitalObjectPar KA;


};

class Calc_bpla_plan
{


public:
    explicit Calc_bpla_plan();
    ~Calc_bpla_plan();

    QString m_fil;
    void set_BpLA(ASD_bpla_struct _BpLA);
    void set_KA(QVector<ASDOrbitalObjectPar> _vecOrb);
    QVector<double> getPos_BpLA(QDateTime dt,ASD_bpla_struct _BpLA);
    QPointF coordpoint2(QPointF p,double D1,double A1);
    double get_azimuth(const double lat1, const double lon1, const double lat2, const double lon2);
    void mainCalc_BpLA();
    bool iszone(QDateTime curr_time, QVector<double> posOrb, QVector<double> posGBI);
    QMap<int, t_plan_bpla> mapBpLA_KA;
    QMap<int, t_plan_bpla> get_BpLA();
    QVector<ASD_bpla_struct> vec_BpLA;
    QVector<ASDOrbitalObjectPar> vec_Orb;

    double ell;
    QStringList result_list;
    QVector<QVector <double> > result_vec;

    QVector<QVector <double> >  get_result(){
        return result_vec;
    }
    QStringList get_result_list(){
        return result_list;
    }

    double calc_length(ASD_bpla_struct _BpLA);




};

#endif // CALC_BPLA_PLAN_H
