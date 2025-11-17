#ifndef ADDORBIT_H
#define ADDORBIT_H


#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
class addOrbit : public ASDObject3D, ASDPositionObj
{

public:
    addOrbit(ASDOrbitalVehicle ka);
    static osg::ref_ptr<osg::MatrixTransform> m_orb;

    bool m_create_object;


    bool m_create_object_NO;

    void repaint(QDateTime time, ASDScene3D * scene);

    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    ASDOrbitalVehicle m_ka;


};


#endif // ADDORBIT_H
