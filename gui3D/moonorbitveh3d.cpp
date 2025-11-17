#include "moonorbitveh3d.h"
#include "../lunaorbitalmotion.h"

osg::ref_ptr<osg::MatrixTransform> ASDMoonOrbitVeh3D::m_model3d = 0;

ASDMoonOrbitVeh3D::ASDMoonOrbitVeh3D(QMap<QDateTime, QVector<double> > coord_agsk)
{
    m_coord_agsk = coord_agsk;
    m_create_object = false;



}

void ASDMoonOrbitVeh3D::repaint(QDateTime time, ASDScene3D *scene)
{

    if(m_model3d==0)
    {
        m_model3d = new osg::MatrixTransform();
        osg::ref_ptr<osg::MatrixTransform> model3d_icon  = scene->addObjectIcon(QString("gui3d/KA.png"));
        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
        osg::ref_ptr<osg::MatrixTransform> model3d_object = scene->addObject(QString("gui3d/tdrs2.osgt"));
        lod->addChild(model3d_icon,3e5,1e30);
        lod->addChild(model3d_object,0,3e5);
        m_model3d->addChild(lod);
    }

    if(m_create_object == false)
    {
        m_transform = new osg::MatrixTransform();
        m_transform->addChild(m_model3d.get());
        scene->m_root_agsk->addChild(m_transform.get());
        m_create_object = true;
    }
    else
    {


        //        lunaOrbitalMotion orbit_motion;
        //        QVector<double>  coord = orbit_motion.getPosition(m_coord_agsk,m_time,time);
        QVector <double> coord(3,0);
        QMap<QDateTime,QVector<double> >::Iterator iter;
        for(iter = m_coord_agsk.begin(); iter!=m_coord_agsk.end(); iter++)
        {
            if(time<iter.key())
            {
                coord = iter.value();
                break;
            }
        }

        osg::Quat angel;
        double r = pow(pow(coord[0],2)+pow(coord[1],2)+pow(coord[2],2),0.5);
        angel.makeRotate_original(osg::Vec3d(r*1000,0,0),osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));

        osg::Matrixd mt;
        mt.setRotate(angel);
        mt.setTrans(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
        m_transform->setMatrix(mt);
    }
}

bool ASDMoonOrbitVeh3D::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_agsk->removeChild(m_transform);
        m_create_object = false;
        return true;
    }
    return false;
}

