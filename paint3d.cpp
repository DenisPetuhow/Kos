#include "paint3d.h"
#include <QCoreApplication>
#include <QDir>


CPaint3D::CPaint3D()
{
    // Попытка загрузить конфигурацию gamma при создании объекта
    loadGammaConfig("config/satellite_gamma_config.xml");
}

void CPaint3D::loadGammaConfig(const QString& configPath)
{
    // Путь "config/..." относителен ТЕКУЩЕЙ РАБОЧЕЙ ДИРЕКТОРИИ, которая при
    // запуске из Qt Creator может отличаться от папки с исполняемым файлом.
    // Поэтому перебираем несколько типовых расположений.
    QStringList candidates;
    candidates << configPath
               << QCoreApplication::applicationDirPath() + "/" + configPath
               << QCoreApplication::applicationDirPath() + "/../" + configPath
               << "../" + configPath
               << "../../" + configPath;

    for (const QString& path : candidates)
    {
        if (QFile::exists(path) && m_gammaConfig.loadFromXML(path))
        {
            qDebug() << "Конфигурация gamma успешно загружена из" << path;
            return;
        }
    }

    qWarning() << "Не удалось найти" << configPath
               << "- gamma будет рассчитываться геометрически из высоты орбиты."
               << "Рабочая директория:" << QDir::currentPath();
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

            // Устанавливаем уникальный ID для каждого КА
            par.idVeh = i + 1;
            m_ka[i].idVeh = par.idVeh;

            ASDBsePar bse;
            bse.type=COMMUNICATION;

            // Получаем высоту орбиты из TLE или Кеплеровых элементов
            double altitude_km = 500.0; // По умолчанию
            if(m_ka[i].type_dat == 1) {
                // TLE данные - извлекаем высоту из большой полуоси
                QVector<double> kep = ka.getKep(m_time_begin);
                altitude_km = kep[0] - R_EARTH; // a - R_EARTH
            } else {
                // Кеплеровы элементы
                altitude_km = m_ka[i].kep.a - R_EARTH;
            }

            // Получаем имя спутника для поиска в конфигурации
            QString satName = m_ka[i].stle.satName;
            if(m_ka[i].type_dat == 0)
                satName = m_ka[i].kep.name;

            // Геометрический максимум надирного угла: конус касается горизонта Земли.
            // Больше него gamma физически быть не может (конус уйдет за горизонт),
            // а r = h*tan(gamma) при gamma -> 90° стремится к бесконечности.
            double gamma_max_deg = asin(R_EARTH / (R_EARTH + altitude_km)) * RAD_TO_DEG;

            // Получаем gamma из конфигурации (по имени спутника) или расчетом
            if(m_gammaConfig.isLoaded()) {
                bse.gamma = m_gammaConfig.getGammaForSatellite(satName, altitude_km);
            } else {
                bse.gamma = gamma_max_deg;
            }

            // Приоритет ручных настроек из GUI/XML сценария (если заданы)
            if(par.bsa.size() > 0) {
                bse = par.bsa[0];
            }

            // Ограничение: gamma не может превышать геометрический максимум.
            // Небольшой отступ 0.5° чтобы основание конуса не совпадало с горизонтом.
            if(bse.gamma >= gamma_max_deg) {
                bse.gamma = gamma_max_deg - 0.5;
            }
            if(bse.gamma <= 0.0) {
                bse.gamma = 5.0;
            }

            qDebug() << "[+] КА #" << par.idVeh << satName
                     << "| h =" << altitude_km << "км"
                     << "| gamma =" << bse.gamma << "° (макс." << gamma_max_deg << "°)";

            ASDObject3D* orb = new addOrbit(ka);
            m_page->addObject3D(orb);

            // ВАЖНО: пишем gamma НАПРЯМУЮ в m_ka[i].bsa ДО calc_bpla(),
            // иначе БПЛА получит через setKaList(m_ka) пустой bsa
            if(m_ka[i].bsa.size() == 0) {
                m_ka[i].bsa.push_back(bse);
            } else {
                m_ka[i].bsa[0].gamma = bse.gamma;
            }
            par.bsa = m_ka[i].bsa;

            par.nameVeh=m_ka[i].stle.satName;
            if(m_ka[i].type_dat==0)
                par.nameVeh=m_ka[i].kep.name;
            m_ka[i].nameVeh = par.nameVeh;

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
    if(m_BpLA.size()>0)
    {
        for(int i = 0; i < m_BpLA.size(); i++)
        {
            osg::ref_ptr<ASDObject3D> bpla_obj3D = new add_BPLA(m_BpLA[i], m_page);

            // Передаем список КА для проверки видимости
            add_BPLA* bpla_ptr = dynamic_cast<add_BPLA*>(bpla_obj3D.get());
            if(bpla_ptr) {
                bpla_ptr->setKaList(m_ka);
            }

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




