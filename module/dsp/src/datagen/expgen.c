
/* 函数名 ：
 * 功能：产生指数分布的随机数
 * 输入参数：
 * 输出参数：返回一个指数分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double expgen(double beta,       // 指数分布的参数sigma
	              long * seed)   // 随机数种子
{
	double u,x;

	u = homogen(0.0,1.0,seed);
	x = - beta * log(u);

	return x;
}
