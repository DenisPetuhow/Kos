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

    // Высота полета БПЛА, км. Держать в синхроне с add_BPLA::BPLA_ALT_KM
    // (не включаем gui3D/add_bpla.h, чтобы расчетный модуль не зависел от OSG).
    static constexpr double BPLA_ALT_KM = 10.0;

    QString m_fil;
    void set_BpLA(ASD_bpla_struct _BpLA);
    void set_KA(QVector<ASDOrbitalObjectPar> _vecOrb);
    QVector<double> getPos_BpLA(QDateTime dt,ASD_bpla_struct _BpLA);
    QPointF coordpoint2(QPointF p,double D1,double A1);
    double get_azimuth(const double lat1, const double lon1, const double lat2, const double lon2);
    void mainCalc_BpLA();

    /*!
     * Проверка: находится ли БПЛА внутри конуса покрытия КА.
     * Геометрия ТА ЖЕ, что у зеленого конуса (addCone) и 3D-линий
     * (add_BPLA::isKaVisible): надирный угол между осью КА->надир и
     * вектором КА->БПЛА сравнивается с gamma.
     * \param posOrb   позиция КА в АГЭСК, км
     * \param posGBI   позиция БПЛА: [0]=lon°, [1]=lat°
     * \param gamma_deg угол полураствора конуса, градусы;
     *                  если <= 0 - берется геометрический максимум
     *                  asin(R/(R+h)) - 0.5° из фактической высоты КА
     */
    bool iszone(QDateTime curr_time, QVector<double> posOrb, QVector<double> posGBI,
                double gamma_deg = -1.0);
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
