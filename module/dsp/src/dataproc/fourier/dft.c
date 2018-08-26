
/* 函数名 ：
 * 功能：计算序列的离散傅里叶正变换或反变换
 * 输入参数：
 * 输出参数：
 * 说明：
 * 备注：
 */

#include <math.h>

void dft(double x[], // 变换数据实部
	double y[],      // 变换数据虚部
	double a[],      // 变换结果实部
	double b[],      // 变换结果虚部
	int n,           // 变换数据长度
	int sign)        // 当sign=1时，进行正变换；sign=-1时，进行反变换
{
	int i,k;

	double c,d,q,w,s;

	q = 6.28318530718 / n;
	for(k=0; k<n; k++)
	{
		w = k * q;
		a[k] = b[k] = 0.0;
		for(i=0; i<n; i++)
		{
			d = i * w;
			c = cos(d);
			s = sin(d) * sign;
			a[k] += c * x[i] + s * y[i];
			b[k] += c * y[i] - s * x[i];
		}
	}
	if(sign == -1)
	{
		c = 1.0 / n;
		for(k=0; k<n; k++)
		{
			a[k] = c * a[k];
			b[k] = c * b[k];
		}
	}

}
