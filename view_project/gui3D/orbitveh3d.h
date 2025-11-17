#ifndef ASDORBITVEH3D_H
#define ASDORBITVEH3D_H
#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
class ASDOrbitVeh3D : public ASDObject3D, ASDPositionObj
{
public:
    ASDOrbitVeh3D(ASDOrbitalVehicle ka, ASDOrbitalObjectPar par);

    void repaint(QDateTime time, ASDScene3D * scene);
    bool remove(ASDScene3D* scene);
    static osg::ref_ptr<osg::MatrixTransform> m_model3d; //адрес формы объекта
    bool m_create_object;

protected:

    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::MatrixTransform> m_transform2;

    ASDOrbitalVehicle m_ka;
    ASDOrbitalObjectPar m_par;
    osg::AnimationPath* animationPath;
    ASDScene3D *m_scene;


};


#endif // ASDORBITVEH3D_H
