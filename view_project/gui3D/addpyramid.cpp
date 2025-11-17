#include "addpyramid.h"
//#include "colorvisitor.h"
addPyramid::addPyramid(ASDOrbitalVehicle ka, ASDBsePar par,QMap<QDateTime,int> mapP)
{
    m_ka = ka;
    m_par = par;
    m_pyr = new osg::Group;
    m_create = false;
    m_create_no = true;
    m_map.clear();
    m_map=mapP  ;
}

void  addPyramid::repaint(QDateTime time, ASDScene3D *scene)
{
    if(m_create_no)
        //   if(!scene->view->done())
    {
        if(m_create==true)
        {
            scene->m_root_gsk->removeChild(m_pyr);
            m_pyr = new osg::Geode();
        }



        QVector<double> coord = m_ka.getCurrPos(time);
        QVector<double> coordKA = ASDCoordConvertor::convAgescToGsc(coord,time);

        ASDAngleMounting angle;
        if(m_par.yaw<=0) {
            m_par.yaw =45*DEG_TO_RAD;
            m_par.deltaV=40.*DEG_TO_RAD;
            m_par.deltaH=35.*DEG_TO_RAD;
        }
        angle.pitch = m_par.pitch;
        angle.roll = m_par.roll;
        angle.yaw = m_par.yaw;
        QVector<QVector <double> > points1;
        points1 = CVizibility::calcPiramidObzor(coord,angle, m_par.deltaV,m_par.deltaH);
        QVector<double> point_geo1 = ASDCoordConvertor::convAgescToGsc(points1[0],time);
        QVector<double> point_geo2 = ASDCoordConvertor::convAgescToGsc(points1[1],time);

        ASDAngleMounting angle2;
        angle2.pitch = -m_par.pitch;
        angle2.roll = -m_par.roll;
        angle2.yaw = -m_par.yaw;
        QVector<QVector <double> > points2;
        points2 = CVizibility::calcPiramidObzor(coord, angle2, m_par.deltaV, m_par.deltaH);
        QVector<double> point_geo3 = ASDCoordConvertor::convAgescToGsc(points2[0],time);
        QVector<double> point_geo4 = ASDCoordConvertor::convAgescToGsc(points2[1],time);

        osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(5);
        (*vertices)[0].set(point_geo1[0]*1000, point_geo1[1]*1000, point_geo1[2]*1000);
        (*vertices)[1].set(point_geo3[0]*1000, point_geo3[1]*1000, point_geo3[2]*1000);
        (*vertices)[2].set(point_geo4[0]*1000, point_geo4[1]*1000, point_geo4[2]*1000);
        (*vertices)[3].set(point_geo2[0]*1000, point_geo2[1]*1000, point_geo2[2]*1000);
        (*vertices)[4].set(coordKA[0]*1000, coordKA[1]*1000, coordKA[2]*1000);

        osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 6);
        (*indices)[0] = 0;      (*indices)[1] = 3;      (*indices)[2] = 4;
        (*indices)[3] = 2;      (*indices)[4] = 1;      (*indices)[5] = 4;
        osg::ref_ptr<osg::DrawElementsUInt> indicesL = new osg::DrawElementsUInt(GL_TRIANGLES, 3);
        (*indicesL)[0] = 0;      (*indicesL)[1] = 3;      (*indicesL)[2] = 4;
        osg::ref_ptr<osg::DrawElementsUInt> indicesR = new osg::DrawElementsUInt(GL_TRIANGLES, 3);
        (*indicesR)[0] = 2;      (*indicesR)[1] = 1;      (*indicesR)[2] = 4;

        osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

        if(m_map.size()>0)
        {

            QList<QDateTime> keyst=m_map.uniqueKeys();
            int dtk=-1;



            for(int ij=0;ij<keyst.size();ij++)
            {   int dt=abs(keyst.at(ij).secsTo(time));

                if (abs(dt)<200) dtk=ij;

            }
            if(dtk>=0)
            {
                // qDebug()<<"VIZ pyramid "<<time.time();
                if(m_map.contains(keyst.at(dtk)))
                {
                    int ob= m_map.value(keyst.at(dtk));
                    color->push_back(osg::Vec4(0.5f,0.9f,0.0f,0.8f));
                    geom->setVertexArray(vertices.get());
                    if(ob==0) geom->addPrimitiveSet(indicesR.get());
                    if(ob==1) geom->addPrimitiveSet(indicesL.get());
                    geom->setColorArray(color.get());
                }

            }
            else{
                color->push_back(osg::Vec4(0.0f,1.0f,0.0f,0.2f));

                geom->setVertexArray(vertices.get());
                geom->addPrimitiveSet(indices.get());
                geom->setColorArray(color.get());

            }


        }else
        {
            color->push_back(osg::Vec4(0.0f,1.0f,0.0f,0.2f));

            geom->setVertexArray(vertices.get());
            geom->addPrimitiveSet(indices.get());
            geom->setColorArray(color.get());
        }
        geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
        osgUtil::SmoothingVisitor::smooth(*geom);

        osg::ref_ptr<osg::Geode> geod = new osg::Geode;
        geod->addDrawable(geom.get());
        // time

        //
        osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
        blendFunc->setFunction(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        osg::StateSet* state = geod->getOrCreateStateSet();
        state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
        state->setAttributeAndModes(blendFunc);
        state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
        m_pyr->addChild(geod);
        scene->m_root_gsk->addChild(m_pyr);
        m_create = true;
    }
}

bool addPyramid::remove(ASDScene3D *scene)
{

    if(!scene->view->done())
    {
        if(m_create == true)
        {
            scene->m_root_gsk->removeChild(m_pyr);
            m_create = false;
            m_create_no = false;

        }
        return true;
    }
    return false;
}
