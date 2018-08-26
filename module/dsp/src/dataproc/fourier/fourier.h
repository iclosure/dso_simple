
/*****************************
 *
 *      傅里叶变换函数集
 *
 *****************************/

#ifndef FOURIER_H
#define FOURIER_H

void dft(double x[],double y[],double a[],double b[],int n,int sign);
void fft(double x[],double y[],int n,int sign);
void chirpzt(double xr[],double zi[],int n,int m,double f1,double f2);
void fft4(double x[],double y[],int n);
void pft(double x[],double y[], int n,int m,int ni[]);
//void rfft(double x[],int n);
void irrft(double x[],int n);
void splitfft(double x[],double y[],int n);




#endif /* FOURIER_H */
