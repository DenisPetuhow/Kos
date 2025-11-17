#include "addKA.h"

osg::ref_ptr<osg::MatrixTransform> addKA::m_model3d = 0;

addKA::addKA(ASDOrbitalVehicle ka, ASDOrbitalObjectPar par)
{
    m_ka = ka;
    m_par = par;
    m_create_object = false;

}

void addKA::repaint(QDateTime time, ASDScene3D *scene)
{

    if(m_model3d==0)
    {
        m_model3d = new osg::MatrixTransform();
        osg::ref_ptr<osg::MatrixTransform> model3d_icon  = scene->addObjectIcon(QString("gui3d/KA.png"));
        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
       osg::ref_ptr<osg::MatrixTransform> model3d_object = scene->addObject(QString("gui3d/tdrs.osgt"));
        lod->addChild(model3d_icon,1e7,1e20);
        lod->addChild(model3d_object,0,1e7);
        m_model3d->addChild(lod);
    }
    if(m_create_object == false)
    {
        m_transform = new osg::MatrixTransform();
        m_transform->addChild(m_model3d.get());
        scene->m_root_agsk->addChild(m_transform.get());
        m_create_object = true;

        osg::Vec3 pos(0,100000,0);
        osg::Vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
        float size = 25;
        osgText::Text* text = new osgText::Text;
        text->setColor(color);
        text->setFont("font/times.ttf");
        text->setCharacterSize(size);
        text->setPosition(pos);
        text->setAxisAlignment(osgText::Text::SCREEN);
        text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
        text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);
        text->setText(m_par.nameVeh.toStdString(), osgText::String::ENCODING_UTF8);
        osg::ref_ptr<osg::Geode> geod = new osg::Geode();
        geod->addDrawable(text);

        float size2 = 15;
        osgText::Text* text2 = new osgText::Text;
        text2->setColor(color);
        text2->setFont("font/times.ttf");
        text2->setCharacterSize(size2);
        text2->setPosition(pos);
        text2->setAxisAlignment(osgText::Text::SCREEN);
        text2->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
        text2->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);
        text2->setText(m_par.nameVeh.toStdString(), osgText::String::ENCODING_UTF8);
        osg::ref_ptr<osg::Geode> geod2 = new osg::Geode();
        geod2->addDrawable(text2);

        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
        lod->addChild(geod2,1e7,1e8);
        lod->addChild(geod,0,1e7);
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

bool addKA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_agsk->removeChild(m_transform);
        m_create_object = false;
        return true;
    }
    return false;
}

