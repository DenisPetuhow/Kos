#include "calc_bpla_plan.h"



Calc_bpla_plan::Calc_bpla_plan()
{
    vec_BpLA.clear();
}

Calc_bpla_plan::~Calc_bpla_plan()
{

}

double PiTOPi(double d)
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





void Calc_bpla_plan::set_BpLA(ASD_bpla_struct _BpLA)
{

    _BpLA.az_bpla = get_azimuth(_BpLA.lat0_bpla,_BpLA.lon0_bpla,_BpLA.lat_fin_bpla,_BpLA.lon_fin_bpla);
    _BpLA.length_bpla=calc_length(_BpLA);

    vec_BpLA.push_back(_BpLA);
    mainCalc_BpLA();
}

void Calc_bpla_plan::set_KA(QVector<ASDOrbitalObjectPar> _vecOrb)
{
    vec_Orb=_vecOrb;
}

QPointF Calc_bpla_plan::coordpoint2(QPointF p, double D1, double A1)
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

double Calc_bpla_plan::get_azimuth(const double lat1, const double lon1, const double lat2, const double lon2)
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

QMap<int, t_plan_bpla> Calc_bpla_plan::get_BpLA()
{

    return mapBpLA_KA;
}

double Calc_bpla_plan::calc_length(ASD_bpla_struct _BpLA)
{
    double tp=M_PI/2.-_BpLA.lat0_bpla*DEG_TO_RAD;
    double ts=M_PI/2.-_BpLA.lat_fin_bpla*DEG_TO_RAD;
    double fp=_BpLA.lon0_bpla*DEG_TO_RAD;
    double fs=_BpLA.lon_fin_bpla*DEG_TO_RAD;

    double length_bpla=acos(cos(tp)*cos(ts)+sin(tp)*sin(ts)*cos(fs-fp))*R_EARTH;

    return length_bpla;
}




QVector<double> Calc_bpla_plan::getPos_BpLA(QDateTime dt, ASD_bpla_struct _BpLA)
{
    QVector<double> cur_pos(3);

    double s = (_BpLA.speed_bpla) * _BpLA.t0_runBPLA.secsTo(dt)/3600.;
    QPointF aaa = coordpoint2(QPointF(_BpLA.lon0_bpla,_BpLA.lat0_bpla), s/6371.0, _BpLA.az_bpla);


    if(_BpLA.length_bpla-s >= 0){
        cur_pos[0]=aaa.x(); //x - lon
        cur_pos[1]=aaa.y(); //y - lat
    }else{
        cur_pos[0]=_BpLA.lon_fin_bpla; //x - lon
        cur_pos[1]=_BpLA.lat_fin_bpla; //y - lat

    }
    cur_pos[2]=s;
    return cur_pos;
}

void Calc_bpla_plan::mainCalc_BpLA()
{
    ASDOrbitalMotion OrbitMotion;
    ASD_bpla_struct _BpLA;


    _BpLA = vec_BpLA.last();
    QVector<double> curPosBpLA;
    curPosBpLA.resize(3);
    QVector<double> posOrb(6);
    t_plan_bpla plan;


    double dt = (_BpLA.length_bpla/_BpLA.speed_bpla) * 3600; // Общее время полета
    //qDebug()<<"Дальность="<<_BpLA.length_bpla<<"Скорость="<<_BpLA.speed_bpla<<"Время полета, с="<<dt
    //<<"интервал="<<_BpLA.time_interval<<"Количество интервалов="<<(int)(dt/_BpLA.time_interval);


    //Заполнение стринглиста с подписями (для гистограммы)
    result_list.clear();
    for(int i = 0; i< (int)(dt/_BpLA.time_interval);i++){
        result_list.append(QString("%1").arg((i+1)*_BpLA.time_interval));

    }
    //qDebug()<<result_list;
    ///////////////////////////////////////////////////////////////




    //расчет положения БпЛА и КА на каждом интервале времени
    QVector<double> _vec;
    _vec.clear();
    for(int i_dt = 0; i_dt < (int)(dt/_BpLA.time_interval); i_dt++){
        QDateTime time =_BpLA.t0_runBPLA.addSecs((qint64)_BpLA.time_interval*i_dt);
        curPosBpLA = getPos_BpLA(time,_BpLA);
        int countKA=0;
        //вычисление позиций КА
        for(int j = 0; j<vec_Orb.size();j++){
            ASDOrbitalObjectPar _obj = vec_Orb[j];
            ASDOrbitalVehicle ka(_obj);

            QVector<double> coordKA = ka.getCurrPos(time);

            // Gamma КА - ТА ЖЕ, что у зеленого конуса и 3D-линий.
            // Если bsa не заполнен (план считается до CPaint3D::calc()),
            // iszone возьмет геометрический максимум из высоты КА.
            double gamma_deg = -1.0;
            if(_obj.bsa.size() > 0)
                gamma_deg = _obj.bsa[0].gamma;

            bool inZone = iszone(time,coordKA,curPosBpLA,gamma_deg);

            if(inZone == true){

                plan.KA = vec_Orb[j];
                plan.time=time;

                mapBpLA_KA.insertMulti(_BpLA.id_bpla,plan);
                countKA++;
            }
        }

        _vec.push_back(countKA);

    }
    result_vec.push_back(_vec);

}

