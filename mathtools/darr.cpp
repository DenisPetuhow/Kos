#include "darr.h"

#define CHK_INDEX

void double_arr::dimension(unsigned long i){
	if(n==0)
            d=(double *)malloc(i*sizeof(double));
 //       else {exit(-1);}
//       if(d==0){exit(-1);}
#ifdef CHK_INDEX
     U=i;
#endif
       n=1;
    };
void double_arr::dimension(unsigned long i,unsigned long j){
	if(n==0)
        d=(double *)malloc(i*j*sizeof(double));
   //     else {exit(-1);}
     //   if(d==0){exit(-1);}
	A=j;n=2;
#ifdef CHK_INDEX
     U=i;
#endif
    };
void double_arr::dimension(unsigned long i,unsigned long j,unsigned long k){
	if(n==0)
        d=(double *)malloc(i*j*k*sizeof(double));
 //       else {exit(-1);}
       // if(d==0){exit(-1);}
	A=j;B=k;n=3;
#ifdef CHK_INDEX
     U=i;
#endif
    };

void double_arr::dimension(unsigned long i,unsigned long j,
    unsigned long k,unsigned long l){
	if(n==0)
        d=(double *)malloc(i*j*k*l*sizeof(double));
 //       else {exit(-1);}
  //      if(d==NULL){exit(-1);}
	A=j;B=k;C=l;n=4;
#ifdef CHK_INDEX
     U=i;
#endif
    };
#ifdef CHK_INDEX
void double_arr::index1() {};
//{exit(-1);};
void double_arr::index2() {};
 //       {exit(-2);};
#endif
