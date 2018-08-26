
/* 函数名 ：
 * 功能：产生自回归滑动平均ARMA(p,q)分布的随机数
 * 输入参数：
 * 输出参数：返回一个贝努力分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <malloc.h>
#include <math.h>

void armapqgen(double a[],  // 长度为(p+1)，ARMA(p,q)模型的自回归系数
	double b[],  // 长度为(q+1),ARMA(p,q)模型的滑动平均系数
	int p,  // ARMA(p,q)模型的滑动自回归系数
	int q,  // ARMA(p,q)模型的滑动平均阶数
	double mu,  // 产生白噪声所用的正态分布的均值mu
	double sigma,  // 产生白噪声所用的正态分布的均方值sigma
	long int * seed,   // 随机数种子
	double x[],        // 长度为n，存放ARMA(p,q)模型的数据
	int n)             // ARMA(p,q)模型数据长度
{
	int i,k,m;
	double s, * w;

	w =  (double*)malloc(n * sizeof(double));
	for(k=0; k<n; k++)
	{ w[k] = normgen(mu,sigma,seed); }
	x[0] = b[0] * w[0];
	for(k=1; k<=p; k++) {
		s = 0.0;
		for(i=1; i<=k; i++) {
			s += a[i] *x[k-i]; }
		s = b[0] * w[k] - s;
		if(q == 0)  {
			x[k] = s;
			continue; }

		m = (k>q)? q:k;
		for(i=1; i<=m; i++) {
			s += b[i] * w[k-i]; }
		x[k] = s; }

	for(k=(p+1); k<n; k++) {
		s = 0.0;
		for(i=1; i<=p; i++) {
			s += a[i] * x[k-i]; }
		s = b[0] * w[k] - s;
		if(q == 0) {
			x[k] = s;
			continue; }
		for(i=1; i<=q; i++) {
			s += b[i] * w[k-i]; }
		x[k] = s; }

	free(w);
}