// ═══════════════════════════════════════════════════════════════════════════
// ПРОВЕРКА ПОПАДАНИЯ БПЛА В ЗОНУ ПОКРЫТИЯ КА
//
// Геометрия согласована с зеленым конусом (addCone) и 3D-линиями
// (add_BPLA::isKaVisible): проверяется НАДИРНЫЙ угол - угол между осью
// конуса (КА -> центр Земли) и вектором (КА -> БПЛА). БПЛА в зоне <=>
// надирный угол < gamma и КА над горизонтом БПЛА.
//
// Старая версия сравнивала фиксированный порог 30° с углом МЕСТА от БПЛА -
// другая геометрия, из-за чего гистограмма не совпадала с 3D-линиями.
// Вдобавок lat/lon передавались в convGscToSsc в ГРАДУСАХ, а функция ждет
// РАДИАНЫ - топоцентрическая система строилась неверно.
// ═══════════════════════════════════════════════════════════════════════════
bool Calc_bpla_plan::iszone(QDateTime curr_time, QVector<double> posOrb,
                            QVector<double> posBpLA, double gamma_deg)
{
    ASDCoordConvertor conv;

    // 1. Обе точки в ГСК на момент времени, км
    QVector<double> ka_gsc = conv.convAgescToGsc(posOrb, curr_time);
    QVector<double> bpla_gsc = ASDCoordConvertor::convGeoToGsc(
        posBpLA[1] * DEG_TO_RAD,   // lat, радианы
        posBpLA[0] * DEG_TO_RAD,   // lon, радианы
        BPLA_ALT_KM);

    // 2. Если gamma не задан - геометрический максимум из фактической
    //    высоты КА (как в CPaint3D::calc при отсутствии конфигурации)
    double r_ka = sqrt(ka_gsc[0]*ka_gsc[0] + ka_gsc[1]*ka_gsc[1] + ka_gsc[2]*ka_gsc[2]);
    if(gamma_deg <= 0.0)
    {
        double h = r_ka - R_EARTH;
        if(h < 1.0) h = 1.0;
        gamma_deg = asin(R_EARTH / (R_EARTH + h)) * RAD_TO_DEG - 0.5;
    }

    // 3. Ось конуса: от КА к центру Земли (надир)
    double ax = -ka_gsc[0];
    double ay = -ka_gsc[1];
    double az = -ka_gsc[2];

    // 4. Вектор от КА к БПЛА
    double bx = bpla_gsc[0] - ka_gsc[0];
    double by = bpla_gsc[1] - ka_gsc[1];
    double bz = bpla_gsc[2] - ka_gsc[2];

    double na = sqrt(ax*ax + ay*ay + az*az);
    double nb = sqrt(bx*bx + by*by + bz*bz);
    if(na < 1e-9 || nb < 1e-9)
        return false;

    // 5. Надирный угол
    double cos_nadir = (ax*bx + ay*by + az*bz) / (na * nb);
    if(cos_nadir > 1.0)  cos_nadir = 1.0;
    if(cos_nadir < -1.0) cos_nadir = -1.0;
    double nadir_angle = acos(cos_nadir);

    if(nadir_angle > gamma_deg * DEG_TO_RAD)
        return false;

    // 6. КА над горизонтом БПЛА: скалярное произведение зенита БПЛА
    //    (направление bpla_gsc от центра Земли) и вектора БПЛА->КА > 0
    double vx = ka_gsc[0] - bpla_gsc[0];
    double vy = ka_gsc[1] - bpla_gsc[1];
    double vz = ka_gsc[2] - bpla_gsc[2];
    double elev_dot = bpla_gsc[0]*vx + bpla_gsc[1]*vy + bpla_gsc[2]*vz;
    if(elev_dot <= 0.0)
        return false;

    // Для совместимости сохраняем угол места (использовался через поле ell)
    double nv = sqrt(vx*vx + vy*vy + vz*vz);
    double nu = sqrt(bpla_gsc[0]*bpla_gsc[0] + bpla_gsc[1]*bpla_gsc[1] + bpla_gsc[2]*bpla_gsc[2]);
    if(nv > 1e-9 && nu > 1e-9)
        ell = asin(elev_dot / (nv * nu));

    return true;
}

