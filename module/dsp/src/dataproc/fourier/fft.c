
/* 函数名 ：
 * 功能：计算复序列快速傅里叶正变换或反变换
 * 输入参数：
 * 输出参数：
 * 说明：
 * 备注：
 */

#include <math.h>

void fft(double x[], // 长度为n，开始存放变换数据实部，最后存放变换结果实部
	double y[],      // 长度为n，开始存放变换数据虚部，最后存放变换结果虚部
	int n,           // 必须为2的整数次幂，即n=2^m
	int sign)        // 当sign=1时，进行正变换；sign=-1时，进行反变换
{
	int i,j,k,m,r,n1,n2;
	double c,c1,e,s,s1,t,tr,ti;

	for(j=1,i=1; i<16; i++)
	{
		m = i;
		j = 2 * j;
		if(j == n) break;
	}
	n1 = n - 1;
	for(j=0,i=0; i<n1; i++)
	{
		if(i < j)
		{
			tr = x[j];
			ti = y[j];
			x[j] = x[i];
			y[j] = y[i];
			x[i] = tr;
			y[i] = ti;
		}

		k = n / 2;
		while(k < (j+1))
		{
			j = j - k;
			k = k / 2;
		}
		j = j + k;
	}

	n1 = 1;
	for(r=1; r<=m; r++)
	{
		n2 = n1;
		n1 = 2 * n1;
		e = 3.14159265359 / n2;
		c = 1.0;
		s = 0.0;
		c1 = cos(e);
		s1 = - sign * sin(e);
		for(j=0; j<n2; j++)
		{
			for(i=j; i<n; i+=n1)
			{
				k = i + n2;
				tr = c * x[k] - s * y[k];
				ti = c * y[k] + s * x[k];
				x[k] = x[i] - tr;
				y[k] = y[i] - ti;
				x[i] = x[i] + tr;
				y[i] = y[i] + ti;
			}
			t = c;
			c = c * c1 - s * s1;
			s = t * s1 + s * c1;
		}
	}

	if(sign == -1)
	{
		for(i=0; i<n; i++)
		{
			x[i] /= n;
			y[i] /=n;
		}
	}

}
