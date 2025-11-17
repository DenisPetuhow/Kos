#include "addpng.h"
#include <QDebug>
#include "osg/BlendColor"
osg::ref_ptr<osg::MatrixTransform> addpng::m_png = 0;

addpng::addpng(double min_lat,double max_lat,double min_lon,double max_lon,QString filepng)
{
     m_min_lat=min_lat;
     m_max_lat=max_lat;
     m_min_lon=min_lon;
     m_max_lon=max_lon;
     m_filepng=filepng;
    m_create_object = false;
    m_create_object_NO = true;


}
//void addCone::setzon(QMap<QDateTime,int> mapP)
//{
//  m_map=mapP  ;
//}

void  addpng::repaint(QDateTime tim, ASDScene3D *scene)
{
    if(!scene->view->done())
    {
    QDateTime time=tim;
    if(m_create_object_NO) //создавать ли объект
    {
        if(m_create_object == false)
        {
            m_png = new osg::MatrixTransform;
              osg::ref_ptr<osg::Geometry> geometryN (new osg::Geometry());
            osg::Vec3Array *coords = new osg::Vec3Array;
             osg::Vec3Array *coordsi = new osg::Vec3Array;
            osg::Vec4Array *carr = new osg::Vec4Array;
            osg::Vec2Array *tcs = new osg::Vec2Array;
              osg::Vec2Array *tcsi = new osg::Vec2Array;
            int dlon=(int)((m_max_lon-m_min_lon)/5.);
            int fff=0.2;
            double xs,ys,zs;
           //  for(int i1=0;i1<5;i1++)



            for (double lat=m_min_lat;lat<= m_max_lat;lat+=5.0)
            {
                for (double lon=m_min_lon;lon< m_max_lon;lon+=5.0)
                {






float dll=fff+0.5;


                    float xu=(lat-m_min_lat)/(m_max_lat-m_min_lat);
                    float xv=(lon-m_min_lon)/(m_max_lon-m_min_lon);
                    QVector<double>  xyz=ASDCoordConvertor::convGeoToGsc(lat*DEG_TO_RAD,lon*DEG_TO_RAD,600.);
xs=xyz[0]*1000;
ys=xyz[1]*1000;
zs=xyz[2]*1000;
                   // coords->push_back(osg::Vec3(xyz[0]*1000,xyz[1]*1000,xyz[2]*1000+dll));
                    coords->push_back(osg::Vec3(xyz[0]*1000,xyz[1]*1000,xyz[2]*1000+dll));
                      tcs->push_back(osg::Vec2(xv,xu));

//                    //2
//                    QVector<double>  xyz1=ASDCoordConvertor::convGeoToGsc(lat*DEG_TO_RAD,(lon+dlon)*DEG_TO_RAD,600.);

//                    coords->push_back(osg::Vec3(xyz1[0]*1000,xyz1[1]*1000,xyz1[2]*1000+dll));
//                    //3
//                      tcs->push_back(osg::Vec2(xv,xu));

//                    QVector<double>  xyz2=ASDCoordConvertor::convGeoToGsc(lat*DEG_TO_RAD,(lon-dlon)*DEG_TO_RAD,600.);

//                    coords->push_back(osg::Vec3(xyz2[0]*1000,xyz2[1]*1000,xyz2[2]*1000+dll));


//                    tcs->push_back(osg::Vec2(xv,xu));


//                    coords->push_back(osg::Vec3(xyz[0]*1000,xyz[1]*1000,xyz[2]*1000+dll));


//                    tcs->push_back(osg::Vec2(xv,xu));
//carr->push_back(osg::Vec4(0.1,0.5,0.8,0.7));

                }
            }

           for(int i1=0;i1<5;i1++)
            {
               if(i1< 3) fff=0.1;
               for(int i2=0;i2<5;i2++)
                 {
                     if(i2>3) fff=0.2;
          for(int i=0;i<coords->size()-(dlon+1);i++)

           {

                coordsi->push_back(coords->at(i));
                coordsi->push_back(coords->at(i+dlon));
                coordsi->push_back(coords->at(i+dlon+1));
                coordsi->push_back(coords->at(i+1));
                tcsi->push_back(tcs->at(i));
                tcsi->push_back(tcs->at(i+dlon));
                tcsi->push_back(tcs->at(i+dlon+1));
                tcsi->push_back(tcs->at(i+1));

          }
                 }
            }

            //



            //






              geometryN->setVertexArray(coordsi);
            //  geometryN->setColorArray(carr);
              geometryN->setTexCoordArray(0,tcsi);
              geometryN->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,coordsi->size()));

qDebug()<<"stat";

               osg::StateSet* state = geometryN->getOrCreateStateSet();

               osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile("1233.png");
               if (image)
                  {
                   qDebug()<<"mvg";
                     // osg::Texture2D* texture = new osg::Texture2D;
                       osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
                      texture->setImage(image);
                      texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP);
                   //   texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP);
                      state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
                      state->setMode( GL_LIGHTING, osg::StateAttribute::ON);
                      state->setTextureAttributeAndModes( 0, texture.get() );

                     // state->setAttributeAndModes(blendFunc1);
                  }


              // geometryN->setStateSet( state );
qDebug()<<"ivg";
               osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
               state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
              osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
                blendFunc->setFunction( GL_ONE_MINUS_DST_COLOR,GL_SRC_ALPHA );
              state->setAttributeAndModes( blendFunc );
               state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
           state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );
                osg::ref_ptr<osg::Geode> geod = new osg::Geode();
             geod->addDrawable(geometryN.get());


qDebug()<<"pngend";


            m_png->addChild(geod);
qDebug()<<"0end";
    m_transform = new osg::MatrixTransform;

    osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
   mt4 = osg::Matrix::translate(xs-6358000,ys-6358000,zs-6358000);
    mt1 = osg::Matrix::rotate(osg::Quat(m_max_lon*DEG_TO_RAD, osg::Z_AXIS));
    mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2-m_max_lat*DEG_TO_RAD, osg::Y_AXIS));
    mt3 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
    mt_sum = mt3*mt2*mt1*mt4;
  //  m_transform->setMatrix(mt3);

         m_transform->addChild(geod.get());


            qDebug()<<"1end";
            scene->m_root_gsk->addChild(m_transform.get());
            m_create_object = true;
            qDebug()<<"2end";
//m_create_object = false;//?/////////////?
        }

    }
    }

}

bool addpng::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_agsk->removeChild(m_transform);
        return true;
    }
    return false;
}

