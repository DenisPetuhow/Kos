#include "adddostup.h"
#include "math.h"
#include "QDebug"

adddostup::adddostup(QMap<QDateTime,  ASDZoneVisible> mapP,ParamregionO point)
{
    m_kazon.clear();
    m_kazon = mapP;
    m_reg= point;
    m_create_object = false;
}






void adddostup::repaint(QDateTime time, ASDScene3D *scene)
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
          scene->m_root_gsk->removeChild(m_transform2);
        {
           // m_transform_traject = new osg::MatrixTransform;
            m_transform = new osg::MatrixTransform;
            m_transform2 = new osg::MatrixTransform();
        }

       // QVector<double> coord;
      // coord.resize(3);
        QList<QDateTime> keyst=m_kazon.uniqueKeys();
        if(m_kazon.size()>0)
        {

//QVector<QDateTime> iten;
//iten.resize(m_reg.size());
int dtk=0;
int dt=0;


for(int ij=0;ij<keyst.size();ij++)
{  // int dt=abs(keyst.at(ij).secsTo(timecur));

if (keyst.at(ij)<timecur) dtk=ij;

}
dt=abs(keyst.at(dtk).secsTo(timecur));

            //

              //if((m_map.timeBegin<time) && (m_map.timeEnd>time)

              osg::Quat angel;
               QVector<double> coord;
             //  for(int ij=0;ij<iten.size();ij++)
              {
               // if(keyst.at(ij)<timecur)
               // if(dt<260)

osg::ref_ptr<osg::Geode> geode (new osg::Geode());
if(m_kazon.contains(keyst.at(dtk)))
{


            ASDZoneVisible posx= m_kazon.value(keyst.at(dtk));
           // osg::ref_ptr<osg::Geode> geode (new osg::Geode());

            int j=posx.idVeh;

             coord=ASDCoordConvertor::convGeoToGsc((m_reg.mlat+1)*DEG_TO_RAD, m_reg.mlong*DEG_TO_RAD, 60.);

            // text

            osg::Vec3 pos(0,0,0);
            osg::Vec4 color(.9f, .8f, .3f, 1.0f);
            float size = 45;
            osgText::Text* text = new osgText::Text;
            text->setColor(color);
            text->setFont("font/times.ttf");
            text->setCharacterSize(size);
            text->setPosition(pos);
            text->setAxisAlignment(osgText::Text::SCREEN);
            text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
            text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);

          //  m_transform->addChild(m_transform2.get());



            double r1 = pow(pow(coord[0],2)+pow(coord[1],2)+pow(coord[2],2),0.5);
            angel.makeRotate_original(osg::Vec3d(r1*1000+2000,0,0),osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));



//                osg::Matrixd mt1;
//                mt1.setTrans(50000,30000,0);
//                m_transform2->setMatrix(mt1);

           // QColor m_col=QColor(251,200,16);
             QColor m_col=QColor(251,0,16);
            QColor m_col1=QColor(10,250,10);
            QColor m_col2=QColor(251,220,20);
            double latc=m_reg.mlat;//
            double lonc=m_reg.mlong;//
            double dllat=m_reg.dllat+200;//
            double dllon=m_reg.dllon+100; //
            double r = 6371.0;
            double  klat=dllat/111.13;
            double  klon=dllon/(111.13*cos(latc*DEG_TO_RAD));
                     // 10x10
              klat/=10.;
             klon/=10.;
int rrrt=0;
            for(int jjj=0;jjj<100;jjj++)
            {
                   int  ilat =int(jjj/10.);
                   int    ilon=int((jjj-ilat*10));
                     ilat=int((jjj-ilon)/10.);
                    double poslati=(latc-dllat/(2.*111.13)+klat*ilat)*DEG_TO_RAD;
                    double posloni=(lonc-dllon/(2.*111.13*cos(latc*DEG_TO_RAD))+klon*ilon)*DEG_TO_RAD;
                    osg::ref_ptr<osg::Geometry> geometry (new osg::Geometry());
                    osg::ref_ptr<osg::Vec3Array> vertices (new osg::Vec3Array());
            // for j 0...100
            double z0i= sin(poslati-klat/2.*DEG_TO_RAD) * r;
            double k = pow(r * r - z0i * z0i, 0.5);

           double x01 = cos(posloni-klon/2.*DEG_TO_RAD) * k;
           double y01 = sin(posloni-klon/2.*DEG_TO_RAD) * k;
           double z1i= sin(poslati-klat/2.*DEG_TO_RAD) * r;
           double k1 = pow(r * r - z0i * z1i, 0.5);

          double x11 = cos(posloni+klon/2.*DEG_TO_RAD) * k1;
          double y11 = sin(posloni+klon/2.*DEG_TO_RAD) * k1;

          double z2i= sin(poslati+klat/2.*DEG_TO_RAD) * r;
          double k2 = pow(r * r - z2i * z1i, 0.5);
          double x21 = cos(posloni-klon/2.*DEG_TO_RAD) * k2;
          double y21 = sin(posloni-klon/2.*DEG_TO_RAD) * k2;

          double z3i= sin(poslati+klat/2.*DEG_TO_RAD) * r;
          double k3 = pow(r * r - z3i * z1i, 0.5);
          double x31 = cos(posloni+klon/2.*DEG_TO_RAD) * k3;
          double y31 = sin(posloni+klon/2.*DEG_TO_RAD) * k3;


           vertices->push_back(osg::Vec3(x01*1000,y01*1000,z0i*1000));
           vertices->push_back(osg::Vec3(x21*1000,y21*1000,z2i*1000));
           vertices->push_back(osg::Vec3(x31*1000,y31*1000,z3i*1000));

           vertices->push_back(osg::Vec3(x01*1000,y01*1000,z0i*1000));
           vertices->push_back(osg::Vec3(x11*1000,y11*1000,z1i*1000));
           vertices->push_back(osg::Vec3(x31*1000,y31*1000,z3i*1000));

           geometry->setVertexArray(vertices.get());
           osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
           int fl=posx.listTimeVizib.at(jjj);
          // if(jjj%2) fl=2;
        if(fl<1) color->push_back(osg::Vec4(m_col.redF(),m_col.greenF(),m_col.blueF(),0.5));
        if(fl==1) color->push_back(osg::Vec4(m_col1.redF(),m_col1.greenF(),m_col1.blueF(),0.5));
        if(fl>=2) color->push_back(osg::Vec4(m_col.redF(),m_col.greenF(),m_col.blueF(),0.5));
           geometry->setColorArray(color);
if(fl==2) rrrt+=1;
           geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
       // geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,vertices->size()));
           geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,vertices->size()));
           geode->addDrawable(geometry.get());



        }

            QString strss=m_reg.name + QString::fromUtf8(" (Полнота=%1 % ) ").arg(rrrt);
            text->setText(strss.toStdString(),osgText::String::ENCODING_UTF8);
            osg::ref_ptr<osg::Geode> geod = new osg::Geode();
            geod->addDrawable(text);
            osg::ref_ptr<osg::LOD> lod = new osg::LOD;
            lod->addChild(geod,0,1e8);

            m_transform2->addChild(lod);
      //if(posx.idVeh==0)
         // qDebug()<<"3deddd="<<posx.idVeh<<posx.idKA<<posx.timeBegin<<posx.dopAtribute;
                }


                osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                blendFunc->setFunction(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
             osg::StateSet* state = geode->getOrCreateStateSet();
             state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);

             state->setAttributeAndModes(blendFunc);
             state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
             m_transform = new osg::MatrixTransform;
             m_transform->addChild(geode);


              osg::Matrixd mt;
              mt.setRotate(angel);
              mt.setTrans(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
              m_transform2->setMatrix(mt);
             scene->m_root_gsk->addChild(m_transform);
             scene->m_root_gsk->addChild(m_transform2);

             m_create_object = true;


        }
    }



}
}

bool adddostup::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        if((scene->m_root_gsk->removeChild(m_transform)) )
        {
            m_create_object = false;
           scene->m_root_gsk->removeChild(m_transform2);
            return true;
        }
        else return false;
    }
    return false;
}

