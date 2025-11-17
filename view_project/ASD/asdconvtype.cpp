#include "asdconvtype.h"

ASDConvType::ASDConvType()
{
}

ASDPosObj ASDConvType::convVectorPosToPosObj(QVector<double> coord, QDateTime time_real, double time)
{
    ASDPosObj coord_1;

    coord_1.x = coord[0];
    coord_1.y = coord[1];
    coord_1.z = coord[2];
    coord_1.Vx = coord[3];
    coord_1.Vy = coord[4];
    coord_1.Vz = coord[5];
    coord_1.time_real = time_real;
    coord_1.time = time;

    return coord_1;

}

QVector<double> ASDConvType::convPosObjToVectorPos(ASDPosObj coord)
{
    QVector <double> coord_1(6,0);

    coord_1[0] = coord.x;
    coord_1[1] = coord.y;
    coord_1[2] = coord.z;
    coord_1[3] = coord.Vx;
    coord_1[4] = coord.Vy;
    coord_1[5] = coord.Vz;

    return coord_1;
}

QVector<ASDCoordObj> ASDConvType::convPosToCoordObj(QVector<ASDPosObj> coord)
{
    ASDCoordObj t_coord;
    QVector<ASDCoordObj> coord_1;
    for(int i=0; i<coord.size(); i++)
    {
        t_coord.time = coord[i].time;
        t_coord.x = coord[i].x;
        t_coord.y = coord[i].y;
        t_coord.z = coord[i].z;
        coord_1.append(t_coord);
    }

    return coord_1;
}

QVector<ASDPointEarth> ASDConvType::convPosObjToPointEarth(QVector<ASDPosObj> coord)
{
    QVector<ASDPointEarth> coord_st;
    ASDPointEarth coord_point;
    QVector <double> coord_t;
    QVector <double> coord_geo;
    for(int i = 0; i<coord.size(); i++)
    {
        coord_t = convPosObjToVectorPos(coord[i]);
        coord_geo = ASDCoordConvertor::convGscToGeo(ASDCoordConvertor::convAgescToGsc(coord_t,coord[i].time_real));

        coord_point.latitude = coord_geo[0];
        coord_point.longitude = coord_geo[1];
        coord_point.height = coord_geo[2];
        coord_st.append(coord_point);
    }
    return coord_st;
}

ASDPointEarth ASDConvType::convPosObjToPointEarth(ASDPosObj coord)
{
    ASDPointEarth coord_point;
    QVector <double> coord_t;
    QVector <double> coord_geo;
    coord_t = convPosObjToVectorPos(coord);
    coord_geo = ASDCoordConvertor::convGscToGeo(ASDCoordConvertor::convAgescToGsc(coord_t,coord.time_real));

    coord_point.latitude = coord_geo[0];
    coord_point.longitude = coord_geo[1];
    coord_point.height = coord_geo[2];

    return coord_point;
}


