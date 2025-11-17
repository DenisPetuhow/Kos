#include "addzonaobz.h"
#include "math.h"
#include "QDebug"
addzonaobz::addzonaobz(QMap<QDateTime,  QPolygonF> mapP)
{
    m_kazon = mapP;

    m_create_object = false;
}

void addzonaobz::repaint(QDateTime time, ASDScene3D *scene)
{
    QDateTime timecur=time;
    if(!scene->view->done())
    {
//        if(m_create_object==true)
//        {


//          //  m_transform_traject = new osg::MatrixTransform;
//            m_transform = new osg::MatrixTransform;
//        }
        //if(m_create_object == false)
          scene->m_root_gsk->removeChild(m_transform);

        {
           // m_transform_traject = new osg::MatrixTransform;
            m_transform = new osg::MatrixTransform;

        }

       // QVector<double> coord;
      // coord.resize(3);
        QList<QDateTime> keyst=m_kazon.uniqueKeys();
        if(m_kazon.size()>0)
        {

//QVector<QDateTime> iten;
//iten.resize(m_reg.size());
int dtk=0;



for(int ij=0;ij<keyst.size();ij++)
{  // int dt=abs(keyst.at(ij).secsTo(timecur));

if (keyst.at(ij)<timecur) dtk=ij;

}


            //

              //if((m_map.timeBegin<time) && (m_map.timeEnd>time)



osg::ref_ptr<osg::Geode> geode (new osg::Geode());



            QPolygonF posx= m_kazon[keyst.at(dtk)];



            QColor m_col=QColor(251,200,16);
            QColor m_col1=QColor(10,250,10);
            QColor m_col2=QColor(233,200,10);

            osg::ref_ptr<osg::Geometry> geometry (new osg::Geometry());
            osg::ref_ptr<osg::Vec3Array> vertices (new osg::Vec3Array());
            double r = 6759.0;
            for(int jjj=0;jjj<posx.size();jjj++)
            {
             double poslati=posx.at(jjj).y()*DEG_TO_RAD;
             double posloni=posx.at(jjj).x()*DEG_TO_RAD;

            double z0i= sin(poslati) * r;
            double k = pow(r * r - z0i * z0i, 0.5);

           double x01 = cos(posloni) * k;
           double y01 = sin(posloni) * k;

           vertices->push_back(osg::Vec3(x01*1000,y01*1000,z0i*1000));
            }

           geometry->setVertexArray(vertices.get());
           osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;

         color->push_back(osg::Vec4(m_col2.redF(),m_col2.greenF(),m_col2.blueF(),0.2));

           geometry->setColorArray(color);

           geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
       // geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,vertices->size()));
           geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON,0,vertices->size()));
           geode->addDrawable(geometry.get());

//qDebug()<<"3deddd";





                osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                blendFunc->setFunction(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


             osg::StateSet* state = geode->getOrCreateStateSet();

             state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);

             state->setAttributeAndModes(blendFunc);
             state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
             m_transform = new osg::MatrixTransform;
             m_transform->addChild(geode);



             scene->m_root_gsk->addChild(m_transform);


             m_create_object = true;


        }
    }




}

bool addzonaobz::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if((scene->m_root_gsk->removeChild(m_transform)) )
        {
            m_create_object = false;

            return true;
        }
        else return false;
    }
    return false;
}


