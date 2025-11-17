#ifndef CPAINT3D_H
#define CPAINT3D_H
#include "ASD/asdtype.h"
#include "ASD/orbitalmotion.h"
#include "ASD/orbitalvehicle.h"
#include "gui3D/scene3d.h"
#include "gui3D/orbitveh3d.h"
#include "gui3D/addpointearth.h"
#include "gui3D/addpointmoon.h"
#include "gui3D/addcone.h"
#include "gui3D/addline.h"
#include "gui3D/addpyramid.h"
#include "gui3D/moonorbitveh3d.h"
#include "gui3D/addorbit.h"
#include "gui3D/adddostup.h"
#include "gui3D/addzonaobz.h"
#include "gui3D/add_bpla.h"
#include "calc_bpla_plan.h"

class CPaint3D
{
public:
    CPaint3D();



    void setPlan(QVector<ASDZoneVisible> zone);


    void setKa(QVector<ASDOrbitalObjectPar> ka);
    void setBpLA(QVector<ASD_bpla_struct> _bpla);
    void setOkik(QVector<ParamGrContrCentr> okik);
    void setzonobz( QMap<QDateTime,  QPolygonF>  kazon);
    void setCoordKA(  QVector<QMap <QDateTime, QVector<double> > > coord_ka);
    void setBox(QVector<Paramregion> region);
    void setTime(QDateTime time_begin, QDateTime time_end);
    void set3D(ASDScene3D* page);
    void setpointreg(QVector<ParamregionO> region,QMap<QDateTime,  ASDZoneVisible> mapP);
    void calc();
    void calc_bpla();

    void repaint(QDateTime time);

    void paintAirCraft(QDateTime time);

    void removeObject(QDateTime time);
    void clear();

private:
    QVector<ASDZoneVisible> m_zone;
    QVector<ParamGrBaseInter> m_kinetic; // кинетическое средство
    QVector<ParamGrBaseInter> m_laser; // лазерное средство
    QVector<Paramregion> m_region;
    QVector<ParamGrContrCentr> m_okik;
    QVector<ASDOrbitalObjectPar> m_ka;
    QVector<ASD_bpla_struct> m_BpLA; //  БПЛА
    QVector<ASDOrbitalMotion> OrbitMotion;
    QDateTime m_time_begin;
    QDateTime m_time_end;
    ASDScene3D* m_page;
    osg::ref_ptr<addPointEarth> Point;
    QVector<QMap <QDateTime, QVector<double> > > m_coord_ka;
    QMap<QDateTime,osg::ref_ptr<ASDObject3D> > m_object;
    QVector<ParamregionO> m_regionp;
    QMap<QDateTime,  ASDZoneVisible> m_mapP;
    QMap<QDateTime,  QPolygonF>  m_kazon;
    QDateTime Curtime;

};

#endif // CPAINT3D_H
