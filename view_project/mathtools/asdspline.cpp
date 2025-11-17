#include <stdio.h>


#include "asdspline.h"


 spline::spline()
 {
     Zdim=4;
     Xdim=4;
     Z_arr=new double[Zdim+2];
     X_arr=new double[Xdim+2];

 }

spline::spline(int Zd,double *Z,int Xd,double *X,double_arr &F):
    Zdim(Zd),Xdim(Xd)
{
//    FILE *stream=fopen("tmp.dat","w");
    Z_arr=new double[Zdim+2];
    X_arr=new double[Xdim+2];
    double_arr F_arr(Xdim+2,Zdim+2);
    for ( int x=1;x<=Xdim;x++ )
    {
	X_arr[x]=X[x-1];
	*F_arr(x,0)=0;
	*F_arr(x,Zdim+1)=0;
	for ( int z=1;z<=Zdim;z++ )
	    *F_arr(x,z)=*F(x-1,z-1);
    }
    for (int z=0;z<Zdim+2;z++ )
    {
	*F_arr(0,z)=0;
	*F_arr(Xdim+1,z)=0;
	Z_arr[z]=Z[z-1];
    }
    Z_arr[0]=Z_arr[2];
    Z_arr[Zdim+1]=Z_arr[Zdim-1];
    X_arr[0]=X_arr[2];
    X_arr[Xdim+1]=X_arr[Xdim-1];
    int Mdim=Xdim>Zdim ? Xdim : Zdim;
    Q.dimension(4,Mdim+2);
    A.dimension(Xdim,Zdim,4,4);
    SetBiCum(F_arr);
}
spline::spline(int Zd,double *Z,double_arr &F):    Zdim(Zd)
{
    Z_arr=new double[Zdim+2];
    double_arr F_arr(Zdim+2);
    *F_arr(0)=0;
    *F_arr(Zdim+1)=0;
	for ( int z=1;z<=Zdim;z++ )
        *F_arr(z)=*F(z-1);

    for (int zz=1;zz<Zdim+2;zz++ )//zz=0 Z_arr[0] присв ив ется после цикл 
    {
	Z_arr[zz]=Z[zz-1];
    }
    Z_arr[0]=Z_arr[2];
    Z_arr[Zdim+1]=Z_arr[Zdim-1];
    int Mdim=Zdim ;
    Q.dimension(4,Mdim+2);
    SetCum(Z_arr,F_arr,Zdim+2);


}
   spline::~spline(){

if(Zdim>3){ delete [] Z_arr;}
      //  if(Z_arr!=NULL) {delete [] Z_arr;}

    // if(X_arr!=NULL) free(X_arr);

     //if(d!=NULL) free(d);
}

void spline::SetBiCum(double_arr &F_arr)
{
    int Mdim=Xdim>Zdim ? Xdim : Zdim;
    double_arr St(Mdim+2),Sb(Mdim),c(Zdim);
    double H;

    for(int z=1;z<Zdim+1;z++)
    {
	for(int x=0;x<Xdim+2;x++) *St(x)=*F_arr(x,z);
	SetCum(X_arr,St,Xdim+2);
        for (int x=0;x<Xdim;x++ )
	for (int k=0;k<4;k++ ) (*A(x,z-1,0,k))=*Q(k,x+1);
    }
    for (int x=1;x<Xdim+1;x++ )
    {
        for (int z=0;z<Zdim+2;z++ ) *St(z)=*F_arr(x,z);
	SetCum(Z_arr,St,Zdim+2);
        for (int z=0;z<Zdim;z++ )
	for (int l=1;l<4;l++ )
	*A(x-1,z,l,0)=*Q(l,z+1);
    }
    for (int z=0;z<Zdim+2;z++ ) *St(z)=*F_arr(0,z);
	SetCum(Z_arr,St,Zdim+2);
        for (int z=0;z<Zdim;z++ ) *Sb(z)=*Q(2,z+1);
        for (int z=0;z<Zdim+2;z++ ) *St(z)=*F_arr(Xdim+1,z);
	SetCum(Z_arr,St,Zdim+2);
        for (int z=0;z<Zdim;z++ ) *c(z)=*Q(2,z+1);
        for (int z=0;z<Zdim;z++ )
	{
	    *St(0)=*Sb(z);
	    *St(Xdim+1)=*c(z);
        for (int x=0;x<Xdim;x++ ) *St(x+1)=*A(x,z,2,0);
	    SetCum(X_arr,St,Xdim+2);
            for (int x=0;x<Xdim;x++ )
	    for (int k=1;k<4;k++ )
	*A(x,z,2,k)=*Q(k,x+1);
	}
        for ( int z=Zdim-2;z>=0;z-- )
	{
	    H=Z_arr[z+2]-Z_arr[z+1];
            for (int x=0;x<Xdim-1;x++ )
	    for (int k=1;k<4;k++ )
	    {
	*A(x,z,1,k)=(*A(x,z+1,0,k)-*A(x,z,0,k))/H-
	(*A(x,z+1,2,k)+*A(x,z,2,k)*2)*H/3;
	*A(x,z,3,k)=(*A(x,z+1,2,k)-*A(x,z,2,k))/(3*H);
	    }

    }

}
void spline::SetCum(const double *Z, double_arr &V,const int L3)
{
    double r1,r2,r3,r4,r5,r6,r7,r8;
    int L2=L3-1, L1=L3-2, L0=L3-3 ;

    *Q(0,0)=1;
    *Q(1,0)=0;
    *Q(2,0)=0;
    for ( int n=1;n<L2;n++ )
    {
	r1=Z[n]-Z[n-1];
	r2=Z[n+1]-Z[n];
	r3=Z[n+1]-Z[n-1];
	if(r1==0) r4=*V(n-1); else r4=(*V(n)-*V(n-1))/r1;
	if(r2==0) r5=*V(n+1); else r5=(*V(n+1)-*V(n))/r2;
	if(r3==0)
	{
	    r7=0; r8=0;
	    if(n==1) r6=3*(*V(n-1)/2); else r6=3*(*V(n+1)/2);
	}
	else
	{
	    r6=3*(r5-r4)/r3;
	    r7=r1/r3;
	    r8=r2/r3;
	}
	r3=2+r7*(*Q(1,n-1));
	*Q(0,n)=-r7*(*Q(0,n-1))/r3;
	*Q(1,n)=-r8/r3;
	*Q(2,n)=(r6-r7*(*Q(2,n-1)))/r3;
    }
    r1=*Q(0,L1);
    *Q(0,L1)=(1-*Q(0,L0))/(*Q(1,L0));
    r2=*Q(2,L1);
    *Q(2,L1)=-*Q(2,L0)/(*Q(1,L0));
    for(int n=L0;n>0;n--)
    {
	*Q(2,n)= *Q(1,n)*(*Q(2,n+1)) + *Q(2,n);
	*Q(0,n)= *Q(1,n)*(*Q(0,n+1)) + *Q(0,n);
    }
    r3=-(*Q(1,L1)*(*Q(2,2))+r2-*Q(2,L1))/(*Q(1,L1)*(*Q(0,2))+r1-*Q(0,L1));
    for(int n=1;n<L2;n++)
    *Q(2,n)+=(*Q(0,n)*r3);
    for(int n=2;n<L2;n++)
    {
	r2=Z[n]-Z[n-1];
	*Q(0,n-1)=*V(n-1);
	*Q(1,n-1)=(*V(n)-*V(n-1))/r2-(2*(*Q(2,n-1))+(*Q(2,n)))*r2/3;
	*Q(3,n-1)=(*Q(2,n)-*Q(2,n-1))/(3*r2);
    }
}
void spline::Cum(const double cX,
	const double *X,
	const int l3,
	double& F,
	double& dFdX)
{   int n;
    for (  n=2;n<l3-1 && X[n]<cX;n++ ) ;
    double r1=cX-X[n-1];
    F=*Q(0,n-1)+r1*(*Q(1,n-1)+r1*(*Q(2,n-1)+r1*(*Q(3,n-1))));
    dFdX=*Q(1,n-1)+r1*(*Q(2,n-1)*2+r1*(*Q(3,n-1))*3);

}

