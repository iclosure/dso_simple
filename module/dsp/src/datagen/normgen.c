
/* 函数名 ：
 * 功能：产生（a,b)区间内正态分布的随机数
 * 输入参数：
 * 输出参数：返回一个正态分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"

double normgen(double mu,    // 正态分布的参数mu
	          double sigma, // 正态分布的均方差sigma 
	          long * seed)  // 随机数种子
{
	int i;
	double x,y;

	for(i=0,x=0; i<12; i++)
		x += homogen(0.0,1.0,seed);
	x = x - 6.0;
	y = mu + x * sigma;

	return y;
}
