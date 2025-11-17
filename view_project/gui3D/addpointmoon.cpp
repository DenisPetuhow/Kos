#include "addpointmoon.h"
#include <../cplanetephconst.h>

//addpointMoon::addpointMoon()
//{

//}
osg::ref_ptr<osg::Group> addpointMoon::m_point = 0;


addpointMoon::addpointMoon(SGroundVeh point, QString icon)
{
    m_p = point;
    m_icon = icon;
    m_create_object = false;
}

void addpointMoon::repaint(QDateTime time, ASDScene3D* scene)
{
    if(m_create_object == false)
        if(m_icon.isEmpty()==true)
        {
            QVector<double> coord = ASDCoordConvertor::convGeoToGsc(m_p.latitude, m_p.longitude, m_p.height,R_MOON);
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
            m_transformM = new osg::MatrixTransform;
            m_transformM->addChild(geode);
            scene->node_moon->addChild(m_transformM);
            m_create_object = true;
        }
        else
        {
            osg::ref_ptr<osg::MatrixTransform> icon  = scene->addObjectIconPoint(m_icon);
            osg::AutoTransform* at = new osg::AutoTransform;

//            // text

//            osg::ref_ptr<osg::Geode> geode = new osg::Geode();

////            //ЧЦМе
//           std::string font("c:/Windows/tahomabd.ttf");

////            //ґґЅЁText¶ФПу
//            osg::ref_ptr<osgText::Text> text = new osgText::Text();
//            geode->addDrawable(text.get());

////            //ЙиЦГЧЦМе
//            text->setFont(font);
//             text->setColor(osg::Vec4(1.0,0.0,1.0,0.6));
//            text->setBoundingBoxColor(osg::Vec4(1.0,0.0,0.0,0.6));
//            //ЙиЦГЧЦМеµД·Ц±жВКЈ¬Д¬ИПОЄ32*32
//           text->setFontResolution(28.0f,28.0f);
//            //ЙиЦГЧЦМеµДґуРЎ
//            text->setCharacterSize(35);
//            //ЙиЦГ¶ФЖл·ЅКЅ
//            text->setAlignment(osgText::Text::LEFT_BOTTOM);
//            //ЙиЦГ·ЅПт
//            text->setAxisAlignment(osgText::Text::USER_DEFINED_ROTATION);
//            //ЙиЦГОДЧЦ
//            //text->setText(m_label);
//        text->setText("1");
//            //№Ш±Х№вХХ
          // geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

//            //ґґЅЁЧФ¶Ї±д»»ЅЪµг
//           osg::ref_ptr<osg::AutoTransform> ate = new osg::AutoTransform;
//            ate->setAutoScaleToScreen(true);
//            ate->setMinimumScale(0);
//           ate->setMaximumScale(1e20);

             QVector<double> coord = ASDCoordConvertor::convGeoToGsc(m_p.latitude, m_p.longitude, 50,R_MOON);
//            osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
//            transform->setPosition(osg::Vec3d(coord[0]*1000+500,coord[1]*1000+500,coord[2]*1000+500));
//           // transform->addChild(scene->node_moon_isxod);
//            //transform->setScale(osg::Vec3d(3*1e-6,3*1e-6,3*1e-6));
//            ate->addChild(transform);
           //  text->setPosition(osg::Vec3d(coord[0]*1000+50,coord[1]*1000+500,coord[2]*1000+500));

          //  scene->node_moon_isxod->addChild(transform);

            //
            at->addChild(icon);
           // at->addChild(geode.get());
            at->setAutoScaleToScreen(true);
            at->setMinimumScale(0);
            at->setMaximumScale(40000);
            m_transformM = new osg::MatrixTransform;
            m_transformM->addChild(at);


            osg::Matrix mt1,mt2,mt3,mt4,mt_sum;

            mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
            mt1 = osg::Matrix::rotate(osg::Quat(m_p.longitude, osg::Z_AXIS));
            mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2-m_p.latitude, osg::Y_AXIS));

            mt3 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
           mt_sum = mt3*mt2*mt1*mt4;
          //  mt_sum = mt2*mt1*mt4;
            m_transformM->setMatrix(mt_sum);
            scene->node_moon_isxod->addChild(m_transformM);
            m_create_object = true;
        }
}

bool addpointMoon::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->node_moon->removeChild(m_transformM);
        m_create_object = false;
        return true;
    }
    return false;
}

