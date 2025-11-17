
#include "geotask.h"

ASDGeoTask::ASDGeoTask()
{

}

ASDGeoTask::~ASDGeoTask()
{

}
void ASDGeoTask::SphereInverse(QVector<double> pt1,QVector<double> pt2 ,double& azi,double& dist)
{
    QVector<double> pt(2,0);
    QVector<double> x(3,0);

  SpherToCart(pt2, x);
  Rotate(x, pt1[1], 2);
  Rotate(x, M_PI_2 - pt1[0], 1);
  CartToSpher(x, pt);
  azi = M_PI - pt[1];
  dist = M_PI_2 - pt[0];


}

void ASDGeoTask::SphereDirect(QVector<double> pt1,double azi,double dist,QVector<double>& pt2)
{
  QVector<double> pt(2,0);
  QVector<double> x(3,0);
  pt[0] = M_PI_2 - dist;
  pt[1] = M_PI - azi;
  SpherToCart(pt, x);
  Rotate(x, pt1[0] - M_PI_2, 1);
  Rotate(x, -pt1[1], 2);
  CartToSpher(x, pt2);
}

void ASDGeoTask::Rotate(QVector<double>& x,double a,int i)
{
  double c, s, xj;
  int j, k;

  j = (i + 1) % 3;
  k = (i - 1) % 3;
  c = cos(a);
  s = sin(a);
  xj = x[j] * c + x[k] * s;
  x[k] = -x[j] * s + x[k] * c;
  x[j] = xj;
}

void ASDGeoTask::SpherToCart(QVector<double> y, QVector<double>& x)
{
  double p;

  p = cos(y[0]);
  x[2] = sin(y[0]);
  x[1] = p * sin(y[1]);
  x[0] = p * cos(y[1]);

}

double ASDGeoTask::CartToSpher(QVector<double> x, QVector<double> &y)
{
  double p;

  p = sqrt(x[0] * x[0] + x[1] * x[1]);
  y[1] = atan2(x[1], x[0]);
  y[0] = atan2(x[2], p);

  return sqrt(p * p + x[2] * x[2]);
}



