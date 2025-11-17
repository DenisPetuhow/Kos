#ifndef SCENE3D_NEW_H
#define SCENE3D_NEW_H
#include "object3d.h"
#include "osgviewerQt.h"
#include <QWidget>

class ASDObject3D;

class ASDScene3D : public ViewerWidget
{
    Q_OBJECT
public:
    ASDScene3D(QWidget *parent = 0);
    ~ASDScene3D();
    void initDateSky(QDateTime dateBegin);
    void addObject3D(osg::ref_ptr<ASDObject3D> object);
//    void setObjMap(QVector<ParamGrBase> station, QVector<ASDOrbitalObjectPar> ka, QVector <ASDZoneVisiblePoint> mapObzRegionKA, QDateTime curtime);
    bool removeObject3D(osg::ref_ptr<ASDObject3D> object);
    void repaintObjects3D(QDateTime time);
    void update3D(QDateTime time);
    void clear();

public slots:
    void changeFlagAxis();
    void changeFlagSky();
    void changeFlagSun();
    void replaceEarth();
    void replaceEarthDN();
    void replaceEarthAtm();

private:
    QList<osg::ref_ptr<ASDObject3D> > m_objects;
    osg::ref_ptr<nodePick3D> m_nodePick;
    QDateTime m_date;
    bool flagAxis;                                 //!< флаг отображения координатных осей
    bool flagSky;
    bool flagSun;
    bool flagEarth;
    bool flagDayNight;

};

#endif // SCENE3D_H
