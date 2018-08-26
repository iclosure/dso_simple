
/* 函数名 ：
 * 功能：产生贝努力分布的随机数
 * 输入参数：
 * 输出参数：返回一个贝努力分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double bernoulligen(double p,   // 贝努力分布的参数p
	               long * seed) // 随机数种子
{
	int x;
	double u;

	u = homogen(0.,1.,seed);
	x = (u<=p)? 1:0;

	return x;
}
