#ifndef ADDLINE_H
#define ADDLINE_H

#include "object3d.h"
//#include "obzor.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"

class addLineKP : public ASDObject3D, ASDPositionObj
{
public:
    addLineKP(ASDZoneVisible mapOCP, ASDOrbitalVehicle ka, SGroundVeh Veh);
    addLineKP(ASDZoneVisible mapOCP, QMap<QDateTime, QVector<double> > ka_coord, SGroundVeh Veh);
    void repaint(QDateTime time, ASDScene3D * scene);
    osg::ref_ptr<osg::Geode> g_line;

    bool remove(ASDScene3D* scene);

protected:
    ASDOrbitalVehicle m_ka;
    QMap<QDateTime, QVector<double> > m_ka_coord;
    SGroundVeh m_point;
    ASDZoneVisible m_map;
    bool m_create;
    bool m_create_no;

    int init;


};


#endif // ADDLINE_H
