
/* 函数名 ：
 * 功能：产生瑞利分布的随机数
 * 输入参数：
 * 输出参数：返回一个瑞利分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double raylieghgen(double sigma,   // 瑞利分布的参数sigma
	               long * seed)    // 随机数种子
{
	double u,x;

	u = homogen(0.,1.,seed);
	x = - 2. * log(u);
	x = sigma * sqrt(x);

	return x;
}
