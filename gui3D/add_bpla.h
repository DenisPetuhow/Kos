#ifndef ADD_BPLA_H
#define ADD_BPLA_H

#include "object3d.h"
#include "ASD/asdtype.h"
#include "ASD/asdconvtype.h"
#include "ASD/orbitalvehicle.h"
#include "osg/BlendColor"
#include "osg/LineWidth"
#include "osg/LineStipple"
#include <QSet>
#include <QMap>
#include <osgText/Text>
#include <osgText/Font>



class add_BPLA : public ASDObject3D, ASDPositionObj
{
public:
    // ЕДИНАЯ высота полета БПЛА в км. Используется ВЕЗДЕ:
    // модель, траектория, старт линии видимости, проверка видимости.
    // Раньше модель рисовалась на 10 км, а линия стартовала с 10 м - линия
    // была оторвана от модели.
    static constexpr double BPLA_ALT_KM = 10.0;

    add_BPLA(ASD_bpla_struct _BPLA, ASDScene3D * scene);

    ASDScene3D * m_scene;
    QVector <double> getPos_BpLA(QDateTime dt);
    static osg::ref_ptr<osg::MatrixTransform> m_bpla_model;
    double length_bpla;
    double az_bpla;
    double speed_bpla;
    double lon0_bpla;
    double lat0_bpla;
    double lon_fin_bpla;
    double lat_fin_bpla;
    QDateTime t0_runBPLA;
    QVector<double> cur_pos_bpla;// [0] - lon, [1] - lat
    bool m_create_object;
    ASD_bpla_struct m_BPLA;
    double get_azimuth(const double lat1, const double lon1, const double lat2,const double lon2);
    QPointF coordpoint2(QPointF p,double D1,double A1);
    double PiTOPi(double d);

    void repaint(QDateTime time, ASDScene3D * scene);
    bool remove(ASDScene3D* scene);

    // Методы для работы с видимостью КА
    void setKaList(QVector<ASDOrbitalObjectPar> ka_list);

protected:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::Geode> m_trajectory_line;

    // Видимость КА
    QVector<ASDOrbitalObjectPar> m_ka_list;
    QMap<int, osg::ref_ptr<osg::Geode>> m_visibility_lines;

    void createTrajectoryLine(ASDScene3D* scene);
    void createBplaModel(ASDScene3D* scene);
    void createLabel();

    void updateVisibilityLines(QDateTime time, ASDScene3D* scene);
    bool isKaVisible(QDateTime time, QVector<double> coordKA_AGESC_km,
                     QVector<double> coordBPLA_geo_deg, double ka_gamma_deg = 30.0);
    osg::ref_ptr<osg::Geode> createVisibilityLine(QVector<double> bpla_agesc_m,
                                                   QVector<double> ka_agesc_m, int ka_id);
};

#endif // ADD_BPLA_H
