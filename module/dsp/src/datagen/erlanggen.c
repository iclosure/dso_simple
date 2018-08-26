
/* 函数名 ：
 * 功能：产生爱尔朗分布的随机数
 * 输入参数：
 * 输出参数：返回一个爱尔朗分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double erlonggen(int m,         // 爱尔朗分布的参数m
				 double beta,   // 爱尔朗分布的参数beta
	             long * seed)   // 随机数种子
{
	int i;
	double u,x;

	for(u=1.,i=0; i<m; i++)
		u = u * homogen(0.,1.,seed);
	x = - beta * log(u);

	return x;
}
