#include "orbitveh3d.h"


osg::ref_ptr<osg::MatrixTransform> ASDOrbitVeh3D::m_model3d = 0;

ASDOrbitVeh3D::ASDOrbitVeh3D(ASDOrbitalVehicle ka, ASDOrbitalObjectPar par)
{
    m_ka = ka;
    m_par = par;
    m_create_object = false;



}

void ASDOrbitVeh3D::repaint(QDateTime time, ASDScene3D *scene)
{

    if(m_model3d==0)
    {
        m_model3d = new osg::MatrixTransform();
        osg::ref_ptr<osg::MatrixTransform> model3d_icon  = scene->addObjectIcon(QString("gui3D/KA.png"));
        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
        // osg::ref_ptr<osg::MatrixTransform> model3d_object = scene->addObject(QString("gui3d/tdrs2.osgt"));
        //   osg::ref_ptr<osg::MatrixTransform> model3d_object = scene->addObject(QString("gui3d/ka/stss.obj"));
        osg::ref_ptr<osg::MatrixTransform> model3d_object = scene->addObject(QString("gui3D/model.3ds"));
        // lod->addChild(model3d_icon,3e6,1e20);
        //lod->addChild(model3d_object,110,3e6);
        //lod->addChild(model3d_icon,3e6,1e20);
        lod->addChild(model3d_object,3e6,1e20);
        m_model3d->addChild(lod);
    }

    if(m_create_object == false)
    {
        m_transform = new osg::MatrixTransform();
        m_transform->addChild(m_model3d.get());
        scene->m_root_agsk->addChild(m_transform.get());
        m_create_object = true;

        osg::Vec3 pos(0,0,0);
        osg::Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
        float size = 15;
        osgText::Text* text = new osgText::Text;
        text->setColor(color);
        text->setFont("font/times.ttf");
        text->setCharacterSize(size);
        text->setPosition(pos);
        text->setAxisAlignment(osgText::Text::SCREEN);
        text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
        //text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);
        text->setDrawMode(osgText::Text::TEXT );
        text->setText(m_par.nameVeh.toStdString(),osgText::String::ENCODING_UTF8);
        osg::ref_ptr<osg::Geode> geod = new osg::Geode();
        geod->addDrawable(text);
        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
        lod->addChild(geod,1000,1e7);
        m_transform2 = new osg::MatrixTransform();
        m_transform2->addChild(lod);
        m_transform->addChild(m_transform2.get());
    }
    else
    {
        QVector<double> coord = m_ka.getCurrPos(time);

        osg::Quat angel;
        double r = pow(pow(coord[0],2)+pow(coord[1],2)+pow(coord[2],2),0.5);
        angel.makeRotate_original(osg::Vec3d(r*1000,0,0),osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));

        osg::Matrixd mt;
        mt.setRotate(angel);
        mt.setTrans(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
        m_transform->setMatrix(mt);

        if(m_par.nameVeh.size()!=0)
        {
            osg::Matrixd mt;
            mt.setTrans(50000,30000,0);
            m_transform2->setMatrix(mt);
        }
    }
}

bool ASDOrbitVeh3D::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_agsk->removeChild(m_transform);
        m_create_object = false;
        return true;
    }
    return false;
}

