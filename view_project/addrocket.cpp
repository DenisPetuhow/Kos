#include "addrocket.h"

osg::ref_ptr<osg::MatrixTransform> addRocket::m_model3d = nullptr;

addRocket::addRocket(QMap<QDateTime, QVector<double> > trassRocket, QDateTime timeObs, QColor color)
{
    m_trassRocket = trassRocket;
    m_timeObs = timeObs;
    m_color = color;
    m_create_Rocket = false;
    m_create_Trassa = false;
    m_create_color = false;
}

void addRocket::repaint(QDateTime time, ASDScene3D *scene)
{
    if(m_model3d==nullptr)
    {
        m_model3d = new osg::MatrixTransform();
        QString nameRocket = "./icons/rocket/Rocket.obj";
        osg::ref_ptr<osg::Node> m_node = new osg::Node();
        m_node = osgDB::readNodeFile(nameRocket.toStdString());
        osg::StateSet* state_satellite = m_node->getOrCreateStateSet();
        state_satellite->setMode( GL_LIGHTING, osg::StateAttribute::OFF);

        osg::ref_ptr<osg::MatrixTransform> transform_satellite = new osg::MatrixTransform();
        transform_satellite->addChild(m_node);
        osg::Matrix mtScale;
        mtScale = mtScale.scale(osg::Vec3d(10000,10000,10000));
        transform_satellite->setMatrix(mtScale);
        osg::ref_ptr<osg::LOD> lod = new osg::LOD;
        lod->addChild(transform_satellite,0,float(1e20));
        m_model3d->addChild(lod);
    }
    if(m_create_Rocket == false)
    {
        m_transform = new osg::MatrixTransform;
        m_transform->addChild(m_model3d.get());

        scene->m_root_gsk->addChild(m_transform);
        m_create_Rocket = true;
    }
    if(m_create_Trassa == false)
    {
        m_transform_traject = new osg::MatrixTransform;
        osg::ref_ptr<osg::Vec3Array> vertexData = new osg::Vec3Array;
        QVector<double> coord_traject(6);
        QMap<QDateTime, QVector<double> > ::Iterator iter;
        for(iter = m_trassRocket.begin(); iter != m_trassRocket.end();iter++)
        {
            coord_traject = ASDCoordConvertor::convAgescToGsc(iter.value(),iter.key());
            vertexData->push_back(osg::Vec3d(coord_traject[0]*1000,coord_traject[1]*1000,coord_traject[2]*1000));
        }
        osg::ref_ptr<osg::Geometry> linesGeom (new osg::Geometry());
        osg::ref_ptr<osg::DrawArrays> drawArrayLines (new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP));
        drawArrayLines->setFirst(0);
        drawArrayLines->setCount(int(vertexData->size()));
        linesGeom->addPrimitiveSet(drawArrayLines);
        linesGeom->setVertexArray(vertexData);
        osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
        color->push_back(osg::Vec4(m_color.red(),m_color.green(),m_color.blue(),m_color.alpha()));
        linesGeom->setColorArray(color);
        linesGeom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        geode->addDrawable(linesGeom.get());
        osg::StateSet* stateLine = geode->getOrCreateStateSet();
        stateLine->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
        m_transform_traject->addChild(geode);

        scene->m_root_gsk->addChild(m_transform_traject);
        m_create_Trassa = true;
    }
    else
    {
        if(!scene->view->done())
        {
            if(time>m_trassRocket.begin().key() && time<m_trassRocket.lastKey())
            {
                QVector<double> coord = ASDCoordConvertor::convAgescToGsc(m_trassRocket.value(time),time);
                if(m_timeObs<time && !m_create_color)
                {
                    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                    osg::ref_ptr<osg::BlendColor> blendColor = new osg::BlendColor;
                    blendFunc->setSourceRGB(osg::BlendFunc::CONSTANT_COLOR);
                    m_transform->getOrCreateStateSet()->setAttributeAndModes(blendFunc, osg::StateAttribute::ON);
                    m_transform->getOrCreateStateSet()->setAttributeAndModes(blendColor, osg::StateAttribute::ON);
                    blendColor->setConstantColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
                    m_create_color = true;
                }
                if(m_timeObs>time && m_create_color)
                {
                    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                    osg::ref_ptr<osg::BlendColor> blendColor = new osg::BlendColor;
                    blendFunc->setSourceRGB(osg::BlendFunc::CONSTANT_COLOR);
                    m_transform->getOrCreateStateSet()->setAttributeAndModes(blendFunc, osg::StateAttribute::ON);
                    m_transform->getOrCreateStateSet()->setAttributeAndModes(blendColor, osg::StateAttribute::ON);
                    blendColor->setConstantColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
                    m_create_color = false;
                }
                double h1 = pow(pow((coord[3])*1000.0,2)+
                        pow(coord[4]*1000.0,2)+
                        pow(coord[5]*1000.0,2),0.5);

                double h2 = pow(pow(coord[5]*1000.0,2)+
                        pow(coord[3]*1000.0,2),0.5);

                double beta = 0.0;
                if(h1 != 0.0)
                    beta = asin(coord[4]*1000.0/h1);
                double alfa=0.0;
                if(h2 != 0.0)
                    alfa = ASDCoordConvertor::angle(coord[3]*1000.0/h2,coord[5]*1000.0/h2);

                osg::Matrix mt0,mt1,mt2,mt3,mt4,mt_sum;
                mt1 = osg::Matrix::rotate(osg::Quat(-beta, osg::X_AXIS));
                mt2 = osg::Matrix::rotate(osg::Quat(alfa, osg::Y_AXIS));
                mt3 = osg::Matrix::rotate(osg::Quat(M_PI/2, osg::X_AXIS));
                mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000.,coord[1]*1000.,coord[2]*1000.));
                mt_sum = mt3*mt1*mt2*mt4;
                m_transform->setMatrix(mt_sum);
            }
            else
            {
                scene->m_root_gsk->removeChild(m_transform);
                m_create_Rocket = false;
                m_create_color = false;
            }
        }
    }
}

bool addRocket::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if((scene->m_root_gsk->removeChild(m_transform)) && (scene->m_root_gsk->removeChild(m_transform_traject)))
        {
            m_create_Rocket = false;
            m_create_Trassa = false;
            return true;
        }
        else return false;
    }
    return false;
}
