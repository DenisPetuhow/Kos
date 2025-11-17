#ifndef VIZIBILITY_H
#define VIZIBILITY_H

#include "ASD/asdcoordconvertor.h"
#include "ASD/asdtype.h"
#include "ASD/SunPosition.hpp"
#include "ASD/geotask.h"
class CVizibility
{
public:
    CVizibility();

    /*!
 * \brief Расчитывает положение объекта на земле в картинной плоскости
 * \param X - координаты КА в АГЭСК
 * \param time - вермя
 * \param angle - ось ориентации аппаратуры относительно приборной СК
 * \param latitude - широта объекта
 * \param longitude - долгота объекта
 * \return вектор содержащий два угла : угол рыскания, угол тангажа и дальность.
 */
static QVector<double> calcCoordPicturePlane(QVector<double> X, QDateTime time, ASDAngleMounting angle, double latitude, double longitude);

/*!
 * \brief Расчитывает координаты объекта в инструментальной СК, при известных
 *  дальности и углах тангажа и рыскания
 * \param angle - структура углов
 * \param D - дальность до объекта в км
 * \return вектор координат
 */
static QVector<double> calcCoordObjInIsc(ASDAngleMounting angle, double D);


/*!
 * \brief перевод между связанной СК и АГЭСК
 * \param coord_vehicle - координаты средства в АГЭСК
 * \param coord_target - координаты объекта в связанной СК
 * \param angle_eqip - углы поворота аппаратуры
 * \return  координаты объекта в АГЭСК
 */
static QVector<double> convConScToAGSK(QVector<double> coord_vehicle, QVector<double> coord_target,ASDAngleMounting angle_eqip);

//расчет конуса и пирамиды обзора

/*!
 * \brief Расчитывает зону РЛС в виде двух точек пересеечения крайних граней треугольника. смотрит в бок
 * \param coord_vehicle
 * \param angle_eqip
 * \param deltaV
 * \param deltaH
 * \return вектор состоящий из двух векторов с координатами в АГЭСК крайних точек на Земле принадлежащих зонам
 */
static QVector<QVector<double> > calcPiramidObzor(QVector<double> coord_vehicle,ASDAngleMounting angle_eqip, double deltaV, double deltaH);

/*!
 * \brief расчитывает зону обзора в виде конуса и направленную строго вниз
 * \param coord_vehicle координаты КА
 * \param gamma угол полураствора конуса
 * \param count_points количетво точек составляющих зону
 * \return возращает координаты точек в ГЕО СК
 */
static QVector<ASDPointEarth> calcKonusObzor(QVector<double> coord_vehicle, QDateTime time, double gamma, int count_points);
static double calcElevationSun(QDateTime time, double lat, double longitude);

static QVector <double> calcInterLineWithEarth(QVector<double> coord0,QVector<double> coord1,bool& resould);

static int root2 ( double a, double b, double * x );


};

#endif // VIZIBILITY_H
