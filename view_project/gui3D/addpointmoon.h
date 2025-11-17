#ifndef ADDPOINTMOON_H
#define ADDPOINTMOON_H

#include "object3d.h"
#include "ASD/interlocation.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "osg/Billboard"

class addpointMoon : public ASDObject3D
{
public:
    addpointMoon(SGroundVeh point, QString icon);
    void repaint(QDateTime time, ASDScene3D* scene);
    bool remove(ASDScene3D* scene);

    bool m_create_object;
   static osg::ref_ptr<osg::Group> m_point;
protected:
    SGroundVeh m_p;
    QString m_icon;
    osg::ref_ptr<osg::MatrixTransform> m_transformM;


};



#endif // ADDPOINTMOON_H
