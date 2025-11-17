#ifndef ADDSPHERESEGMENT_H
#define ADDSPHERESEGMENT_H

#include "object3d.h"
#include "interlocation/interlocation.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"
#include "osg/Billboard"

class addSphereSegment : public ASDObject3D
{
public:
    addSphereSegment(ParamZone zone);
    void repaint(QDateTime time, ASDScene3D* scene);
    bool remove(ASDScene3D* scene);

    bool m_create_object;
   static osg::ref_ptr<osg::Group> m_point;
protected:
    ParamZone m_zone;
    osg::ref_ptr<osg::MatrixTransform> m_transform;


};

#endif // ADDSPHERESEGMENT_H
