
/* 函数名 ：
 * 功能：产生韦伯分布的随机数
 * 输入参数：
 * 输出参数：返回一个韦伯分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"  // 调用homogeneous
#include <math.h>

double weibullgen(double alpha,  // 韦伯分布的参数alpha
				  double beta,   // 韦伯分布的均方差beta
	              long * seed)   // 随机数种子
{
	double u,x;

	u = homogen(0.,1.,seed);
	u = - log(u);
	x = beta * pow(u,1.0 / alpha);

	return x;
}
