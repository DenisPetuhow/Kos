#ifndef ADDZONAOBZ_H
#define ADDZONAOBZ_H

#include "object3d.h"
//#include "obzor.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"

class addzonaobz : public ASDObject3D, ASDPositionObj
{
public:
        addzonaobz(QMap<QDateTime,  QPolygonF> mapP);

        void repaint(QDateTime time, ASDScene3D * scene);
        bool remove(ASDScene3D* scene);
        bool m_create_object;
        bool m_create_object_NO;
        protected:
        osg::ref_ptr<osg::MatrixTransform> m_transform;
         osg::ref_ptr<osg::MatrixTransform> m_transform2;
        QMap<QDateTime,  QPolygonF>  m_kazon;


};



#endif // ADDZONAOBZ_H
