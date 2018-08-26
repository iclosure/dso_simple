
/* 函数名 ：
 * 功能：产生柯西分布的随机数
 * 输入参数：
 * 输出参数：返回一个柯西分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include <math.h>

double cauchygen(double alpha,  // 柯西分布的参数alpha
				 double beta,   // 柯西分布的参数beta
	             long * seed)   // 随机数种子
{
	double u,x;

	u = homogen(0.,1.,seed);
	x = alpha - beta / tan(3.1415926 * u);

	return x;
}
