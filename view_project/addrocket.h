#ifndef ADDROCKET_H
#define ADDROCKET_H

#include "object3d.h"
#include "common/asdtype.h"
#include "common/asdconvtype.h"
#include "vehicle/orbitalvehicle.h"
#include "vehicle/strategicrocket.h"
#include "osg/BlendColor"

class addRocket : public ASDObject3D
{
public:
    addRocket(QMap<QDateTime, QVector<double> > trassRocket, QDateTime timeObs, QColor color);
    void repaint(QDateTime time, ASDScene3D * scene);
    bool remove(ASDScene3D* scene);
    static osg::ref_ptr<osg::MatrixTransform> m_model3d; //адрес формы объекта

protected:
    bool m_create_color;
    bool m_create_Rocket;
    bool m_create_Trassa;
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::ref_ptr<osg::MatrixTransform> m_transform_traject;
    QMap<QDateTime, QVector<double> > m_trassRocket;
    QDateTime m_timeObs;
    QColor m_color;
    ASDScene3D *m_scene;
};

#endif // ADDROCKET_H
