#ifndef SPLINE_H
#define SPLINE_H
#include "math.h"
#include "darr.h"

/*!
 * \brief Класс, задающий сплайн
 */

class spline
{
    double_arr A,Q;
    double *Z_arr,*X_arr;
    int Zdim,Xdim;
    double  *d;
    double  *a(int i,int j){return d+(i<<2)+j;};
    void SetCum(const double *, double_arr & ,const int );
    void SetBiCum(double_arr&);
    void Cum( double , const double *, const int, double&, double& );
public:
    spline();
    ~spline();
    spline(int,double *,int,double *,double_arr&);
    spline(int,double *,double_arr&);
    double BiCum(const double,const double,double&,double&);
    double Cum(const double,double&);
    //interpol for n>=2 and n=4  --->INTERPOLATION (NEWTON)
double intpNewton( double* x ,double* y, double xt,int n);
	};
#endif
