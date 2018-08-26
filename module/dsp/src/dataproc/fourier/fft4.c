
/* 函数名 ：
 * 功能：计算复序列的基5快速傅里叶变换(尚未调试通过)
 * 输入参数：
 * 输出参数：
 * 说明：
 * 备注：
 */

#include <math.h>

void fft4(double x[], // 长度为n，开始存放变换数据实部，最后存放变换结果实部
	double y[],  // 长度为n，开始存放变换数据虚部，最后存放变换结果虚部
	int n) // 必须为4的整数次幂，即n=4^m
{
	int i,j,k,m,i1,i2,i3,n1,n2;
	double a,b,c,e,r1,r2,r3,r4,s1,s2,s3,s4;
	double co1,co2,co3,si1,si2,si3;

	for(j=1,i=1; i<10; i++)
	{
		m = i;
		j = 4 * j;
		if(j == n)break;
	}

	n2 = n;
	for(k=1; k<=m; k++)
	{
		n1 = n2;
		n2 = n2 / 4;
		e = 6.28318530718 / n1;
		a = 0.0;
		for(j=0; j<n2; j++)
		{
			b = a + a;
			c = a + b;
			co1 = cos(a);
			co2 = cos(b);
			co3 = cos(c);
			si1 = sin(a);
			si2 = sin(b);
			si3 = sin(c);
			a = (j+1) * e;
			for(i=j; i<n; i=i+n1)
			{
				i1 = i  + n2;
				i2 = i1 + n2;
				i3 = i2 + n2;
				r1 = x[i] + x[i2];
				r3 = x[i] - x[i2];
				s1 = y[i] + y[i2];
				s3 = y[i] - y[i2];
				r2 = x[i1] + x[i3];
				r4 = x[i1] - x[i3];
				s2 = y[i1] + y[i3];
				s4 = y[i1] - y[i3];
				x[i] = r1 - r2;
				r2 = r1 - r2;
				r1 = r3 - s4;
				r3 = r3 + s4;
				y[i] = s1 + s2;
				s2 = s1 - s2;
				s1 = s3 + r4;
				s3 = s3 - r4;
				x[i1] = co1 * r3 + si1 * s3;
				y[i1] = co1 * s3 - si1 * r3;
				x[i2] = co2 * r2 + si2 * s2;
				y[i2] = co2 * s2 - si2 * r2;
				x[i3] = co3 * r1 + si3 * s1;
				y[i3] = co3 * s1 - si3 * r1;
			}
		}
	}

	n1 = n - 1;
	for(j=0,i=0; i<n1; i++)
	{
		if(i < j)
		{
			r1 = x[j];
			s1 = y[j];
			x[j] = x[i];
			y[j] = y[i];
			x[i] = r1;
			y[i] = s1;
		}

		k = n / 4;
		while(3*k < (j+1))
		{
			j = j - 3 * k;
			k = k / 4;
		}

		j = j + k;
	}
}
