#include "vizibility.h"

CVizibility::CVizibility()
{
}

QVector <double> CVizibility::calcCoordPicturePlane(QVector<double> X, QDateTime time, ASDAngleMounting angle, double latitude, double longitude)
{
    QVector <double> coordObj_agsk = ASDCoordConvertor::convGscToAgesc(ASDCoordConvertor::convGeoToGsc(latitude, longitude,0),time);

    QVector <double> coordObj_opsc = ASDCoordConvertor::convAgescToOpscRelative(X,coordObj_agsk);
    double r_ka = pow(pow(X[0],2)+pow(X[1],2)+pow(X[2],2),0.5);
    double r_z = pow(pow(coordObj_opsc[0],2)+pow(coordObj_opsc[1],2)+pow(coordObj_opsc[2],2),0.5);
    QVector <double> coordObj_isc = ASDCoordConvertor::convOpscToIsc(r_ka,coordObj_opsc);
    QVector <double> coordObj_conSc = ASDCoordConvertor::convIscToConSc(coordObj_isc,angle);
    double r_xy = pow(pow(coordObj_conSc[0],2)+pow(coordObj_conSc[1],2),0.5);
    double r = pow(pow(coordObj_isc[0],2)+pow(coordObj_isc[1],2)+pow(coordObj_isc[2],2),0.5);

    double D = pow(pow(coordObj_agsk[0]-X[0],2)+pow(coordObj_agsk[1]-X[1],2)+pow(coordObj_agsk[2]-X[2],2),0.5);
    QVector <double> delta;

    double deltaH_real_sin = coordObj_conSc[1]/r_xy;
    double deltaH_real_cos = coordObj_conSc[0]/r_xy;

    double deltaH_real = ASDCoordConvertor::angle(deltaH_real_sin,deltaH_real_cos); //в плоскости XY

    if(deltaH_real>M_PI) deltaH_real -=2*M_PI;

    double deltaV_real_sin = coordObj_conSc[2]/r;
    double deltaV_real_cos = r_xy/r;

    double deltaV_real = ASDCoordConvertor::angle(deltaV_real_sin,deltaV_real_cos); //в плоскости YZ
    if(deltaV_real>M_PI) deltaV_real -=2*M_PI;



    delta.append(deltaV_real); //рыскание
    delta.append(deltaH_real); //тангаж
    delta.append(D); //дальность от КА до объекта

    return delta;
}

QVector<double> CVizibility::calcCoordObjInIsc(ASDAngleMounting angle, double D)
{
    double x,y,z,D_xy;
    y = D*sin(angle.pitch);
    D_xy = D*cos(angle.pitch);
    x = D_xy*cos(angle.yaw);
    z = D_xy*sin(angle.yaw);
    QVector <double> X;
    X.append(x);
    X.append(y);
    X.append(z);
    return X;
}

QVector<double> CVizibility::convConScToAGSK(QVector<double> coord_vehicle, QVector<double> coord_target,ASDAngleMounting angle_eqip)
{
    double r = pow(pow(coord_vehicle[0],2)+pow(coord_vehicle[1],2)+pow(coord_vehicle[2],2),0.5);
    QVector<double> coord_Ics = ASDCoordConvertor::convConScToIsc(coord_target,angle_eqip);
    QVector<double> coord_Opsc = ASDCoordConvertor::convIscToOpsc(r,coord_Ics);
    QVector<double> coord_agsk = ASDCoordConvertor::convOpscToAgescRelative(coord_vehicle,coord_Opsc);
    return coord_agsk;
}

QVector<QVector<double> > CVizibility::calcPiramidObzor(QVector<double> coord_vehicle, ASDAngleMounting angle_eqip, double deltaV, double deltaH)
{
    QVector<double> coord_target(6,0.);
    coord_target[0] = 500; //произвольная дальность до точки
    coord_target[1] = 0;
    coord_target[2] = 0;

    ASDAngleMounting angle_eqip_mod;
    angle_eqip_mod = angle_eqip;
    angle_eqip_mod.yaw -= deltaV;
    QVector<double> point_1;
    bool resould = false;
    QVector<double> point_1_agsk;
    while(resould == false)
    {
    point_1 = convConScToAGSK(coord_vehicle,coord_target,angle_eqip_mod);
    point_1_agsk = calcInterLineWithEarth(coord_vehicle,point_1,resould);
    angle_eqip_mod.yaw += deltaV/10.;
    }

    angle_eqip_mod = angle_eqip;
    angle_eqip_mod.yaw += deltaV;
    QVector<double> point_2;
    resould = false;
    QVector<double> point_2_agsk;
    while(resould == false)
    {
    point_2 = convConScToAGSK(coord_vehicle,coord_target,angle_eqip_mod);
    point_2_agsk = calcInterLineWithEarth(coord_vehicle,point_2,resould);
    angle_eqip_mod.yaw -= deltaV/10.;
    }
    QVector<QVector<double> > points(2);
    points[0] = point_1_agsk;
    points[1] = point_2_agsk;
    return points;
}

