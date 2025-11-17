#ifndef DARR_H
#define DARR_H

//#include <stdio.h>
#include <malloc.h>
#include <math.h>

//#define CHK_INDEX

/*!
 * \brief Класс, описывающий двумерный массив и операции над ним. Требует доработки.
 */

class double_arr
{
     double *d;
    unsigned long U;
    void index1();
    void index2();
    unsigned long A,B,C;unsigned long n;
public:
    double_arr():d(0),n(0){}

    double_arr(unsigned long i){
        d=(double *)malloc(i*sizeof(double));
       //if(d==NULL){return(-1);}
#ifdef CHK_INDEX
     U=i;
#endif
       n=1;
    }

    double_arr(unsigned long i,unsigned long j)
	{
        d=(double *)malloc(i*j*sizeof(double));
         //  if(d==NULL){return(-1);}
	A=j;n=2;
#ifdef CHK_INDEX
     U=i;
#endif
    };

    double_arr(unsigned long i,unsigned long j,unsigned long k)
	{
        d=(double*)malloc(i*j*k*sizeof(double));
	A=j;B=k;n=3;
#ifdef CHK_INDEX
     U=i;
#endif
    };


    double_arr(unsigned long i,unsigned long j,unsigned long k,
	unsigned long l)
	{
        d=(double *)malloc(i*j*k*l*sizeof(double));
	A=j;B=k;C=l;n=4;
#ifdef CHK_INDEX
     U=i;
#endif
	};

    ~double_arr(){free(d);};

    void dimension(unsigned long i);
    void dimension(unsigned long i,unsigned long j);
    void dimension(unsigned long i,unsigned long j,unsigned long k);
    void dimension(unsigned long i,unsigned long j,unsigned long k,
	unsigned long l);

    double  *operator()(unsigned long i){
#ifdef CHK_INDEX
    if(n!=1)  index1();
    if(i>=U ) index2();
#endif
        return  d+i;

        };

    double  *operator()(unsigned long i,unsigned long j){
#ifdef CHK_INDEX
    if(n!=2) index1();
    if(i>=U || j>=A) index2();
#endif
        return (d+A*i+j);
            };

    double  *operator()(unsigned long i,unsigned long j,unsigned long k){
#ifdef CHK_INDEX
    if(n!=3) index1();
    if(i>=U || j>=A || k>=B)  index2();
#endif
        return d+B*(A*i+j)+k;
        };

    double  *operator()(unsigned long i,unsigned long j,
        unsigned long k,unsigned long l){
#ifdef CHK_INDEX
    if(n!=4) index1();
    if(i>=U || j>=A || k>=B || l>=C)  index2();
#endif
        return d+C*(B*(A*i+j)+k)+l;
        };
};
#endif
