#ifndef ADDDOSTUP_H
#define ADDDOSTUP_H

#include "object3d.h"
//#include "obzor.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"

class adddostup : public ASDObject3D, ASDPositionObj
{
public:
        adddostup(QMap<QDateTime,  ASDZoneVisible> mapP,ParamregionO point);

        void repaint(QDateTime time, ASDScene3D * scene);
        bool remove(ASDScene3D* scene);
        bool m_create_object;
        bool m_create_object_NO;
        protected:
        osg::ref_ptr<osg::MatrixTransform> m_transform;
         osg::ref_ptr<osg::MatrixTransform> m_transform2;
        QMap<QDateTime,  ASDZoneVisible>  m_kazon;
        ParamregionO m_reg;

};

#endif // ADDDOSTUP_H
