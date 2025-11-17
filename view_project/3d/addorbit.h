#ifndef ADDORBIT_H
#define ADDORBIT_H


#include "object3d.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"
#include "vehicle/orbitalvehicle.h"
class addOrbit : public ASDObject3D, ASDPositionObj
{

public:
    addOrbit(ASDOrbitalVehicle ka);
  //  static osg::ref_ptr<osg::MatrixTransform> m_orb;

    bool m_create_object;


    bool m_create_object_NO;

    void repaint(QDateTime time, ASDScene3D * scene);

    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::MatrixTransform> m_orb ;
    ASDOrbitalVehicle m_ka;

    double omega_old;



};


#endif // ADDORBIT_H
