#include "addline.h"

addLineKP::addLineKP(ASDZoneVisible mapOCP, ASDOrbitalVehicle ka, SGroundVeh Veh)
{
    m_map = mapOCP;
    m_ka = ka;
    m_point = Veh;
    g_line = new osg::Geode();
    m_create = false;
    m_create_no = true;
    init = 0;


}

addLineKP::addLineKP(ASDZoneVisible mapOCP, QMap<QDateTime, QVector<double> > ka_coord, SGroundVeh Veh)
{
    m_map = mapOCP;
    m_ka_coord = ka_coord;
    m_point = Veh;
    g_line = new osg::Geode();
    m_create = false;
    m_create_no = true;
    init = 1;
}

void addLineKP::repaint(QDateTime time, ASDScene3D *scene)
{

    if((m_map.timeBegin<time) && (m_map.timeEnd>time))
    {
        if(!scene->view->done())
        {
            if(m_create==true)
            {
                scene->m_root_gsk->removeChild(g_line);
                g_line = new osg::Geode();
            }
             QVector<double> coord;
            if(init==0)
            {
            coord = m_ka.getCurrPos(time);
            }
            if(init==1)
            {
                QMap<QDateTime,QVector<double> >::Iterator iter;
                for(iter = m_ka_coord.begin(); iter!=m_ka_coord.end(); iter++)
                {
                    if(time<iter.key())
                    {
                        coord = iter.value();
                        break;
                    }
                }
            }



            QVector<double> coordKA = ASDCoordConvertor::convAgescToGsc(coord,time);
            QVector<double> coordPoint = ASDCoordConvertor::convGeoToGsc(m_point.latitude, m_point.longitude, m_point.height);
            osg::Vec3 x1(coordKA[0]*1000,coordKA[1]*1000,coordKA[2]*1000);
            osg::Vec3 x0(coordPoint[0]*1000.,coordPoint[1]*1000.,coordPoint[2]*1000.);
            osg::ref_ptr<osg::Geometry> line (new osg::Geometry);
            osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
            points->push_back(x0);
            points->push_back(x1);
            osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
            color->push_back(osg::Vec4(1.0,0,0,1));
            line->setVertexArray(points);
            line->setColorArray(color);
            line->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
            line->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));
            g_line->addDrawable(line.get());
            osg::StateSet* state = g_line->getOrCreateStateSet();
            state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
            scene->m_root_gsk->addChild(g_line.get());
            m_create = true;


        }
    }

    if((time>m_map.timeEnd)&&(m_create == true))
    {
        if(!scene->view->done())
        {
            if(scene->removeObject3D(this))
            {
                m_create = false;
            }
        }
    }
}

bool addLineKP::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
     {
        if(scene->m_root_gsk->removeChild(g_line))
        {
        m_create = false;
        return true;
        }
        else return false;
    }
    return false;
}
