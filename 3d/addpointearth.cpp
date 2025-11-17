#include "addpointearth.h"

osg::ref_ptr<osg::Group> addPointEarth::m_point = 0;


addPointEarth::addPointEarth(SGroundVeh point, QString icon)
{
    m_p = point;
    m_icon = icon;
    m_create_object = false;
}

void addPointEarth::repaint(QDateTime time, ASDScene3D* scene)
{
    if(m_create_object == false)
        if(m_icon.isEmpty()==true)
        {
            QVector<double> coord = ASDCoordConvertor::convGeoToGsc(m_p.latitude, m_p.longitude, m_p.height);
            osg::ref_ptr<osg::Geode> geode (new osg::Geode());
            osg::ref_ptr<osg::Geometry> geometry (new osg::Geometry());
            osg::ref_ptr<osg::Vec3Array> vertices (new osg::Vec3Array());
            vertices->push_back(osg::Vec3(coord[0]*1000,coord[1]*1000,coord[2]*1000));
            geometry->setVertexArray(vertices.get());
            osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
            color->push_back(osg::Vec4(1.0,0,0,1));
            geometry->setColorArray(color);
            geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
            geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS,0,vertices->size()));
            osg::Point *point = new osg::Point;
            point->setSize(1);
            geode->getOrCreateStateSet()->setAttribute(point);
            geode->addDrawable(geometry.get());
            osg::StateSet* state = geode->getOrCreateStateSet();
            state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
            m_transform = new osg::MatrixTransform;
            m_transform->addChild(geode);
            scene->m_root_gsk->addChild(m_transform);


            m_create_object = true;
        }
        else
        {
            osg::ref_ptr<osg::MatrixTransform> icon  = scene->addObjectIconPoint(m_icon);
            osg::AutoTransform* at = new osg::AutoTransform;
            at->addChild(icon);
            at->setAutoScaleToScreen(true);
            at->setMinimumScale(0);
            at->setMaximumScale(4000);
            m_transform = new osg::MatrixTransform;
            m_transform->addChild(at);
            QVector<double> coord = ASDCoordConvertor::convGeoToGsc(m_p.latitude, m_p.longitude, 10);

            osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
            mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
            mt1 = osg::Matrix::rotate(osg::Quat(m_p.longitude, osg::Z_AXIS));
            mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2-m_p.latitude, osg::Y_AXIS));
            mt3 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
            mt_sum = mt3*mt2*mt1*mt4;
            m_transform->setMatrix(mt_sum);
            scene->m_root_gsk->addChild(m_transform);
            m_create_object = true;

        }
}

bool addPointEarth::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_gsk->removeChild(m_transform);
        m_create_object = false;
        return true;
    }
    return false;
}
