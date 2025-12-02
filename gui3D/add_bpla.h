#ifndef ADD_BPLA_H
#define ADD_BPLA_H

#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
#include "osg/BlendColor"
#include "osg/LineWidth"
#include "osg/LineStipple"



class add_BPLA : public ASDObject3D, ASDPositionObj
{
public:



    add_BPLA(ASD_bpla_struct _BPLA,QString icon,ASDScene3D * scene);
    ASDScene3D * m_scene;
    QVector <double> getPos_BpLA(QDateTime dt);
    static osg::ref_ptr<osg::MatrixTransform> m_bpla;
    double length_bpla;
    double az_bpla;
    double speed_bpla;
    double lon0_bpla;
    double lat0_bpla;
    double lon_fin_bpla;
    double lat_fin_bpla;
    QDateTime t0_runBPLA;
    QVector<double> cur_pos_bpla;// [0] - lat, [1] - lon
    QString m_icon;
    bool m_create_object;
    ASD_bpla_struct m_BPLA;
    double get_azimuth(const double lat1, const double lon1, const double lat2,const double lon2);
    QPointF coordpoint2(QPointF p,double D1,double A1);
    double PiTOPi(double d);

    void repaint(QDateTime time, ASDScene3D * scene);

    bool remove(ASDScene3D* scene);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::Geode> m_trajectory_line;

    void createTrajectoryLine(ASDScene3D* scene);

};

#endif // ADD_BPLA_H
