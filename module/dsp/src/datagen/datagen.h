
/*****************************
 *
 *      数据生成函数集
 *
 *****************************/

#ifndef DATAGEN_H
#define DATAGEN_H

double homogen(double a,double b, long *seed);
double normgen(double mu,double sigma,long *seed);
double lognormgen(double mu,double sigma,long *seed);
double weibullgen(double alpha,double beta,long *seed);
double raylieghgen(double sigma,long *seed);
double laplacegen(double beta,long *seed);
double expgen(double beta,long *seed);
double erlonggen(int m,double beta,long *seed);
double cauchygen(double alpha,double beta,long *seed);
double bernoulligen(double p,long *seed);
void armapqgen(double a[],double b[],int p,int q,double mu,double sigma,long int * seed,double x[],int n);
double bernoulligaussgen(double p,double mu,double sigma,long *seed);
double binomialgen(int n,double p,long *seed);






#endif /* DATAGEN_H */
