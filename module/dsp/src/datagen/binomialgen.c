
/* 函数名 ：
 * 功能：产生二项式分布的随机数
 * 输入参数：
 * 输出参数：返回一个二项式分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double binomialgen(int n,  // 二项式分布的参数n
	double p,  // 二项式分布的参数p
	long int * seed)  // 随机数种子
{
	int i;
	double x;

	for(x=0,i=0; i<n; i++)
		x +=bernoulligen(p,seed);

	return x;
}
