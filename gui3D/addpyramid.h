#ifndef ADDPYRAMID_H
#define ADDPYRAMID_H

#include "object3d.h"
#include "gui3D/vizibility.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
#include "osgUtil/SmoothingVisitor"

class addPyramid : public ASDObject3D, ASDPositionObj
{

public:
    addPyramid(ASDOrbitalVehicle ka, ASDBsePar par,QMap<QDateTime,int> mapP);

    void repaint(QDateTime time, ASDScene3D * scene);
    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::Group> m_pyr;
    ASDOrbitalVehicle m_ka;
    ASDBsePar m_par;
    bool m_create;
        bool m_create_no; //создавать ли объект
         QMap<QDateTime,int> m_map;

};


#endif // ADDPYRAMID_H
