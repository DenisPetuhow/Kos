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
            bool inZone = iszone(time,coordKA,curPosBpLA);

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

bool Calc_bpla_plan::iszone(QDateTime curr_time, QVector<double> posOrb, QVector<double> posBpLA)
{
    bool to_returv = false;
    ASDCoordConvertor conv;

    QVector<double> coord_scc(6, 0);

    double Azim;
    double Elev;
    double r;
    double elmin =30*DEG_TO_RAD;


    coord_scc = conv.convGscToSsc(conv.convAgescToGsc(posOrb,curr_time),posBpLA[1],posBpLA[0],0.0);
    if (coord_scc[1] > -100)
    {

        r = pow(coord_scc[0] * coord_scc[0] + coord_scc[1] * coord_scc[1]
                + coord_scc[2] * coord_scc[2], 0.5);
        Elev = conv.angle(coord_scc[1] / r, pow(coord_scc[0] * coord_scc[0]
                + coord_scc[2] * coord_scc[2], 0.5) / r);
        Azim= conv.angle(coord_scc[2]/ pow(coord_scc[0] * coord_scc[0]+ coord_scc[2] * coord_scc[2], 0.5),
                coord_scc[0]/ pow(coord_scc[0] * coord_scc[0]+ coord_scc[2] * coord_scc[2], 0.5));

        if(Elev>M_PI)
            Elev = 2*M_PI-Elev;

        if ((Azim) < 0)
            Azim += 2 * M_PI;


        if(elmin < Elev)
        {
            ell=Elev;
            to_returv = true;
            return to_returv;
        }
        else
        {
            return false;
        }
    }

    return to_returv;

}

