#include "scene3d.h"

ASDScene3D::ASDScene3D(QWidget *parent) :
    ViewerWidget(parent)
{
    m_date = QDateTime::currentDateTime();

    createSky(m_root_agsk, m_date);
    createEarth(m_root_gsk, "readymapdaynight.earth");

    sb = new QStatusBar;
    sb->setMaximumHeight(20);

    m_nodePick = new nodePick3D(m_root_agsk);

    //две строчки очищают оперативку от загруженных, но не используемых слoев
    view->getDatabasePager()->setDoPreCompile( true);
    view->getDatabasePager()->setTargetMaximumNumberOfPageLOD(2);
    view->getDatabasePager()->setUnrefImageDataAfterApplyPolicy(true,true);

    flagEarth = true;
    flagDayNight = true;
    flagAxis = false;
    flagSky = true;
    flagSun = true;
}

ASDScene3D::~ASDScene3D()
{
    clear();
}

void ASDScene3D::initDateSky(QDateTime dateBegin)
{
    moveEarth(dateBegin);
}

void ASDScene3D::addObject3D(osg::ref_ptr<ASDObject3D> object)
{
    m_objects.append(object);
}

bool ASDScene3D::removeObject3D(osg::ref_ptr<ASDObject3D> object)
{
    int i = m_objects.indexOf(object);

    if(object->remove(this))
    {
        m_objects.removeAt(i);
        return true;
    }
    return false;

}

void ASDScene3D::repaintObjects3D(QDateTime time)
{
    moveEarth(time);
    if(m_objects.size()==0) return;
    foreach (osg::ref_ptr<ASDObject3D> object, m_objects)
    {
        if(object.get())  object.get()->repaint(time, this);
    }

}
void ASDScene3D::update3D(QDateTime time)
{
    if(m_objects.size()==0) return;
    foreach (osg::ref_ptr<ASDObject3D> object, m_objects)
    {
        if(object.get()) object.get()->repaint(time, this);
    }
}

void ASDScene3D::clear()
{

    foreach (osg::ref_ptr<ASDObject3D> object, m_objects)
    {
        object.get()->remove(this);

    }
    m_objects.clear();
}

void ASDScene3D::replaceEarthAtm()
{

}

void ASDScene3D::replaceEarthDN()
{
    if (flagDayNight){
        flagDayNight=false;
        clearGlobe(m_root_gsk);
        createGlobe(m_root_gsk, "readymapdaynight.earth");
    }

    else{
        flagDayNight=true;
        clearGlobe(m_root_gsk);
        createGlobe(m_root_gsk, "readymapgeo.earth");
    }
}

void ASDScene3D::replaceEarth()
{
    if (flagEarth){
        flagEarth=false;
        clearGlobe(m_root_gsk);
        createGlobe(m_root_gsk, "readymap.earth");
    }

    else{
        flagEarth=true;
        clearGlobe( m_root_gsk);
        createGlobe(m_root_gsk, "readymapgeo.earth");
    }
}

void ASDScene3D::changeFlagAxis()
{
    if (flagAxis){
        flagAxis=false;
        clearScene(m_root_gsk);
    }

    else{
        flagAxis=true;
        addAxesOSGT(m_root_gsk);
    }
}

void ASDScene3D::changeFlagSky()
{
    if (flagSky){
        flagSky=false;
        clearStars();
    }

    else{
        flagSky=true;
        createStars();
    }
}

void ASDScene3D::changeFlagSun()
{
    if (flagSun){
        flagSun=false;
        clearSun();
    }

    else{
        flagSun=true;
        createSun();
    }
}
