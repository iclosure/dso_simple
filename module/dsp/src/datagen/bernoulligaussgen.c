
/* 函数名 ：
 * 功能：产生贝努力-高斯分布的随机数
 * 输入参数：
 * 输出参数：返回一个贝努力-高斯分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"

double bernoulligaussgen(double p,  // 贝努力分布的参数p
	double mu,  // 高斯分布参数mu
	double sigma,  // 高斯分布的均方差sigma
	long int * seed)  // 随机数种子
{
	double u,x;

	u = homogen(0.,1.,seed);
	if(u<=p)
		x = normgen(mu,sigma,seed);
	else
		x = 0.0;

	return x;
}