QVector<ASDPointEarth> CVizibility::calcKonusObzor(QVector<double> coord_vehicle, QDateTime time, double gamma, int count_points)
{
    double r_ka = pow(pow(coord_vehicle[0],2)+pow(coord_vehicle[1],2)+pow(coord_vehicle[2],2),0.5);
    double gama_pred = asin(R_EARTH/r_ka);
    if(gamma>gama_pred)
        gamma = gama_pred;
    double teta = acos(r_ka*sin(gamma)/R_EARTH);
    double fi = M_PI_2-teta-gamma;
    QVector<double> coord_geo = ASDCoordConvertor::convGscToGeo(ASDCoordConvertor::convAgescToGsc(coord_vehicle,time));
    QVector<ASDPointEarth> points;
    for(int i=0; i<count_points; i++)
    {
        ASDPointEarth point;
        QVector<double> coord(4,0);
        double Azimus = 2*M_PI/count_points*i;
        ASDGeoTask::SphereDirect(coord_geo,Azimus,fi,coord);
        point.height = 0;
        point.latitude = coord[0];
        point.longitude = coord[1];
        points.append(point);
    }
    return points;
}

double CVizibility::calcElevationSun(QDateTime time, double lat, double longitude)
{   SunPosition sun;
    QVector<double> sun_agsk = sun.getPosition(time);
    QVector<double> coord = ASDCoordConvertor::calcAzimuth_Elevetion(sun_agsk,lat,longitude,time);
    return coord[1];
}

int CVizibility::root2 ( double a, double b, double * x )
{
    if ( b == 0 )
    {
        x[0] = -a;
        x[1] = 0.;
    }
    else
    {
        a *= -0.5;
        double d = a * a - b;
        if ( d < 0 ) return 0;
        d = sqrt ( d );
        x[0] = a > 0 ? a + d : a - d;
        x[1] = b / x[0];
    }
    return 2;
}

/*!
 * \brief Расчитывает координаты пересечение прямой проходящей через две точки с Землей
 * \return
 */
QVector <double> CVizibility::calcInterLineWithEarth(QVector<double> coord0,QVector<double> coord1, bool& resould)
{
    double A, B, C, D, K, A1, B1, C1, A_, B_;
    QVector <double> coord_reg1(3),coord_reg2(3), coord_reg_agsk;

    A = (coord1[0]-coord0[0])/(coord1[1]-coord0[1]);
    B = (coord1[2]-coord0[2])/(coord1[1]-coord0[1]);
    C = A*A + B*B;
    D = 2*A*coord0[0]+2*B*coord0[2];
    K = coord0[0]*coord0[0] + coord0[2]*coord0[2];
    A1 = C+1;
    B1 = D - 2*C*coord0[1];
    C1 = C*coord0[1]*coord0[1]-D*coord0[1]+K - R_EARTH*R_EARTH;
    A_ = B1/A1;
    B_ = C1/A1;
    double X[2], r1, r2;
    if(root2(A_,B_,X) ==2)
    {
        coord_reg1[1] = X[0];
        coord_reg2[1] = X[1];

        coord_reg1[0] = A*(coord_reg1[1]-coord0[1])+coord0[0];
        coord_reg1[2] = B*(coord_reg1[1]-coord0[1])+coord0[2];

        coord_reg2[0] = A*(coord_reg2[1]-coord0[1])+coord0[0];
        coord_reg2[2] = B*(coord_reg2[1]-coord0[1])+coord0[2];

        r1 = pow(pow(coord_reg1[0]-coord0[0],2)+pow(coord_reg1[1]-coord0[1],2)+pow(coord_reg1[2]-coord0[2],2),0.5);
        r2 = pow(pow(coord_reg2[0]-coord0[0],2)+pow(coord_reg2[1]-coord0[1],2)+pow(coord_reg2[2]-coord0[2],2),0.5);
        resould = true;
        if(r2>r1)
        {
            coord_reg_agsk = coord_reg1;
        }
        else
        {
            coord_reg_agsk = coord_reg2;

        }
        return coord_reg_agsk;
    }
    resould = false;
}















