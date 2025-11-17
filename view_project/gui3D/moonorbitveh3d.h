#ifndef ASDMOONORBITVEH3D_H
#define ASDMOONORBITVEH3D_H
#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
#include "QMap"
class ASDMoonOrbitVeh3D : public ASDObject3D, ASDPositionObj
{
public:
     ASDMoonOrbitVeh3D(QMap<QDateTime, QVector<double> > coord_agsk);

    void repaint(QDateTime time, ASDScene3D * scene);
    bool remove(ASDScene3D* scene);
    static osg::ref_ptr<osg::MatrixTransform> m_model3d; //адрес формы объекта
    bool m_create_object;

protected:

    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::MatrixTransform> m_transform2;
    QDateTime m_time;
ASDOrbitalVehicle m_ka;
ASDOrbitalObjectPar m_par;
osg::AnimationPath* animationPath;
ASDScene3D *m_scene;
QMap<QDateTime, QVector<double> > m_coord_agsk;


};

#endif // ASDORBITVEH3D_H
