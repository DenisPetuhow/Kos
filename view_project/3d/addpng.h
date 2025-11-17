#ifndef ADDPNG_H
#define ADDPNG_H


#include "object3d.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"

class addpng : public ASDObject3D, ASDPositionObj
{

public:
    addpng(double min_lat,double max_lat,double min_lon,double max_lon,QString filepng);
    static osg::ref_ptr<osg::MatrixTransform> m_png;
//void setzon(QMap<QDateTime,int> mapP);
    bool m_create_object;


    bool m_create_object_NO;

    void repaint(QDateTime time, ASDScene3D * scene);

    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
   QVector<double> m_latpos;
   QVector<double> m_lonpos;
   double m_min_lat;
   double m_max_lat;
   double m_min_lon;
   double m_max_lon;
   QString m_filepng;

};

#endif // ADDPNG_H
