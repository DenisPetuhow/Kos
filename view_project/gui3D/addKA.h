#ifndef ADDKA_H
#define ADDKA_H
#include "object3d.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"
#include "vehicle/orbitalvehicle.h"
class addKA : public ASDObject3D, ASDPositionObj
{
public:
     addKA(ASDOrbitalVehicle ka, ASDOrbitalObjectPar par);

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

#endif // ADDKA_H