double spline::BiCum(const double X,const double Z,double& dFdX,double& dFdZ)
{
    double x1,z1,f0,f1,fx,fz;
    int x,z;
    for (  x=0; x<Xdim-1 && X_arr[x+2]<=X;x++ ) ;
    for (  z=0; z<Zdim-1 && Z_arr[z+2]<=Z; z++ ) ;
    d=(double  *)A(x,z,0,0);
    x1=X-X_arr[x+1];
    z1=Z-Z_arr[z+1];
    f0=0;
    f1=0;
    dFdX=0;
    dFdZ=0;
    for ( int l=3;l>0;l-- )
    {
	fx=0; fz=0;
	for ( int k=3;k>=0;k-- )
	{
	    fx=fx*z1+*a(k,l);
	    fz=fz*x1+*a(l,k);

	}
	f0=f0*z1+fz;
	dFdX=dFdX*x1+l*fx;
	dFdZ=dFdZ*z1+l*fz;
    }
    for (int k=3;k>=0;k-- ) f1=f1*x1+*a(0,k);
    return f0*z1+f1;
}
double spline::Cum( double Z,double& dFdZ)
{
    double F;

    if(Z<Z_arr[0]) Z=Z_arr[0];
    if(Z>Z_arr[Zdim]) Z=Z_arr[Zdim];
     Cum(Z,Z_arr,Zdim+2,F,dFdZ);
     return F;
}
// lin interpol for n>=2 and n=4  --->INTERPOLATION (NEWTON)
double spline::intpNewton( double* x ,double* y, double xt,int n)
{
    double F=0.;
    if(n<2) return F;
    if(n==2)
    {
    F=y[0]+(xt-x[0])*(y[1]-y[0])/(x[1]-x[0]);

     return F;
    }
    if(n==3)
    {
     if((xt>=x[0])&&(xt<x[1]))
        {
    F=y[0]+(xt-x[0])*(y[1]-y[0])/(x[1]-x[0]);

     return F;
        }else
     {
         F=y[1]+(xt-x[1])*(y[2]-y[1])/(x[2]-x[1]);

          return F;
     }
    }
    if(n==4)
    {

    double x21=(y[1]-y[0])/(x[1]-x[0]);
    double x32=(y[2]-y[1])/(x[2]-x[1]);
    double x43=(y[3]-y[2])/(x[3]-x[2]);
    double x321=(x32 - x21)/(x[2]-x[0]);
    double   x432 =(x43 - x32)/(x[3]-x[1]);
    double x4321=(x432-x321)/(x[3]-x[0]);
        F=y[0]+x21*(xt-x[0])+
     x321*(xt-x[0])*(xt-x[1])+
     x4321*(xt-x[0])*(xt-x[1])*(xt-x[2]);


       return F;
    }
     return F;
}
