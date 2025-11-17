#include "paint3d.h"
#include "QPixmap"


CPaint3D::CPaint3D()
{

}
void CPaint3D::setPlan(QVector<ASDZoneVisible> zone)
{
    m_zone.clear();
    m_zone = zone;
}
void CPaint3D::setzonobz( QMap<QDateTime,  QPolygonF>  kazon)
{
    m_kazon.clear();
    m_kazon= kazon;
}


void CPaint3D::setBpLA(QVector<ASD_bpla_struct> _bpla)
{
    m_BpLA.clear();
    m_BpLA = _bpla;

}


void CPaint3D::setKa(QVector<ASDOrbitalObjectPar> ka_full)
{
    m_ka.clear();
    m_ka = ka_full;
}

void CPaint3D::setOkik(QVector<ParamGrContrCentr> okik)
{
    m_okik.clear();
    m_okik = okik;
}

void CPaint3D::setCoordKA(QVector<QMap<QDateTime, QVector<double> > > coord_ka)
{
    m_coord_ka.clear();
    m_coord_ka = coord_ka;
}

void CPaint3D::setTime(QDateTime time_begin, QDateTime time_end)
{
    m_time_begin = time_begin;
    m_time_end = time_end;


}
void CPaint3D::setBox(QVector<Paramregion> region)
{
    m_region.clear();
    m_region = region;
}
void CPaint3D::setpointreg(QVector<ParamregionO> regionp,QMap<QDateTime,  ASDZoneVisible> mapP)
{
    m_mapP.clear();
    m_regionp = regionp;
    m_mapP=mapP;

}

void CPaint3D::set3D(ASDScene3D *page)
{
    m_page = page;
    m_page->setEnabled(true);
}

void CPaint3D::calc()
{

    if(m_ka.size()>0)
    {
        for(int i  =0; i<m_ka.size(); i++)
        {
            if(m_ka[i].type_dat==0)

            {
                m_ka[i].kep.i*=DEG_TO_RAD;
                m_ka[i].kep.l*=DEG_TO_RAD;
                m_ka[i].kep.omega*=DEG_TO_RAD;
                m_ka[i].kep.u*=DEG_TO_RAD;

            }
            ASDOrbitalVehicle ka(m_ka[i]);

            ASDOrbitalObjectPar par(m_ka[i]);
            ASDBsePar bse;
            bse.type=COMMUNICATION;
            bse.gamma=asin(R_EARTH/(R_EARTH + 500.))*RAD_TO_DEG; //g

            ASDObject3D* orb = new addOrbit(ka);
            m_page->addObject3D(orb);

            for(int i  =0; i<par.bsa.size(); i++)
            {
                bse = par.bsa[i];
            }
            par.nameVeh=m_ka[i].stle.satName;
            if(m_ka[i].type_dat==0)
                par.nameVeh=m_ka[i].kep.name;

            osg::ref_ptr<ASDObject3D> KA = new ASDOrbitVeh3D(ka,par);
            m_page->addObject3D(KA);

            QMap<QDateTime,  int> m_mapK;
            if(bse.type == COMMUNICATION)
            {
                ASDObject3D * Cone = new addCone(ka, bse,m_mapK);
                m_page->addObject3D(Cone);
            }
        }
    }


}

void CPaint3D::calc_bpla()
{
    QPixmap originalIcon("images/bpl.png");
    //QPixmap resizeIcon =

    QString icon = QString("images/bpl.png");

    //addPoint(m_root_agsk,coord,image);



    if(m_BpLA.size()>0)
    {
        for(int i  =0; i<m_BpLA.size(); i++)
        {
            osg::ref_ptr<ASDObject3D> bpla_obj3D= new add_BPLA(m_BpLA[i],icon,m_page);
            m_page->addObject3D(bpla_obj3D);
        }
    }

}

void CPaint3D::repaint(QDateTime time)
{
    removeObject(time);
    m_page->repaintObjects3D(time);

}

void CPaint3D::removeObject(QDateTime time)
{
    if(m_object.size()==0) return;
    QMap<QDateTime,osg::ref_ptr<ASDObject3D> >::Iterator iter = m_object.begin();
    for(; iter !=m_object.end(); iter++)
    {
        if(iter.key()<time)
        {
            bool uspex =  m_page->removeObject3D(iter.value());
            if(uspex)
            {
                m_object.erase(iter);

            }
            break;
        }else break;
    }
}

void CPaint3D::clear()
{
    m_page->clear();
    m_object.clear();
}




