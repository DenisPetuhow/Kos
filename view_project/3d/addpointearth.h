#ifndef ADDPOINTEARTH_H
#define ADDPOINTEARTH_H

#include "object3d.h"
#include "interlocation/interlocation.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"
#include "osg/Billboard"

class addPointEarth : public ASDObject3D
{
public:
    addPointEarth(SGroundVeh point, QString icon);
    void repaint(QDateTime time, ASDScene3D* scene);
    bool remove(ASDScene3D* scene);

    bool m_create_object;
   static osg::ref_ptr<osg::Group> m_point;
protected:
    SGroundVeh m_p;
    QString m_icon;
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::MatrixTransform> m_transform2;

};

#endif // ADDPOINTEARTH_H
