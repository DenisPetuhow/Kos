#ifndef ASDCONVTYPE_H
#define ASDCONVTYPE_H

#include "asdtype.h"
#include "asdcoordconvertor.h"


/*!
 * \brief Класс, содержащий средства для конвертирования структур
 */


class ASDConvType
{
public:
    ASDConvType();

    /*!
     * \brief Перевод из векторной записи координат в структуру
     * \param coord - вектор положения (x,y,z,Vx,Vy,Vz)
     * \param time_real - дата и время
     * \param time - относительное время
     * \return структура координат объекта на заданный момент времени
     */
    static ASDPosObj convVectorPosToPosObj(QVector <double> coord, QDateTime time_real = QDateTime::currentDateTime(), double time = 0);

    /*!
     * \brief Перевод из структуры в векторную запись
     * \param coord - структура координат объекта
     * \return вектор положения (x,y,z,Vx,Vy,Vz)
     */
    static QVector <double> convPosObjToVectorPos (ASDPosObj coord);

    /*!
     * \brief Перевод из структуры ASDPosObj в структуру ASDCoordObj
     */
    static QVector <ASDCoordObj> convPosToCoordObj(QVector<ASDPosObj> coord);

    /*!
     * \brief Перевод из структуры координаты обьекта в АГЭСК в точку на Земле
     * \param coord - вектор структур  ASDPosObj
     * \return - вектор структур ASDPointEarth
     */
    static QVector <ASDPointEarth> convPosObjToPointEarth(QVector<ASDPosObj> coord);

    /*!
     * \brief Перевод из структуры координаты обьекта в АГЭСК в точку на Земле
     * \param coord - вектор структур  ASDPosObj
     * \return - вектор структур ASDPointEarth
     */
    static ASDPointEarth convPosObjToPointEarth(ASDPosObj coord);

};

#endif // ASDCONVTYPE_H
