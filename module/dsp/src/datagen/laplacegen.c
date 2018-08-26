
/* 函数名 ：
 * 功能：产生拉普拉斯分布的随机数
 * 输入参数：
 * 输出参数：返回一个拉普拉斯分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double laplacegen(double beta,   // 拉普拉斯分布的参数sigma
	              long * seed)   // 随机数种子
{
	double u1,u2,x;

	u1 = homogen(0.0,1.0,seed);
	u2 = homogen(0.0,1.0,seed);
	if(u1 <=0.5)
		x = - beta * log(1. - u2);
	else 
		x = beta * log(u2);

	return x;
}
