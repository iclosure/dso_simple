
/* 函数名 ：
 * 功能：计算共轭对称复序列的快速傅里反变换，起变换结果是实数。
 * 输入参数：
 * 输出参数：
 * 说明：
 * 备注：
 */

#include "fourier.h"
#include <math.h>

void irfft(double x[], /* 长度为n，开始存放具有共轭对称性的复序列，
					   其存储顺序为[Re(0),Re(1),...,Re(n/2),Im(n/2-1),..,Im(1)]。
					   其中Re(0)=X(0),Re(n?2)=X(n/2)。根据X(k)的共轭对称性很容易写出后半部分的值。
					   最后存放变换结果x(i=0,1,...,n-1),这里x(i)是实数。*/
	int n)          // 数据长度。必须是2的整数次幂，即n=2^m
{
	int i,j,k,m,i1,i2,i3,i4,i5,i6,i7,i8,n2,n4,n8,id,is;
	double a,e,a3,t1,t2,t3,t4,t5,cc1,cc3,ss1,ss3;
	double *y;

	y = x;

	for(j=1,i=1; i<16; i++)
	{
		m = i;
		j = 2 * j;
		if(j == n) break;
	}

	n2 = 2 * n;
	for(k=1; k<m; k++)
	{
		is = 0;
		id = n2;
		n2 = n2 / 2;
		n4 = n2 / 4;
		n8 = n2 / 8;
		e = 6.28318530718 / n2;
		do {
			for(i=is; i<n; i+=id)
			{
				i1 = i;
				i2 = i1 + n4;
				i3 = i2 + n4;
				i4 = i3 + n4;
				t1    = x[i1] - x[i3];
				x[i1] = x[i1] + x[i3];
				x[i2] = 2 * x[i2];
				x[i3] = t1 - 2 * x[i4];
				x[i4] = t1 + 2 * x[i4];
				if(n4 == 1) continue;
				i1 += n8;
				i2 += n8;
				i3 += n8;
				i4 += n8;
				t1 = (x[i2] - x[i1]) / sqrt(2.0);
				t2 = (x[i4] + x[i3]) / sqrt(2.0);
				x[i1] = x[i1] + x[i2];
				x[i2] = x[i4] - x[i3];
				x[i3] = 2 * (- t2 - t1);
				x[i4] = 2 * (- t2 + t1);
			}

			is = 2 * id - n2;
			id = 4 * id;
		} while( is < (n-1));

		a = e;
		for(j=1; j<n8; j++)
		{
			a3 = 3 * a;
			cc1 = cos(a);
			ss1 = sin(a);
			cc3 = cos(a3);
			ss3 = sin(a3);
			a = (j + 1) * e;
			is = 0;
			id = 2 * n2;
			do {
				for(i=is; i<=(n-1); i=i+id)
				{
					i1 = i + j;
					i2 = i1 + n4;
					i3 = i2 + n4;
					i4 = i3 + n4;
					i5 = i + n4 - j;
					i6 = i5 + n4;
					i7 = i6 + n4;
					i8 = i7 + n4;
					t1 = x[i1] - x[i6];
					x[i1] = x[i1] + x[i6];
					t2 = x[i5] - x[i2];
					x[i5] = x[i2] + x[i5];
					t3 = x[i8] + x[i3];
					x[i6] = x[i8] - x[i3];
					t4 = x[i4] + x[i7];
					x[i2] = x[i4] - x[i7];
					t5 = t1 - t4;
					t1 = t1 + t4;
					t4 = t2 - t3;
					t2 = t2 + t3;
					x[i3] =   t5 * cc1 + t4 * ss1;
					x[i7] = - t4 * cc1 + t5 * ss1;
					x[i4] =   t1 * cc3 - t2 * ss3;
					x[i8] =   t2 * cc3 + t1 * ss3;
				}

				is = 2 * id - n2;
				id = 4 * id;
			} while(is < (n-1));
		}
	}

	is = 0;
	id = 4;
	do {
		for(i=is; i<n; i+=id)
		{
			i1 = i + 1;
			t1 = x[i];
			x[i]  = t1 + x[i1];
			x[i1] = t1 - x[i1];
		}

		is = 2 * id - 2;
		id = 4 * id;
	} while(is < (n-1));

	for(j=0,i=0; i<(n-1); i++)
	{
		if(i < j)
		{
			t1 = x[j];
			x[j] = x[i];
			x[i] = t1;
		}

		k = n / 2;
		while(k < (j+1))
		{
			j = j - k;
			k = k / 2;
		}

		j = j + k;
	}

	for(i=0; i<n; i++)
		x[i] = x[i] / n;

}