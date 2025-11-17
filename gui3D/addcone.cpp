#include "addcone.h"
//#include "colorvisitor.h"
#include "osg/BlendColor"
osg::ref_ptr<osg::MatrixTransform> addCone::m_cone = 0;

addCone::addCone(ASDOrbitalVehicle ka, ASDBsePar par,QMap<QDateTime,int> mapP)
{
    m_ka = ka;
    m_par = par;
    m_create_object = false;
    m_create_object_NO = true;
    if(m_map.size()>0)
        m_map.clear();
    m_map=mapP;
}

void  addCone::repaint(QDateTime tim, ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        QDateTime time=tim;
        if(m_create_object_NO) //создавать ли объект
        {
            if(m_create_object == false)
            {
                m_cone = new osg::MatrixTransform;
                QVector<double> coord = m_ka.getCurrPos(time);
                ASDInterLocation m_c;
                QVector<double> coordEnd(3);
                QVector<double> coord0(3, 0.);
                coordEnd = m_c.calcInterLineWithEarth(coord, coord0);
                QVector <double> coordRes(3);
                double gamma = m_par.gamma*DEG_TO_RAD;
                //double gamma = 1.5*DEG_TO_RAD;
                QColor color(50,200,20,100);

                coordRes[0] = (coordEnd[0]-coord[0])*1000.;
                coordRes[1] = (coordEnd[1]-coord[1])*1000.;
                coordRes[2] = (coordEnd[2]-coord[2])*1000.;
                double h1 = pow(coordRes[0]*coordRes[0]+coordRes[1]*coordRes[1]+coordRes[2]*coordRes[2],0.5);
                double r = h1*tan(gamma);

                osg::ref_ptr<osg::Cone> model = new osg::Cone(osg::Vec3d(0.0f,0.0f,-0.75*h1),r,h1);
                osg::ref_ptr<osg::ShapeDrawable> geom = new osg::ShapeDrawable();
                geom->setShape(model);
                geom->setColor(osg::Vec4f(color.redF(),color.greenF(),color.blueF(),color.alphaF()));
                osg::ref_ptr<osg::Geode> geod = new osg::Geode();
                geod->addDrawable(geom);



                osg::StateSet* state = geod->getOrCreateStateSet();
                osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
                state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
                osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
                state->setAttributeAndModes( blendFunc );
                state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
                state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON  );
                m_cone->addChild(geod);
                m_transform = new osg::MatrixTransform();
                m_transform->addChild(m_cone.get());
                scene->m_root_agsk->addChild(m_transform.get());
                m_create_object = true;
                //m_create_object = false;//?/////////////?
            }
            else
            {
                QVector<double> coord = m_ka.getCurrPos(time);
                ASDInterLocation m_c;
                QVector<double> coordEnd(3);
                QVector<double> coord0(3, 0.);
                coordEnd = m_c.calcInterLineWithEarth(coord, coord0);
                QVector <double> coordRes(3);
                coordRes[0] = (coordEnd[0]-coord[0])*1000.;
                coordRes[1] = (coordEnd[1]-coord[1])*1000.;
                coordRes[2] = (coordEnd[2]-coord[2])*1000.;
                double h1 = pow(coordRes[0]*coordRes[0]+coordRes[1]*coordRes[1]+coordRes[2]*coordRes[2],0.5);
                double h2 = pow(coordRes[0]*coordRes[0]+coordRes[1]*coordRes[1],0.5);
                double beta = asin(coordRes[2]/h1);
                double alfa=0;
                if(h2 != 0)
                {
                    alfa = ASDCoordConvertor::angle(coordRes[1]/h2,coordRes[0]/h2);
                }
                osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
                mt1 = osg::Matrix::rotate(osg::Quat(-M_PI/2., osg::Y_AXIS));
                mt2 = osg::Matrix::rotate(osg::Quat(alfa, osg::Z_AXIS));
                mt3 = osg::Matrix::rotate(osg::Quat(-beta, osg::Y_AXIS));
                mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000.,coord[1]*1000.,coord[2]*1000.));
                mt_sum = mt1*mt3*mt2*mt4;
                m_transform->setMatrix(mt_sum);


                if(m_map.size()>0)
                {

                    QList<QDateTime> keyst=m_map.uniqueKeys();
                    int dtk=-1;



                    for(int ij=0;ij<keyst.size();ij++)
                    {   int dt=abs(keyst.at(ij).secsTo(time));

                        if (abs(dt)<100) dtk=ij;

                    }
                    if(dtk>=0)
                    {


                        osg::StateSet* state = m_transform.get()->getOrCreateStateSet();
                        osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);

                        state->setMode( GL_SRC_COLOR, osg::StateAttribute::INHERIT);
                        osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                        osg::ref_ptr<osg::BlendColor> blendColor = new osg::BlendColor;
                        blendFunc->setSourceRGB(osg::BlendFunc::CONSTANT_COLOR);
                        blendColor->setConstantColor(osg::Vec4(0.9f,0.0f,0.0f,0.9f));
                        blendFunc->setDestinationRGB(osg::BlendFunc::ONE_MINUS_CONSTANT_COLOR);

                        state->setAttributeAndModes( blendColor );
                        state->setAttributeAndModes( blendFunc );
                        state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
                        state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON  );

                        m_transform->setStateSet(state);




                    }
                    else
                    {
                        osg::StateSet* state = m_transform.get()->getOrCreateStateSet();

                        osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
                        state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
                        osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                        blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
                        state->setAttributeAndModes( blendFunc );
                        state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
                        state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON  );
                    }


                }

            }
        }
    }

}

bool addCone::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_agsk->removeChild(m_transform);
        return true;
    }
    return false;
}
