#ifndef ADDCONE_H
#define ADDCONE_H

#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
class addCone : public ASDObject3D, ASDPositionObj
{

public:
    addCone(ASDOrbitalVehicle ka, ASDBsePar par,QMap<QDateTime,int> mapP);
    // Конус КАЖДОГО КА хранится в своем экземпляре (был static - все КА делили один указатель)
    osg::ref_ptr<osg::MatrixTransform> m_cone;
//void setzon(QMap<QDateTime,int> mapP);
    bool m_create_object;


    bool m_create_object_NO;

    void repaint(QDateTime time, ASDScene3D * scene);

    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    ASDOrbitalVehicle m_ka;
    ASDBsePar m_par;
    QMap<QDateTime,int> m_map;

};

#endif // ADDCONE_H
