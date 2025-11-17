#include "addorbit.h"

//addOrbit::addOrbit()
//{

//}




addOrbit::addOrbit(ASDOrbitalVehicle ka)
{
    m_ka = ka;

    m_create_object = false;
    m_create_object_NO = true;

}

void  addOrbit::repaint(QDateTime time, ASDScene3D *scene)
{
     QDateTime timecur=time;

   //if(m_create_object_NO) //создавать ли объект
 if(!scene->view->done())
    {
    if(m_create_object == false)
        {



m_orb=0;
m_transform=0;
           scene->m_root_gsk->removeChild(m_orb);
            scene->m_root_gsk->removeChild(m_transform);
            m_orb = new osg::MatrixTransform;
            QVector<double> coord = m_ka.getCurrPos(timecur);


             QVector<double> coordKA = ASDCoordConvertor::convAgescToKsc(coord);
            //QVector<double> coordKA = ASDCoordConvertor::convAgescToKsc(ASDCoordConvertor::convAgescToGsc(coord,time));

             double i = coordKA[0];
             double omega = coordKA[1];
             double w = coordKA[2];
             double p = coordKA[3];
             double e = coordKA[4];
             double u = coordKA[5];
             double r, x, y;
omega_old=omega;
             osg::ref_ptr<osg::Geometry> kaX (new osg::Geometry);
             osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
             osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
             for (int v = 0; v < 360; v += 5)
             {
                 r = p / (1.0 + e * cos(v * DEG_TO_RAD));
                 x = r * cos(v * DEG_TO_RAD);
                 y = r * sin(v * DEG_TO_RAD);

                // glVertex3f(x *1000., y * 1000., r*1000.);

                QVector<double> kepl1(6);

                kepl1[0]=coordKA[0];
                kepl1[1]=coordKA[1];
                kepl1[2]=coordKA[2];
                kepl1[3]=coordKA[3];
                kepl1[4]=coordKA[4];
                kepl1[5]=v* DEG_TO_RAD;

                 QVector<double> kepag= ASDCoordConvertor::convKscToAgesc(kepl1);

                  points->push_back(osg::Vec3(kepag[0]*1000.,kepag[1]*1000.,kepag[2]*1000.));
                  color->push_back(osg::Vec4(1.0,1,0,0.7));
             }
             kaX->setVertexArray(points);
             kaX->setColorArray(color);
             kaX->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
             kaX->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,72));
             kaX->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(1.0f) );
             osg::ref_ptr<osg::Geode> geod = new osg::Geode();
             geod->addDrawable(kaX.get());

             osg::StateSet* state = geod->getOrCreateStateSet();
             osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
             state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
             osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
             blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
             state->setAttributeAndModes( blendFunc );
             state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
             state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON  );
             m_orb->addChild(geod);
             m_transform = new osg::MatrixTransform();
             m_transform->addChild(m_orb.get());
             scene->m_root_agsk->addChild(m_transform.get());

       //  osg::Matrix mt1,mt2,mt3,mt_sum,mt0,mt00,mt20;
         //PQW = ReferenceFrames::Rz(-Omega)
         //    * ReferenceFrames::Rx(-i)
         //    * ReferenceFrames::Rz(-omega);
//
         //ZEMMM
//         osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
//         mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
//         mt1 = osg::Matrix::rotate(osg::Quat(m_p.longitude, osg::Z_AXIS));
//         mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2-m_p.latitude, osg::Y_AXIS));
//         mt3 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
//         mt_sum = mt3*mt2*mt1*mt4;
//         m_transform->setMatrix(mt_sum);

         //
//          mt1 = osg::Matrix::rotate(osg::Quat(omega, osg::Z_AXIS));
//          mt2 = osg::Matrix::rotate(osg::Quat(i, osg::X_AXIS));
//         mt3 = osg::Matrix::rotate(osg::Quat(u*cos(i), osg::Z_AXIS));
//          // mt3 = osg::Matrix::rotate(osg::Quat(-omega, osg::Z_AXIS));
/////mt0=osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
//mt0 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
//mt20= osg::Matrix::rotate(osg::Quat(M_PI_2-u*cos(i), osg::Y_AXIS));
//           mt_sum =mt3*mt2*mt1;
//           mt00=mt0*mt20*mt_sum;
     //   m_transform->setMatrix(mt_sum);

        m_create_object = true;

        }
       else
        {
           QVector<double> coord = m_ka.getCurrPos(time);
           QVector<double> coordKA = ASDCoordConvertor::convAgescToKsc(coord);
          //QVector<double> coordKA = ASDCoordConvertor::convAgescToKsc(ASDCoordConvertor::convAgescToGsc(coord,time));

           double i = coordKA[0];
           double omega = coordKA[1];
           double w = coordKA[2];
           double p = coordKA[3];
           double e = coordKA[4];
           double u = coordKA[5];
           osg::Matrix mt3;

             mt3 = osg::Matrix::rotate(osg::Quat(-(omega_old-omega), osg::Z_AXIS));


            m_transform->setMatrix(mt3);

//            ASDInterLocation m_c;
//            QVector<double> coordEnd(3);
//            QVector<double> coord0(3, 0.);
//            coordEnd = m_c.calcInterLineWithEarth(coord, coord0);
//            QVector <double> coordRes(3);
//            coordRes[0] = (coordEnd[0]-coord[0])*1000.;
//            coordRes[1] = (coordEnd[1]-coord[1])*1000.;
//            coordRes[2] = (coordEnd[2]-coord[2])*1000.;
//            double h1 = pow(coordRes[0]*coordRes[0]+coordRes[1]*coordRes[1]+coordRes[2]*coordRes[2],0.5);
//            double h2 = pow(coordRes[0]*coordRes[0]+coordRes[1]*coordRes[1],0.5);
//            double beta = asin(coordRes[2]/h1);
//            double alfa=0;
//            if(h2 != 0)
//            {
//                alfa = ASDCoordConvertor::angle(coordRes[1]/h2,coordRes[0]/h2);
//            }
//            osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
//            mt1 = osg::Matrix::rotate(osg::Quat(-M_PI/2., osg::Y_AXIS));
//            mt2 = osg::Matrix::rotate(osg::Quat(alfa, osg::Z_AXIS));
//            mt3 = osg::Matrix::rotate(osg::Quat(-beta, osg::Y_AXIS));
//          //  mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000.,coord[1]*1000.,coord[2]*1000.));
//            mt_sum = mt1*mt3*mt2;
//            m_transform->setMatrix(mt_sum);
        }
    }
}

bool addOrbit::remove(ASDScene3D *scene)
{
      scene->m_root_agsk->removeChild(m_transform);
    //  scene->m_root_agsk->removeChild(m_orb);
   //if(!scene->view->done())
    {


    if(scene->m_root_agsk->removeChild(m_orb))
    {

      //   m_create_object = false;

        m_create_object_NO=true;
         return true;
    }
   }
    return false;
}

