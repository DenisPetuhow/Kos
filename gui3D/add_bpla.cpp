#include "add_bpla.h"
osg::ref_ptr<osg::MatrixTransform> add_BPLA::m_bpla = 0;



add_BPLA::add_BPLA(ASD_bpla_struct _BPLA, QString icon,ASDScene3D * scene)
{
    m_scene = scene;
    m_BPLA = _BPLA;
    m_icon = icon;
    cur_pos_bpla.resize(2);
    lat0_bpla    = _BPLA.lat0_bpla;
    lon0_bpla    = _BPLA.lon0_bpla;
    lat_fin_bpla = _BPLA.lat_fin_bpla;
    lon_fin_bpla = _BPLA.lon_fin_bpla;
    speed_bpla   = _BPLA.speed_bpla;
    t0_runBPLA   = _BPLA.t0_runBPLA;


    az_bpla = get_azimuth(lat0_bpla,lon0_bpla,lat_fin_bpla,lon_fin_bpla);
    cur_pos_bpla[0] = lat0_bpla;
    cur_pos_bpla[1] = lon0_bpla;

    //расчет дальности
    double tp=M_PI/2.-cur_pos_bpla[0]*DEG_TO_RAD;
    double ts=M_PI/2.-lat_fin_bpla*DEG_TO_RAD;
    double fp=cur_pos_bpla[1]*DEG_TO_RAD;
    double fs=lon_fin_bpla*DEG_TO_RAD;
    length_bpla=acos(cos(tp)*cos(ts)+sin(tp)*sin(ts)*cos(fs-fp))*R_EARTH;
    //qDebug()<<" Дальность до цели = "<<length_bpla<<"км"<<icon;
    m_create_object=true;

}

double add_BPLA::get_azimuth(const double lat1, const double lon1, const double lat2, const double lon2)
{
    double tp=M_PI/2.-lat1*DEG_TO_RAD;
    double ts=M_PI/2.-lat2*DEG_TO_RAD;
    double fp=lon1*DEG_TO_RAD;
    double fs=lon2*DEG_TO_RAD;
    double length=acos(cos(tp)*cos(ts)+sin(tp)*sin(ts)*cos(fs-fp));

    double hsm,hsb;
    if(length<50./6371.)
        return atan2((fs-fp)/sin(tp),(tp-ts)+1e-6);

    hsm=atan2(cos((ts-tp)/2)*cos((fs-fp)/2),cos((ts+tp)/2)*sin((fs-fp)/2));
    hsb=atan2(sin((ts-tp)/2)*cos((fs-fp)/2),sin((ts+tp)/2)*sin((fs-fp)/2));

    return (hsm+hsb);
}

QPointF add_BPLA::coordpoint2(QPointF p, double D1, double A1)
{
    QPointF res;
    double A=PiTOPi(A1);
    double FI1=p.y()*DEG_TO_RAD;
    double AL1=p.x()*DEG_TO_RAD;

    double SA=sin(A);
    double CA=cos(A);

    double SX=sin(D1);
    double CX=cos(D1);
    double SF1=sin(FI1);
    double CF1=cos(FI1);
    double FI11=asin(SF1*CX+CF1*SX*CA);
    if(FI11>M_PI)
        FI1=FI11-M_PI;
    double  ALA=asin(SA*SX/cos(FI11));
    if((CX-SF1*sin(FI11))<0.0)
        ALA=M_PI-ALA;
    ALA=ALA+AL1;
    if(ALA>M_PI)
        ALA=ALA-M_PI/2.;
    res.setX(PiTOPi(ALA)*RAD_TO_DEG);
    res.setY(FI11*RAD_TO_DEG);

    return res;
}

double add_BPLA::PiTOPi(double d)
{
    {
        if ( d >= -M_PI && d <= M_PI) return d;

        double modu = fmod(d, M_PI*2);

        if (modu < -M_PI){
            modu += M_PI*2;
        }

        if (modu > M_PI){
            modu -= M_PI*2;
        }

        return modu;
    }
}

QVector<double> add_BPLA::getPos_BpLA(QDateTime dt)
{
    QVector<double> cur_pos(2);

    double s = (speed_bpla) * t0_runBPLA.secsTo(dt)/3600.;
    QPointF aaa = coordpoint2(QPointF(lon0_bpla,lat0_bpla), s/6371.0, az_bpla);
    //qDebug()<<"Dal="<<(length_bpla-s)<<length_bpla<<s<<"dt="<<t0_runBPLA.secsTo(dt);


    if(length_bpla-s >= 0){
        cur_pos[0]=aaa.x(); //x - lon
        cur_pos[1]=aaa.y(); //y - lat
    }else{
        cur_pos[0]=lon_fin_bpla; //x - lon
        cur_pos[1]=lat_fin_bpla; //y - lat
        m_create_object=false;
       // m_scene->removeObject3D(m_transform);

    }

    return cur_pos;
}


void add_BPLA::repaint(QDateTime time, ASDScene3D *scene)
{
    scene->m_root_gsk->removeChild(m_transform);
    cur_pos_bpla = getPos_BpLA(time);
//    if(m_create_object==false){

//    }
    //qDebug()<<cur_pos_bpla;

    if(m_icon.isEmpty()==true)
    {
        QVector<double> coord = ASDCoordConvertor::convGeoToGsc(cur_pos_bpla[1]*DEG_TO_RAD, cur_pos_bpla[0]*DEG_TO_RAD, 10);
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
        point->setSize(100);
        geode->getOrCreateStateSet()->setAttribute(point);
        geode->addDrawable(geometry.get());
        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
        m_transform = new osg::MatrixTransform;
        m_transform->addChild(geode);
        scene->m_root_gsk->addChild(m_transform);


    }
    else
    {
        osg::ref_ptr<osg::MatrixTransform> icon  = scene->addObjectIconPoint(m_icon);
        osg::AutoTransform* at = new osg::AutoTransform;
        at->addChild(icon);
        at->setAutoScaleToScreen(true);
        at->setMinimumScale(0);
        at->setMaximumScale(500);
        m_transform = new osg::MatrixTransform;
        m_transform->addChild(at);
        QVector<double> coord = ASDCoordConvertor::convGeoToGsc(cur_pos_bpla[1]*DEG_TO_RAD, cur_pos_bpla[0]*DEG_TO_RAD, 10);

        osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
        mt4 = osg::Matrix::translate(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));
        mt1 = osg::Matrix::rotate(osg::Quat(cur_pos_bpla[0]*DEG_TO_RAD, osg::Z_AXIS));
        mt2 = osg::Matrix::rotate(osg::Quat(M_PI_2-cur_pos_bpla[1]*DEG_TO_RAD, osg::Y_AXIS));
        mt3 = osg::Matrix::rotate(osg::Quat(M_PI, osg::Z_AXIS));
        mt_sum = mt3*mt2*mt1*mt4;
        m_transform->setMatrix(mt_sum);
        scene->m_root_gsk->addChild(m_transform);
    }



}

bool add_BPLA::remove(ASDScene3D *scene)
{
    if(!scene->view->done())
    {
        scene->m_root_gsk->removeChild(m_transform);

        return true;
    }
    return false;
}
