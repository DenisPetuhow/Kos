#ifndef ASDGEOTASK_H
#define ASDGEOTASK_H
#include "QVector"
#include <stdlib.h>
#include <math.h>
class ASDGeoTask
{
public:
    ASDGeoTask();
    ~ASDGeoTask();

    /*!
     * \brief Решение прямой геодезической задачи
     * нахождение положения точки по координатам исходного пункта
     * и значениям начального направления и расстояния
     * \param pt1 - широта и долгота исходного пункта (рад)
     * \param azi - азимут
     * \param dist- расстояние сферическое (рад)
     * \param pt2 - широта и долгота искомой точки (рад)
     */
    static void SphereDirect(QVector<double> pt1,double azi,double dist, QVector<double>& pt2);

    /*!
     * \brief Решение обратной геодезической задачи
     * нахождение начального направления и расстояния между двумя точками с известными координатами
     * \param pt1 - широта и долгота точки 1 (рад)
     * \param pt2 - широта и долгота точки 2 (рад)
     * \param azi - определяется азимут начального направления
     * \param dist - расстояние сферическое (рад)
     */
    static void SphereInverse(QVector<double> pt1, QVector<double> pt2 , double& azi, double& dist);

    /*!
     * \brief Преобразование сферических координат в декартовы
     * \param y - широта и долгота (рад)
     * \param x - вектор x,y,z
     */
    static void SpherToCart(QVector<double> y,QVector<double>& x);

    /*!
     * \brief Вращение вокруг координатной оси
     * \param x - входной-выходной веткор
     * \param a - угол поворота(рад)
     * \param i - номеер координатной оси (0..2)
     */
    static void Rotate(QVector<double>& x,double a,int i);

    /*!
     * \brief Преобразование вектора в сферические координаты
     * \param x - вектор (x,y,z)
     * \param y - широта, долгота
     * \return длину вектора
     */
    static double CartToSpher(QVector<double> x, QVector<double> &y);



};

#endif //ASDGEOTASK_H
