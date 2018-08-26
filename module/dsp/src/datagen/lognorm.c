
/* 函数名 ：
 * 功能：产生对数正态分布的随机数
 * 输入参数：
 * 输出参数：返回一个对数正态分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double lognormgen(double mu,    // 对数正态分布的参数mu
	          double sigma, // 对数正态分布的均方差sigma 
	          long * seed)  // 随机数种子
{
	double x,y;

	y = normgen(mu,sigma,seed);
	x = exp(y);

	return x;
}
