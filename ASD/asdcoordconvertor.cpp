/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdcoordconvertor.cpp.\n
 ** Описание: Файл содержит класс конвертирования координат объектов.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 23.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "asdcoordconvertor.h"
#include "QDebug"

ASDCoordConvertor::ASDCoordConvertor()
{

}

ASDCoordConvertor::~ASDCoordConvertor()
{

}

QVector<double> ASDCoordConvertor::convAgescToGsc(QVector<double> coord,
                                                  QDateTime time)
{
    QVector<double> t_coord(6);
    //	double x, y, z, vx, vy, vz;
    double gama;

    gama = compSiderealTime(time);

    double cos_gama = cos(gama);
    double sin_gama = sin(gama);

    t_coord[0] = coord.value(0) * cos_gama + coord.value(1) * sin_gama;
    t_coord[1] = coord.value(1) * cos_gama - coord.value(0) * sin_gama;
    t_coord[2] = coord.value(2);
    t_coord[3] = coord.value(3) * cos_gama + coord.value(4) * sin_gama + (2
                                                                          * M_PI * t_coord[1]) / 86164.;
    t_coord[4] = coord.value(4) * cos_gama - coord.value(3) * sin_gama - (2
                                                                          * M_PI * t_coord[0]) / 86164.;
    t_coord[5] = coord.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convAgescToTsc(QVector<double> coord,
                                                  QDateTime time, double lat, double lon, double h)
{
    return convGscToTsc(convAgescToGsc(coord, time), lat, lon, h);
}

QVector<double> ASDCoordConvertor::convOpscToOscRelative(QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> t_coord(6);
    double v, p, e, r, dv;
    double r1 =pow(pow(coordVehicle[0],2)+pow(coordVehicle[1],2),0.5);
    v = angle(coordVehicle[1]/r1, coordVehicle[0]/r1); //истинная аномалия
    p = K_EARTH * pow(sin(v), 2) / pow(coordVehicle.value(3), 2);//(стр. 49)  из проекций орб. системы координат
    e = coordVehicle.value(4) * pow(p / K_EARTH, 0.5) - cos(v);//(стр. 49)
    r = p / (1 + e * cos(v));
    dv = pow(K_EARTH / p, 0.5) * (1 + e * cos(v)) / r;

    double a11, a12, a21, a22, a33;
    a11 = cos(v);
    a12 = sin(v);


    a21 = -a12;
    a22 = a11;


    a33 = 1;

    t_coord[0] = coordTarget.value(0) * a11 + coordTarget.value(1) * a21;
    t_coord[1] = coordTarget.value(0) * a12 + coordTarget.value(1) * a22;
    t_coord[2] = coordTarget.value(2);
    t_coord[3] = coordTarget.value(3) * a11 + coordTarget.value(4) * a21
            - dv * t_coord[1];
    t_coord[4] = coordTarget.value(4) * a12 - coordTarget.value(3) * a22
            + dv * t_coord[0];
    t_coord[5] = coordTarget.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convOpscToAgescRelative(
        QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> coord_kep = convAgescToKsc(coordVehicle);
    QVector<double> coord_t;
    //поворот на аргумент широты КА вокруг Z
    coord_t = rotateZ(coordTarget,-coord_kep[5]);
    //поворот на наклонение вокруг X
    coord_t = rotateX(coord_t,-coord_kep[0]);
    //поворот на прямое восхождение восходящего узла вокруг Z
    coord_t = rotateZ(coord_t,-coord_kep[1]);
    return coord_t;
}

QVector<double> ASDCoordConvertor::convOpscToIsc(double radius, QVector<double> coordTarget)
{
    QVector <double> t_coord(6,0);
    t_coord[0] = -(coordTarget[0]-radius);
    t_coord[1] =   coordTarget[1];
    t_coord[2] = - coordTarget[2];

    t_coord[3] = - coordTarget[3];
    t_coord[4] =   coordTarget[4];
    t_coord[5] = - coordTarget[5];

    return t_coord;

}

QVector<double> ASDCoordConvertor::convIscToOpsc(double radius, QVector<double> coordTarget)
{
    QVector <double> t_coord(6,0);
    t_coord[0] = -(coordTarget[0]-radius);
    t_coord[1] =   coordTarget[1];
    t_coord[2] = - coordTarget[2];

    t_coord[3] = - coordTarget[3];
    t_coord[4] =   coordTarget[4];
    t_coord[5] = - coordTarget[5];

    return t_coord;
}

QVector<double> ASDCoordConvertor::convIscToConSc(QVector<double> coordTarget, ASDAngleMounting angle)
{
    QVector<double> coord_t;
    //поворот на угол рыскания вокруг Y
    coord_t = rotateY(coordTarget,angle.yaw);
    //поворот на угол тангажа вокруг X
    coord_t = rotateZ(coord_t,angle.pitch);
    //поворот на угол крена вокруг X
    coord_t = rotateX(coord_t,angle.roll);
    return coord_t;

}

QVector<double> ASDCoordConvertor::convConScToIsc(QVector<double> coordTarget, ASDAngleMounting angle)
{
    QVector<double> coord_t;
    //поворот на угол крена вокруг X
    coord_t = rotateX(coordTarget,-angle.roll);
    //поворот на угол тангажа вокруг X
    coord_t = rotateZ(coord_t,-angle.pitch);
    //поворот на угол рыскания вокруг Y
    coord_t = rotateY(coord_t,-angle.yaw);

    return coord_t;

}

QVector<double> ASDCoordConvertor::convAgescToOscRelative(
        QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> coord_kep = convAgescToKsc(coordVehicle);
    QVector<double> coord_t;
    //поворот на прямое восхождение восходящего узла вокруг Z
    coord_t = rotateZ(coordTarget,coord_kep[1]);
    //поворот на наклонение вокруг X
    coord_t = rotateX(coord_t,coord_kep[0]);
    //поворот на аргумент широты перигея вокруг Z
    coord_t = rotateZ(coord_t,coord_kep[2]);
    return coord_t;

}

QVector<double> ASDCoordConvertor::convOscToAgescRelative(QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> coord_kep = convAgescToKsc(coordVehicle);
    QVector<double> coord_t;
    //поворот на аргумент широты перигея вокруг Z
    coord_t = rotateZ(coord_t,-coord_kep[2]);
    //поворот на наклонение вокруг X
    coord_t = rotateX(coord_t,-coord_kep[0]);
    //поворот на прямое восхождение восходящего узла вокруг Z
    coord_t = rotateZ(coordTarget,-coord_kep[1]);

    return coord_t;


}

QVector<double> ASDCoordConvertor::convAgescToOsc(QVector<double> coord)
{
    QVector<double> t_coord(6);
    double X[6];
    double r, l, C, c[3], L[3], V;
    /* матрица направляющих косинусов
     * a11 a21 a31
     * a12 a22 a32
     * a13 a23 a33
     */
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;

    X[0] = coord.value(0);
    X[1] = coord.value(1);
    X[2] = coord.value(2);
    X[3] = coord.value(3);
    X[4] = coord.value(4);
    X[5] = coord.value(5);

    r = pow(X[0] * X[0] + X[1] * X[1] + X[2] * X[2], 0.5);
    V = pow(X[3] * X[3] + X[4] * X[4] + X[5] * X[5], 0.5);

    c[0] = X[1] * X[5] - X[2] * X[4];
    c[1] = X[2] * X[3] - X[0] * X[5];
    c[2] = X[0] * X[4] - X[1] * X[3];

    L[0] = -K_EARTH * X[0] / r + c[2] * X[4] - c[1] * X[5];
    L[1] = -K_EARTH * X[1] / r + c[0] * X[5] - c[2] * X[3];
    L[2] = -K_EARTH * X[2] / r + c[1] * X[3] - c[0] * X[4];

    C = pow(c[0] * c[0] + c[1] * c[1] + c[2] * c[2], 0.5);
    l = pow(L[0] * L[0] + L[1] * L[1] + L[2] * L[2], 0.5);
    QVector <double> coordVehicle_kep;
    if(l<=0.001) //орбита круговая. Вектор Лапласа нулевой
    {
        coordVehicle_kep = ASDCoordConvertor::convAgescToKsc(coord);
        L[0] = cos(coordVehicle_kep[1]);
        L[1] = sin(coordVehicle_kep[1]);
        L[2] = 0;
        l =1;
        c[0] /= C;
        c[1] /= C;
        c[2] /= C;
        C = 1;
    }
    a11 = L[0] / l;
    a12 = (c[1] * L[2] - c[2] * L[1]) / (C * l);
    a13 = c[0] / C;

    a21 = L[1] / l;
    a22 = (c[2] * L[0] - c[0] * L[2]) / (C * l);
    a23 = c[1] / C;

    a31 = L[2] / l;
    a32 = (c[0] * L[1] - c[1] * L[0]) / (C * l);
    a33 = c[2] / C;

    t_coord[0] = a11 * coord.value(0) + a21 * coord.value(1) + a31
            * coord.value(2);
    t_coord[1] = a12 * coord.value(0) + a22 * coord.value(1) + a32
            * coord.value(2);
    t_coord[2] = a13 * coord.value(0) + a23 * coord.value(1) + a33
            * coord.value(2);

    t_coord[3] = a11 * coord.value(3) + a21 * coord.value(4) + a31
            * coord.value(5);
    t_coord[4] = a12 * coord.value(3) + a22 * coord.value(4) + a32
            * coord.value(5);
    t_coord[5] = a13 * coord.value(3) + a23 * coord.value(4) + a33
            * coord.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convOscToOpsc(QVector<double> coord)
{
    QVector<double> t_coord(6);
    double v, p, e, r, dv;

    v = atan2(coord.value(1), coord.value(0));

    double cos_v = cos(v);
    double sin_v = sin(v);

    p = K_EARTH * pow(sin_v, 2) / pow(coord.value(3), 2);
    e = coord.value(4) * pow(p / K_EARTH, 0.5) - cos_v;
    r = p / (1 + e * cos_v);
    dv = pow(K_EARTH / p, 0.5) * (1 + e * cos_v) / r;

    t_coord[0] = coord.value(0) * cos_v + coord.value(1) * sin_v;
    t_coord[1] = -coord.value(0) * sin_v + coord.value(1) * cos_v;
    t_coord[2] = coord.value(2);
    t_coord[3] = coord.value(3) * cos_v + coord.value(4) * sin_v + dv
            * t_coord[1];
    t_coord[4] = coord.value(4) * cos_v - coord.value(3) * sin_v - dv
            * t_coord[0];
    t_coord[5] = coord.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convOscToOpscRelative(
        QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> t_coord(6);
    double v, p, e, r, dv;

    v = atan2(coordVehicle.value(1), coordVehicle.value(0));

    double cos_v = cos(v);
    double sin_v = sin(v);

    p = K_EARTH * pow(sin_v, 2) / pow(coordVehicle.value(3), 2);
    e = coordVehicle.value(4) * pow(p / K_EARTH, 0.5) - cos_v;
    r = p / (1 + e * cos_v);
    dv = pow(K_EARTH / p, 0.5) * (1 + e * cos_v) / r;


    t_coord[0] = coordTarget.value(0) * cos_v + coordTarget.value(1) * sin_v;
    t_coord[1] = -coordTarget.value(0) * sin_v + coordTarget.value(1) * cos_v;
    t_coord[2] = coordTarget.value(2);
    t_coord[3] = coordTarget.value(3) * cos_v + coordTarget.value(4) * sin_v
            + dv * t_coord[1];
    t_coord[4] = coordTarget.value(4) * cos_v - coordTarget.value(3) * sin_v
            - dv * t_coord[0];
    t_coord[5] = coordTarget.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convAgescToOpscRelative(
        QVector<double> coordVehicle, QVector<double> coordTarget)
{
    QVector<double> coord_kep = convAgescToKsc(coordVehicle);
    QVector<double> coord_t;
    //поворот на прямое восхождение восходящего узла вокруг Z
    coord_t = rotateZ(coordTarget,coord_kep[1]);
    //поворот на наклонение вокруг X
    coord_t = rotateX(coord_t,coord_kep[0]);
    //поворот на аргумент широты КА вокруг Z
    coord_t = rotateZ(coord_t,coord_kep[5]);
    return coord_t;

}

QVector<double> ASDCoordConvertor::convAgescToKsc(QVector<double> coord, double GR)
{
    QVector<double> t_coord(6);

    /*
     * Y[0]- наклонение
     * Y[1]- долгота восходящего узла
     * Y[2]- аргумент широты перигея
     * Y[3]- фокальный параметр
     * Y[4]- экцентриситет
     * Y[5]- аргумент широты КА
     */

    double X[6], Y[6];
    double r, l, C, W1, W2, c[5], L[5], V;

    X[0] = coord.value(0);
    X[1] = coord.value(1);
    X[2] = coord.value(2);
    X[3] = coord.value(3);
    X[4] = coord.value(4);
    X[5] = coord.value(5);



    r = pow(X[0] * X[0] + X[1] * X[1] + X[2] * X[2], 0.5);
    V = pow(X[3] * X[3] + X[4] * X[4] + X[5] * X[5], 0.5);

    c[0] = X[1] * X[5] - X[2] * X[4];
    c[1] = X[2] * X[3] - X[0] * X[5];
    c[2] = X[0] * X[4] - X[1] * X[3];

    L[0] = -GR * X[0] / r + c[2] * X[4] - c[1] * X[5];
    L[1] = -GR * X[1] / r + c[0] * X[5] - c[2] * X[3];
    L[2] = -GR * X[2] / r + c[1] * X[3] - c[0] * X[4];

    C = pow(c[0] * c[0] + c[1] * c[1] + c[2] * c[2], 0.5);
    l = pow(L[0] * L[0] + L[1] * L[1] + L[2] * L[2], 0.5);

    Y[4] = l / GR; // экцентриситет
    Y[0] = acos(c[2] / C); // наклонение

    if (Y[0] < 0)
        Y[0] += M_PI;
    if (Y[0] > 0.005) // не экваториальная орбита
    {
        if (c[0] / (C * sin(Y[0])) > 1)
        {
            W1 = M_PI / 2.;
            W2 = acos(-c[1] / (C * sin(Y[0])));
            if (W2 > 0)
            {
                Y[1] = M_PI / 2.;
            }
            else
                Y[1] = 3 * M_PI / 2.;
        }
        else
        {
            W1 = asin(c[0] / (C * sin(Y[0])));
            W2 = acos(-c[1] / (C * sin(Y[0])));

            if (fabs(W1) < 0.00001)
            {
                if (W2 <M_PI/2.)
                {
                    Y[1] = 0;
                }
                else
                    Y[1] = M_PI;
            } else
            {

                if ((W1 >= 0) && (W2 >= 0))
                    Y[1] = W2;
                if ((W1 >= 0) && (W2 <= 0))
                    Y[1] = M_PI - W1;
                if ((W1 <= 0) && (W2 >= 0))
                    Y[1] = 2 * M_PI - W2;
                if ((W1 < 0) && (W2 < 0))
                    Y[1] = M_PI - W2;
            }

        }

    }
    else
    {
        Y[1] = 0; // для экваториальной орбиты прямое восхождение восходящего узла равно 0
        if (Y[4] < 0.005)
        {
            Y[2] = 0;
        }
    }

    Y[3] = C * C / GR; // фокальный параметр (для круговых - радиус)
    if (Y[4] >  0.005) // орбита эллиптическая
    {
        if (Y[0] > 1e-3) // орбита не экваториальная
        {
            if ((c[0] * L[1] - c[1] * L[0]) / (C * l * sin(Y[0])) > 1)
            {
                W2 = 0;
            }
            else
            {
                W2 = acos((c[0] * L[1] - c[1] * L[0]) / (C * l * sin(Y[0])));
            }

            W1 = asin(L[2] / (l * sin(Y[0]))); //аргумент широты перигея
        }
        else
        { //орбита экваториальная эллиптическая
            W1 = asin(L[1] / l);
            W2 = acos(L[0] / l);

        }

        if ((W1 >= 0) && (W2 >= 0))
            Y[2] = W2;
        if ((W1 >= 0) && (W2 <= 0))
            Y[2] = M_PI - W1;
        if ((W1 <= 0) && (W2 >= 0))
            Y[2] = 2 * M_PI - W2;
        if ((W1 < 0) && (W2 < 0))
            Y[2] = M_PI - W2;

    }
    else
    { // орбита круговая
        Y[2] = 0;
    }
    double k;
    if (Y[0] > 1e-4)
    {
        W1 = asin(X[2] / (r * sin(Y[0]))); //аргумент широты КА
        k = 1 / r * (X[0] / cos(Y[1]) + X[2] * tan(Y[1]) / tan(Y[0]));
        if(k>1) k=1;
        if(k<-1) k=-1;
        W2 = acos(k);
    }
    else
    {
        W1 =  asin(X[1] / r);
        W2 =  acos(X[0] / r);
    }
    if ((W1 >= 0) && (W2 >= 0))
        Y[5] = W2;
    if ((W1 >= 0) && (W2 <= 0))
        Y[5] = M_PI - W1;
    if ((W1 <= 0) && (W2 >= 0))
        Y[5] = 2 * M_PI - W2;
    if ((W1 < 0) && (W2 < 0))
        Y[5] = M_PI - W2;

    for (int i = 0; i < 6; i++)
    {
        t_coord[i] = Y[i]; //TODO приведение типов!!

    }

    return t_coord;
}

QVector<double> ASDCoordConvertor::convGscToAgesc(QVector<double> coord,
                                                  QDateTime time)
{
    QVector<double> t_coord(6);
    double gama, sin_gama, cos_gama;

    gama = compSiderealTime(time);
    sin_gama = sin(gama);
    cos_gama = cos(gama);

    t_coord[0] = coord.value(0) * cos_gama - coord.value(1) * sin_gama;
    t_coord[1] = coord.value(0) * sin_gama + coord.value(1) * cos_gama;
    t_coord[2] = coord.value(2);

    t_coord[3] = coord.value(3) * cos_gama - coord.value(4) * sin_gama - (2
                                                                          * M_PI * t_coord[1]) / 86164.;
    t_coord[4] = coord.value(3) * sin_gama + coord.value(4) * cos_gama + (2
                                                                          * M_PI * t_coord[0]) / 86164.;
    t_coord[5] = coord.value(5);

    return t_coord;
}

QVector<double> ASDCoordConvertor::convGscToTsc(QVector<double> coord,
                                                double lat, double lon, double h)
{
    QVector<double> t_coord(6);
    double delta, rn, B, sin_B, cos_B;

    if (lat != 0)
    {
        B = atan(pow((1 - 1. / 298.3), -2) * tan(lat)); // связь между геоцентрической и геодезической широтой
        rn = R_EARTH * sin(lat) / sin(B);
        delta = R_EARTH * cos(lat) - rn * cos(B);
    }
    else
    {
        rn = R_EARTH;
        delta = 0.;
    }

    sin_B = sin(B);
    cos_B = cos(B);

    double sin_lon = 0, cos_lon = 0;
    sin_lon = sin(lon);
    cos_lon = cos(lon);

    t_coord[0] = coord.value(0) * sin_lon - coord.value(1) * cos_lon;

    t_coord[1] = coord.value(0) * cos_lon * cos_B + coord.value(1) * sin_lon
            * cos_B + coord.value(2) * sin_B - rn - h - delta * cos_B;

    t_coord[2] = -coord.value(0) * cos_lon * sin_B - coord.value(1)
            * sin_lon * sin_B + coord.value(2) * cos_B + delta * sin_B;

    t_coord[3] = coord.value(3) * sin_lon - coord.value(4) * cos_lon;

    t_coord[4] = coord.value(3) * cos_lon * cos_B + coord.value(4) * sin_lon
            * cos_B + coord.value(5) * sin_B;

    t_coord[5] = -coord.value(3) * cos_lon * sin_B - coord.value(4)
            * sin_lon * sin_B + coord.value(5) * cos_B;

    return t_coord;
}

QVector<double> ASDCoordConvertor::convGscToOsc(QVector<double> coord,
                                                QDateTime time)
{
    return convAgescToOsc(convGscToAgesc(coord, time));
}

QVector<double> ASDCoordConvertor::convGscToKsc(QVector<double> coord,
                                                QDateTime time)
{
    return convAgescToKsc(convGscToAgesc(coord, time));
}

QVector<double> ASDCoordConvertor::convTscToAgesc(QVector<double> coord,
                                                  QDateTime time, double lat, double lon, double h)
{
    return convGscToAgesc(convTscToGsc(coord, lat, lon, h), time);
}

QVector<double> ASDCoordConvertor::convTscToGsc(QVector<double> coord,
                                                double lat, double lon, double h)
{
    QVector<double> t_coord(6);
    double delta, rn, B;

    if (lat != 0)
    {
        B = atan(pow((1 - 1 / 298.3), -2) * tan(lat)); // связь между геоцентрической и геодезтческой широтой
        rn = R_EARTH * sin(lat) / sin(B);
        delta = R_EARTH * cos(lat) - rn * cos(B);
    }
    else
    {
        rn = R_EARTH;
        delta = 0.;
    }

    double sin_B = sin(B);
    double cos_B = cos(B);
    double sin_lon = 0, cos_lon = 0;
    sin_lon = sin(lon);
    cos_lon = cos(lon);

    t_coord[0] = coord.value(0) * sin_lon + coord.value(1) * cos_lon * cos_B
            - coord.value(2) * sin_B * cos_lon + (rn * cos_B + h * cos_B
                                                  + delta) * cos_lon;

    t_coord[1] = -coord.value(0) * cos_lon + coord.value(1) * sin_lon
            * cos_B - coord.value(2) * sin_B * sin_lon + (rn * cos_B + h
                                                          * cos_B + delta) * sin_lon;

    t_coord[2] = coord.value(1) * sin_B + coord.value(2) * cos_B + (rn + h)
            * sin_B;

    t_coord[3] = coord.value(3) * sin_lon + coord.value(4) * cos_lon * cos_B
            - coord.value(5) * sin_B * cos_lon;

    t_coord[4] = -coord.value(3) * cos_lon + coord.value(4) * sin_lon
            * cos_B - coord.value(5) * sin_B * sin_lon;

    t_coord[5] = coord.value(4) * sin_B + coord.value(5) * cos_B;

    return t_coord;
}

QVector<double> ASDCoordConvertor::convTscToOsc(QVector<double> coord,
                                                QDateTime time, double lat, double lon, double h)
{
    return convAgescToOsc(convTscToAgesc(coord, time, lat, lon, h));
}

QVector<double> ASDCoordConvertor::convTscToKsc(QVector<double> coord,
                                                QDateTime time, double lat, double lon, double h)
{
    return convAgescToKsc(convTscToAgesc(coord, time, lat, lon, h));
}

QVector<double> ASDCoordConvertor::convKscToAgesc(QVector<double> coord, double GR)
{
    /*
     * coord.value(0)- наклонение
     * coord.value(1)- долгота восходящего узла
     * coord.value(2)- аргумент широты перигея
     * coord.value(3)- фокальный параметр
     * coord.value(4)- экцентриситет
     * coord.value(5)- аргумент широты КА
     */
    QVector<double> t_coord(6);
    double Vr, Vt, r, u;

    Vr = pow(GR / coord.value(3), 0.5) * coord.value(4) * sin(coord.value(
                                                                       5) - coord.value(2));
    Vt = pow(GR / coord.value(3), 0.5) * (1 + coord.value(4) * cos(
                                                   coord.value(5) - coord.value(2)));
    u = coord.value(5);

    double sin_u = sin(u);
    double cos_u = cos(u);

    r = coord.value(3) / (1 + coord.value(4) * cos(coord.value(5)
                                                   - coord.value(2)));

    double sin1 = sin(coord.value(1));
    double cos1 = cos(coord.value(1));
    double cos0 = cos(coord.value(0));
    double sin0 = sin(coord.value(0));

    t_coord[0] = r * (cos1 * cos_u - sin1 * sin_u
                      * cos0);
    t_coord[1] = r * (sin1 * cos_u + sin_u * cos1 * cos0);
    t_coord[2] = r * sin_u * sin0;

    t_coord[3] = Vr * (cos1 * cos_u - sin1
                       * sin_u * cos0) - Vt * (cos1
                                               * sin_u + sin1 * cos_u * cos0);

    t_coord[4] = Vr * (sin1 * cos_u + cos1
                       * sin_u * cos0) - Vt * (sin1
                                               * sin_u - cos1 * cos_u * cos0);
    t_coord[5] = Vr * sin_u * sin0 + Vt * cos_u * sin0;

    return t_coord;
}

QVector<double> ASDCoordConvertor::convKscToGsc(QVector<double> coord,
                                                QDateTime time)
{
    return convAgescToGsc(convKscToAgesc(coord), time);
}

QVector<double> ASDCoordConvertor::convKscToTsc(QVector<double> coord,
                                                QDateTime timeMoscow, double lat, double lon, double h)
{
    return convAgescToTsc(convKscToAgesc(coord), timeMoscow, lat, lon, h);
}

QVector<double> ASDCoordConvertor::convKscToOsc(QVector<double> coord)
{
    return convAgescToOsc(convKscToAgesc(coord));
}

QVector<double> ASDCoordConvertor::convSscToGsc(QVector<double> coord,
                                                double lat, double lon, double A)
{
    QVector<double> t_coord(6);
    double X[6];
    double Xogk, Yogk, Zogk; //координаты в относительной геоцентрической СК (считая начала координат совпадающими)
    double Xgk, Ygk, Zgk;//координаты в относительной геоцентрической СК (с учетом несовпадения начала координат)

    /* матрица направляющих косинусов
     * a11 a21 a31
     * a12 a22 a32
     * a13 a23 a33
     */
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    double b11, b12, b13, b21, b22, b23, b31, b32, b33;
    double c11, c12, c13, c21, c22, c23, c31, c32, c33;
    double Xrc, Zrc;

    X[0] = coord.value(3);//Vxck
    X[1] = coord.value(4);//Vyck
    X[2] = coord.value(5);//Vzck
    X[3] = coord.value(0);//Xck
    X[4] = coord.value(1);//Yck
    X[5] = coord.value(2);//Zck

    //A - азимут прицеливания
    //lon - долгота
    //lat - геоцентрическая широта
    double cos_lon = cos(lon);
    double sin_lon = sin(lon);
    double cos_lat = cos(lat);
    double sin_lat = sin(lat);
    double cos_A = cos(A);
    double sin_A = sin(A);


    //матрица направляющих косинусов Агр.с. - пересчет проекций скорости из ССК в ГСК
    a11 = -cos_A * cos_lon * sin_lat - sin_A * sin_lon;
    a12 = -sin_lon * sin_lat * cos_A + cos_lon * sin_A;
    a13 = cos_A * cos_lat;

    a21 = cos_lon * cos_lat;
    a22 = sin_lon * cos_lat;
    a23 = sin_lat;

    a31 = cos_lon * sin_lat * sin_A - sin_lon * cos_A;
    a32 = sin_A * sin_lon * sin_lat + cos_A * cos_lon;
    a33 = -sin_A * cos_lat;

    //рассчитаем Vxk, Vyk, Vzk
    t_coord[3] = a11 * X[0] + a21 * X[1] + a31 * X[2];
    t_coord[4] = a12 * X[0] + a22 * X[1] + a32 * X[2];
    t_coord[5] = a13 * X[0] + a23 * X[1] + a33 * X[2];

    // матрица направляющих косинусов Агс - пересчет координат из ССК в ОГСК (считая начала координат совпадающими)
    b11 = -cos_A * sin_lat;
    b12 = sin_A;
    b13 = cos_A * cos_lat;

    b21 = cos_lat;
    b22 = 0;
    b23 = sin_lat;

    b31 = sin_lat * sin_A;
    b32 = cos_A;
    b33 = -cos_lat * sin_A;

    //рассчитываем Х0гк, Y0гк, Z0гк
    Xogk = b11 * X[3] + b21 * X[4] + b31 * X[5];
    Yogk = b12 * X[3] + b22 * X[4] + b32 * X[5];
    Zogk = b13 * X[3] + b23 * X[4] + b33 * X[5];

    //учитываем несовпадение начала координат и рассчитываем Xгк, Yгк, Zгк
    Xrc = R_EARTH * cos_lat;
    Zrc = R_EARTH * sin_lat;

    Xgk = Xogk + Xrc;
    Ygk = Yogk;
    Zgk = Zogk + Zrc;

    //матрица направляющих косинусов Агр.г - переход от относительной геоцентрической СК к гринвичской
    c11 = cos_lon;
    c12 = sin_lon;
    c13 = 0;

    c21 = -sin_lon;
    c22 = cos_lon;
    c23 = 0;

    c31 = 0;
    c32 = 0;
    c33 = 1;

    //рассчитываем Хк, Yк, Zк - искомые координаты
    t_coord[0] = c11 * Xgk + c21 * Ygk + c31 * Zgk;
    t_coord[1] = c12 * Xgk + c22 * Ygk + c32 * Zgk;
    t_coord[2] = c13 * Xgk + c23 * Ygk + c33 * Zgk;

    return t_coord;
}

QVector<double> ASDCoordConvertor::convGscToSsc(QVector<double> coord,
                                                double lat, double lon, double A)
{
    QVector<double> t_coord(6);
    double X[6];
    double Xogk, Yogk, Zogk; //координаты в относительной геоцентрической СК (считая начала координат совпадающими)
    double Xgk, Ygk, Zgk;//координаты в относительной геоцентрической СК (с учетом несовпадения начала координат)

    /* матрица направляющих косинусов
     * a11 a21 a31
     * a12 a22 a32
     * a13 a23 a33
     */
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    double b11, b12, b13, b21, b22, b23, b31, b32, b33;
    double c11, c12, c13, c21, c22, c23, c31, c32, c33;
    double Xrc, Zrc;

    X[0] = coord.value(0);//Xk
    X[1] = coord.value(1);//Yk
    X[2] = coord.value(2);//Zk
    X[3] = coord.value(3);//Vxk
    X[4] = coord.value(4);//Vyk
    X[5] = coord.value(5);//Vzk

    // A - азимут прицеливания
    // lon - долгота
    // lat - геоцентрическая широта
    // A=A*DEG_TO_RAD;
    // lon=lon*DEG_TO_RAD;
    // lat=lat*DEG_TO_RAD;

    double cos_lon = cos(lon);
    double sin_lon = sin(lon);
    double cos_lat = cos(lat);
    double sin_lat = sin(lat);
    double cos_A = cos(A);
    double sin_A = sin(A);


    //матрица направляющих косинусов Агр.с. (транспонированная) - пересчет проекций скорости из ГСК в ССК
    a11 = -cos_A * cos_lon * sin_lat - sin_A * sin_lon;
    a21 = -sin_lon * sin_lat * cos_A + cos_lon * sin_A;
    a31 = cos_A * cos_lat;

    a12 = cos_lon * cos_lat;
    a22 = sin_lon * cos_lat;
    a32 = sin_lat;

    a13 = cos_lon * sin_lat * sin_A - sin_lon * cos_A;
    a23 = sin_A * sin_lon * sin_lat + cos_A * cos_lon;
    a33 = -sin_A * cos_lat;

    //рассчитаем Vxk, Vyk, Vzk
    t_coord[3] = a11 * X[3] + a21 * X[4] + a31 * X[5];
    t_coord[4] = a12 * X[3] + a22 * X[4] + a32 * X[5];
    t_coord[5] = a13 * X[3] + a23 * X[4] + a33 * X[5];

    //матрица направляющих косинусов Агр.г (транспонированная) - переход от гринвичской СК к геоцентрической
    c11 = cos_lon;
    c21 = sin_lon;
    c31 = 0;

    c12 = -sin_lon;
    c22 = cos_lon;
    c32 = 0;

    c13 = 0;
    c23 = 0;
    c33 = 1;

    //рассчитываем Хгк, Yгк, Zгк
    Xgk = c11 * X[0] + c21 * X[1] + c31 * X[2];
    Ygk = c12 * X[0] + c22 * X[1] + c32 * X[2];
    Zgk = c13 * X[0] + c23 * X[1] + c33 * X[2];

    //учитываем несовпадение начала координат и рассчитываем Xoгк, Yoгк, Zoгк
    Xrc = R_EARTH * cos_lat;
    Zrc = R_EARTH * sin_lat;

    Xogk = Xgk - Xrc;
    Yogk = Ygk;
    Zogk = Zgk - Zrc;

    // матрица направляющих косинусов Агс (транспонированная) - пересчет координат из ОГСК в ССК
    b11 = -cos_A * sin_lat;
    b21 = sin_A;
    b31 = cos_A * cos_lat;

    b12 = cos_lat;
    b22 = 0;
    b32 = sin_lat;

    b13 = sin_lat * sin_A;
    b23 = cos_A;
    b33 = -cos_lat * sin_A;

    //рассчитываем Хcк, Ycк, Zcк
    t_coord[0] = b11 * Xogk + b21 * Yogk + b31 * Zogk;
    t_coord[1] = b12 * Xogk + b22 * Yogk + b32 * Zogk;
    t_coord[2] = b13 * Xogk + b23 * Yogk + b33 * Zogk;

    return t_coord;
}

double ASDCoordConvertor::angle(double t_sin, double t_cos)
{
    double W1, W2;
    W1 = asin(t_sin);
    W2 = acos(t_cos);

    if ((t_sin >= 0) && (t_cos >= 0))
        return W1;
    if ((t_sin >= 0) && (t_cos <= 0))
        return M_PI - W1;
    if ((t_sin < 0) && (t_cos < 0))
        return 2*M_PI - W2;
    if ((t_sin <= 0) && (t_cos >= 0))
        return 2*M_PI - W2;

}

template <class _Type> inline _Type _modulus(_Type arg1, _Type arg2)
{
    _Type result;
    result=arg1 - trunc(arg1/arg2)*arg2;
    if (result<0)
        result=+arg2;
    return result;
}



double ASDCoordConvertor::compSiderealTime(QDateTime time)
{
    double dEarthAngle;
    //    qDebug()<<"***********************************";
    //    qDebug()<<"Время на входе "<<time.toString();
    /// Алгоритм Меёссе
    double yr = time.date().year() - 1;
    double a=trunc(yr/100); // Промежуточная величина
    double b = 2-a+trunc(a/4);// Промежуточная величина
    float julianDayNumber = trunc(365.25*yr)+trunc(30.6001*14)+1720994.5+b; //!< Расчет номера дня по Юлианскому календарю
    //    qDebug()<<"Номер дня по юлианскому календарю "<<julianDayNumber;
    int daysOfYear=0;
    int daysOfMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    for (int i=0; i<(time.date().month()-1); i++)
    {
        daysOfYear+=daysOfMonth[i];
    }
    if ( (( (time.date().year())%4)==0) &&
         ( (((time.date().year())%100)!=0) || (((time.date().year())%100)==0) ) &&
         (time.date().month()>2)    )
        daysOfYear++;
    daysOfYear += time.date().day();
    double julianDate = julianDayNumber+daysOfYear; //!< Полная дата По Юлианскому календарю
    //    qDebug()<<" Полная дата по Юлианскому календарю: "<<julianDate;
    double dSec = 3600*time.time().hour() + 60*time.time().minute() + time.time().second() + 0.001*time.time().msec(); //!< Вычисление количества секунда в текущей дате
    //    qDebug()<<" Время в секунды : "<<dSec;

    julianDate +=(dSec/86400.) ; //!< Полное время по Юлианскому календарю (дата + время)
    //    qDebug()<<" Полное время по Юлианскому календарю (дата + время): "<<julianDate;

    //    double dTu = (julianDate - 2451545.0) / 36525 ;
    //    double GMST = (24110.54841 + 8640184.812866 * dTu + 0.093104 * dTu * dTu - 6.2e-6 * dTu * dTu * dTu) / 13750.9870831398;

    double UT = julianDate+0.5;
    UT = UT - floor(UT);
    double TU=((julianDate - UT) - 2451545.0) / 36525. ;
    double GMST = (24110.54841 + 8640184.812866 * TU + 0.093104 * TU * TU - 6.2e-6 * TU * TU * TU) /* / 13750.9870831398 */;
    while(GMST<0) GMST+=86400.;
    GMST = _modulus ((GMST+86400.*1.00273790934*UT),((double)86400.));
    //    qDebug()<< "GMST: "<<GMST;
    dEarthAngle = GMST*(2*M_PI/86400.);

    return dEarthAngle;
}

double ASDCoordConvertor::UD(const QDateTime time)
{
    double yr = time.date().year() - 1;
    double a=trunc(yr/100); // Промежуточная величина
    double b = 2-a+trunc(a/4);// Промежуточная величина
    float julianDayNumber = trunc(365.25*yr)+trunc(30.6001*14)+1720994.5+b; //!< Расчет номера дня по Юлианскому календарю
    //    qDebug()<<"Номер дня по юлианскому календарю "<<julianDayNumber;
    int daysOfYear=0;
    int daysOfMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    for (int i=0; i<(time.date().month()-1); i++)
    {
        daysOfYear+=daysOfMonth[i];
    }
    if ( (( (time.date().year())%4)==0) &&
         ( (((time.date().year())%100)!=0) || (((time.date().year())%100)==0) ) &&
         (time.date().month()>2)    )
        daysOfYear++;
    daysOfYear += time.date().day();
    double julianDate = julianDayNumber+daysOfYear; //!< Полная дата По Юлианскому календарю
    //    qDebug()<<" Полная дата по Юлианскому календарю: "<<julianDate;
    double dSec = 3600*time.time().hour() + 60*time.time().minute() + time.time().second() + 0.001*time.time().msec(); //!< Вычисление количества секунда в текущей дате
    //    qDebug()<<" Время в секунды : "<<dSec;

    julianDate +=(dSec/86400.) ; //!< Полное время по Юлианскому календарю (дата + время)
    return julianDate;
}

double ASDCoordConvertor::MUD(const QDateTime time)
{
    double ud = UD(time);
    return ud - 2400000.5;
}


QDateTime ASDCoordConvertor::calcLocalTime(const QDateTime time,
                                           const double lon)
{
    return time.addSecs((int) ((24. * 3600.) / (2 * M_PI) * lon));
}

QVector<double> ASDCoordConvertor::convParamActSiteToAgesc(ASDCurPos pos,
                                                           QDateTime time_start, double lat, double lon, double A)
{
    /*
     * coord.value(0)-наклонение
     * coord.value(1)-прямое восхождение восходящего узла
     * coord.value(2)-аргумент широты перигея
     * coord.value(3)- фокальный параметр
     * coord.value(4)- экцентриситет
     * coord.value(5)- аргумент широты КА
     */
    QVector<double> coord(6);
    QVector<double> t_coord(6);
    double veloc = pos.velocity / 1000.;
    double r = pos.height / 1000. + R_EARTH;
    coord[0] = acos(cos(lat) * sin(A));

    double cos_lon = cos(lon);
    double sin_lon = sin(lon);
    double cos_lat = cos(lat);
    double sin_lat = sin(lat);
    double cos_A = cos(A);
    double sin_A = sin(A);

    double Uct;
    if (A != 0)
    {
        if (coord[0] != 0)
        {
            Uct
                    = angle(sin_lat / sin(coord[0]), 1. / (tan(A) * tan(
                                                               coord[0]))); //аргумент широты точки старта
        }
        else
        {
            Uct = 0;
        }
    }
    else
        Uct = lat;
    double u = Uct + pos.geoAngle;
    double Vr = veloc * sin(pos.angleInclinVel);
    double Vt = veloc * cos(pos.angleInclinVel);

    double cos_u = cos(u);
    double sin_u = sin(u);

    double delta_lon = angle(sin_u * sin_A, cos_A / sin(coord[0]));

    coord[1] = lon - delta_lon + compSiderealTime(time_start.addSecs(pos.time));

    double sin1 = sin(coord.value(1));
    double cos1 = cos(coord.value(1));
    double cos0 = cos(coord.value(0));
    double sin0 = sin(coord.value(0));

    t_coord[0] = r * (cos1 * cos_u - sin1 * sin_u
                      * cos0);
    t_coord[1] = r * (sin1 * cos_u + sin_u * cos1 * cos0);
    t_coord[2] = r * sin_u * sin0;

    t_coord[3] = Vr * (cos1 * cos_u - sin1
                       * sin_u * cos0) - Vt * (cos1
                                               * sin_u + sin1 * cos_u * cos0);

    t_coord[4] = Vr * (sin1 * cos_u + cos1
                       * sin_u * cos0) - Vt * (sin1
                                               * sin_u - cos1 * cos_u * cos0);
    t_coord[5] = Vr * sin_u * sin0 + Vt * cos_u * sin0;

    return t_coord;
}

QVector<double> ASDCoordConvertor::convGeoToGsc(double lat, double lon, double h, double r_planet)
{
    QVector<double> coord(6,0);
    double k;
    double r = r_planet+h;
    coord[2] = sin(lat) * r;
    k = pow(r * r - coord[2] * coord[2], 0.5);
    coord[0] = cos(lon) * k;
    coord[1] = sin(lon) * k;
    return coord;
}

QVector<double> ASDCoordConvertor::convGscToGeo(QVector<double> coord)
{
    QVector <double> coord1(3);
    double r = pow(coord[0]*coord[0]+coord[1]*coord[1]+coord[2]*coord[2],0.5);
    double r1 = pow(coord[0]*coord[0]+coord[1]*coord[1],0.5);
    coord1[0] = asin(coord[2]/r); //широта [рад]
    coord1[1] = angle(coord[1]/r1,coord[0]/r1); //долгота [рад]
    coord1[2] = r - R_EARTH; //высота [км]

    return coord1;
}

double ASDCoordConvertor::calcAngulDist(double lat1, double long1, double lat2, double long2)
{
    return acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(long2-long1));
}

QVector<double> ASDCoordConvertor::convRscToSsc(ASDAngleMounting angle, QVector<double> coord)
{
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = cos(angle.pitch)*cos(angle.yaw);
    a12 = cos(angle.pitch)*sin(angle.roll)*sin(angle.yaw) - sin(angle.pitch)*cos(angle.roll);
    a13 = cos(angle.roll)*cos(angle.pitch)*sin(angle.yaw) + sin(angle.pitch)*sin(angle.roll);
    a21 = sin(angle.pitch)*cos(angle.yaw);
    a22 = sin(angle.pitch)*sin(angle.roll)*sin(angle.yaw) + cos(angle.pitch)*cos(angle.roll);
    a23 = sin(angle.pitch)*cos(angle.roll)*sin(angle.yaw) - cos(angle.pitch)*sin(angle.roll);
    a31 = - sin(angle.yaw);
    a32 = cos(angle.yaw)*sin(angle.roll);
    a33 = cos(angle.yaw)*cos(angle.roll);

    QVector <double> coord1(6);
    coord1[0] = a11*coord[0]+a12*coord[1]+a13*coord[2]; //x
    coord1[1] = a21*coord[0]+a22*coord[1]+a23*coord[2]; //y
    coord1[2] = a31*coord[0]+a32*coord[1]+a33*coord[2]; //z

    coord1[3] = a11*coord[3]+a12*coord[4]+a13*coord[5]; //Vx
    coord1[4] = a21*coord[3]+a22*coord[4]+a23*coord[5]; //Vy
    coord1[5] = a31*coord[3]+a32*coord[4]+a33*coord[5]; //Vz

    return coord1;
}

QVector<double> ASDCoordConvertor::convVscToSsc(double angle_vel, double angle_side, QVector<double> coord)
{
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = cos(angle_vel) * cos(angle_side);
    a12 = - sin(angle_vel);
    a13 = cos(angle_vel) * sin(angle_side);
    a21 = sin(angle_vel) * cos(angle_side);
    a22 = cos(angle_vel);
    a23 = sin(angle_vel) * sin(angle_side);
    a31 = - sin(angle_side);
    a32 = 0;
    a33 = cos(angle_side);

    QVector <double> coord1(6);
    coord1[0] = a11*coord[0]+a12*coord[1]+a13*coord[2]; //x
    coord1[1] = a21*coord[0]+a22*coord[1]+a23*coord[2]; //y
    coord1[2] = a31*coord[0]+a32*coord[1]+a33*coord[2]; //z

    coord1[3] = a11*coord[3]+a12*coord[4]+a13*coord[5]; //Vx
    coord1[4] = a21*coord[3]+a22*coord[4]+a23*coord[5]; //Vy
    coord1[5] = a31*coord[3]+a32*coord[4]+a33*coord[5]; //Vz

    return coord1;
}

double ASDCoordConvertor::convLatGeogToGeod(double latGeog)
{
    return latGeog + ALFA_EARTH*sin(2*latGeog);
}

double ASDCoordConvertor::convGeodToGeog(double latGeod)
{
    return 0;
}

double ASDCoordConvertor::calcAzimuth(double latitude_1, double longitude_1, double latitude_2, double longitude_2, double delta_time)
{

    double azim;
    QVector <double> X1_gsk, X2_gsk;
    QVector <double> X1_agesk, X2_agesk;
    //    if(longitude<m_longitude)
    //    {
    //        delta_time *=-1;
    //    }
    X1_gsk = ASDCoordConvertor::convGeoToGsc(latitude_1,longitude_1,0);
    X2_gsk = ASDCoordConvertor::convGeoToGsc(latitude_2,longitude_2+OMEGA_EARTH*delta_time,0);
    for(int i =0; i<3; i++) // размер ветора увеличи до 6
    {
        X1_gsk.append(0);
        X2_gsk.append(0);
    }
    X1_agesk = X1_gsk;
    X2_agesk = X2_gsk;
    double sin_A, cos_A, F;
    F = acos((X1_agesk[0]*X2_agesk[0]+X1_agesk[1]*X2_agesk[1]+X1_agesk[2]*X2_agesk[2])/pow(R_EARTH,2));
    sin_A = cos(latitude_2)*sin(longitude_2+OMEGA_EARTH*delta_time-longitude_1)/sin(F);
    cos_A = (cos(latitude_1)*sin(latitude_2) - sin(latitude_1)*cos(latitude_2)*cos(longitude_2+OMEGA_EARTH*delta_time-longitude_1))/sin(F);
    azim = ASDCoordConvertor::angle(sin_A,cos_A);


    return azim;
}

QVector<double> ASDCoordConvertor::rotateX(QVector<double> coord, const double &beta)
{
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = 1;
    a12 = 0;
    a13 = 0;
    a21 = 0;
    a22 = cos(beta);
    a23 = -sin(beta);
    a31 = 0;
    a32 = sin(beta);
    a33 = cos(beta);

    QVector <double> coord1(6);
    coord1[0] = a11*coord[0]+a21*coord[1]+a31*coord[2]; //x
    coord1[1] = a12*coord[0]+a22*coord[1]+a32*coord[2]; //y
    coord1[2] = a13*coord[0]+a23*coord[1]+a33*coord[2]; //z

    coord1[3] = a11*coord[3]+a21*coord[4]+a31*coord[5]; //Vx
    coord1[4] = a12*coord[3]+a22*coord[4]+a32*coord[5]; //Vy
    coord1[5] = a13*coord[3]+a23*coord[4]+a33*coord[5]; //Vz

    return coord1;
}

QVector<double> ASDCoordConvertor::rotateY(QVector<double> coord, const double &beta)
{
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = cos(beta);
    a12 = 0;
    a13 = sin(beta);
    a21 = 0;
    a22 = 1;
    a23 = 0;
    a31 = -sin(beta);
    a32 = 0;
    a33 = cos(beta);

    QVector <double> coord1(6);
    coord1[0] = a11*coord[0]+a21*coord[1]+a31*coord[2]; //x
    coord1[1] = a12*coord[0]+a22*coord[1]+a32*coord[2]; //y
    coord1[2] = a13*coord[0]+a23*coord[1]+a33*coord[2]; //z

    coord1[3] = a11*coord[3]+a21*coord[4]+a31*coord[5]; //Vx
    coord1[4] = a12*coord[3]+a22*coord[4]+a32*coord[5]; //Vy
    coord1[5] = a13*coord[3]+a23*coord[4]+a33*coord[5]; //Vz

    return coord1;
}

QVector<double> ASDCoordConvertor::rotateZ(QVector<double> coord, const double &beta)
{
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = cos(beta);
    a12 = -sin(beta);
    a13 = 0;
    a21 = sin(beta);
    a22 = cos(beta);
    a23 = 0;
    a31 = 0;
    a32 = 0;
    a33 = 1;

    QVector <double> coord1(6);
    coord1[0] = a11*coord[0]+a21*coord[1]+a31*coord[2]; //x
    coord1[1] = a12*coord[0]+a22*coord[1]+a32*coord[2]; //y
    coord1[2] = a13*coord[0]+a23*coord[1]+a33*coord[2]; //z

    coord1[3] = a11*coord[3]+a21*coord[4]+a31*coord[5]; //Vx
    coord1[4] = a12*coord[3]+a22*coord[4]+a32*coord[5]; //Vy
    coord1[5] = a13*coord[3]+a23*coord[4]+a33*coord[5]; //Vz

    return coord1;
}

QVector<double> ASDCoordConvertor::calcAzimuth_Elevetion(QVector<double> coord_AGSK, double latitude, double longitude, QDateTime time)
{
    QVector<double> coord_Gsc = convAgescToGsc(coord_AGSK,time);
    QVector<double> coord_Ssc =  convGscToSsc(coord_Gsc,latitude,longitude,0);
    double r = pow(pow(coord_Ssc[0],2)+pow(coord_Ssc[1],2)+pow(coord_Ssc[2],2),0.5);
    double r_1 = pow(pow(coord_Ssc[0],2)+pow(coord_Ssc[2],2),0.5);
    double sin_elev = coord_Ssc[1]/r;
    double elev = asin(sin_elev);
    double sin_azimuth = coord_Ssc[2]/r_1;
    double cos_azimuth = coord_Ssc[0]/r_1;
    double azimuth = angle(sin_azimuth, cos_azimuth);
    QVector <double> coord_t(3);
    coord_t[0] = azimuth;
    coord_t[1] = elev;
    coord_t[2] = r;
    return coord_t;
}

QVector<double> ASDCoordConvertor::convSscToRlsc(QVector<double> coord_Ssc)
{

    double r = pow(pow(coord_Ssc[0],2)+pow(coord_Ssc[1],2)+pow(coord_Ssc[2],2),0.5);
    double r_1 = pow(pow(coord_Ssc[0],2)+pow(coord_Ssc[2],2),0.5);
    double sin_elev = coord_Ssc[1]/r;
    double elev = asin(sin_elev);
    double sin_azimuth = coord_Ssc[2]/r_1;
    double cos_azimuth = coord_Ssc[0]/r_1;
    double azimuth = angle(sin_azimuth, cos_azimuth);
    QVector<double> coord(6,0);
    coord[0] = r;
    coord[1] = azimuth;
    coord[2] = elev;
    return coord;
}

QVector<double> ASDCoordConvertor::convIzmToGsc(QVector<double> coord, double latitude, double longitude, double height, double r, double azimuth, double elevetion)
{
    QVector<double> coord1(coord);
    QVector<double> coord2 = rotateY(coord1,-elevetion);
    QVector<double> coord3 = rotateZ(coord2,-azimuth);

    QVector<double> coord4(6);
    coord4[3] = coord3[0];
    coord4[4] = coord3[1];
    coord4[5] = coord3[0];
    return ASDCoordConvertor::convSscToGsc(coord4,latitude,longitude,0);
}

//QVector<double> ASDCoordConvertor::convAgescToEsp2(QVector<double> coord)
//{

//}

//QVector<double> ASDCoordConvertor::convEsp2ToAgesc(QVector<double> coord_Ssc)
//{

//}



