
/* 函数名 ：
 * 功能：计算复序列的基4快速傅里叶变换
 * 输入参数：
 * 输出参数：
 * 说明：
 * 备注：
 */

#include <math.h>

/* 函数正文 */
void  splitfft(double x[], // 双精度实型一组数组，长度为n。开始时存放要变换数据的实部，最后存放变换结果的实部。
	double y[],            // 双精度实型一组数组，长度为n。开始时存放要变换数据的虚部，最后存放变换结果的虚部。
	int n)                 // 整型变量。数据长度。必须是2的整数次幂，即n=2^m。
{
	int i,j,k,m,i1,i2,i3,n1,n2,n4,id,is;
	double a,e,a3,r1,r2;
	double s1,s2,s3,cc1,cc3,ss1,ss3;

	for(j=1,i=1; i<16; i++) {
		m = i;
		j = 2 * j;
		if(j == n)break;
	}
	n2 = 2 * n;
	for(k=1; k<m; k++) {
		n2 = n2 / 2;
		n4 = n2 / 4;
		e = 6.28318530718 / n2;
		a = 0;
		for(j=0; j<n4; j++) {
			a3 = 3 * a;
			cc1 = cos(a);
			ss1 = sin(a);
			cc3 = cos(a3);
			ss3 = sin(a3);
			a = (j+1) * e;
			is = j;
			id = 2 * n2;
			do{
				for(i=is;i<(n-1); i+=id) {
					i1 = i + n4;
					i2 = i1 + n4;
					i3 = i2 + n4;
					r1 = x[i] - x[i2];
					x[i] = x[i] + x[i2];
					r2 = x[i1] - x[i3];
					x[i1] = x[i1] + x[i3];
					s1 = y[i] - y[i2];
					y[i] = y[i] + y[i2];
					s2 = y[i1] - y[i3];
					y[i1] = y[i1] + y[i3];
					s3 = r1 - s2;
					r1 = r1 + s2;
					s2 = r2 - s1;
					r2 = r2 + s1;
					x[i2] = r1 * cc1 - s2 * ss1;
					y[i2] = - s2 * cc1 - r1 * ss1;
					x[i3] = s3 * cc3 + r2 * ss3;
					y[i3] = r2 * cc3 - s3 * ss3;
				}
				is = 2 * id - n2 + j;
				id = 4 * id;
			} while(is < (n-1));
		}
	}
	is = 0; id = 4;
	do {
		for(i=is; i<n; i+=id) {
			i1 = i + 1;
			r1 = x[i];
			r2 = y[i];
			x[i] = r1 + x[i1];
			y[i] = r2 + y[i1];
			x[i1] = r1 - x[i1];
			y[i1] = r2 - y[i1];
		}
		is = 2 * id - 2;
		id = 4 * id;
	} while(is < (n-1));

	n1 = n - 1;
	for(j=0,i=0; i<n1; i++) {
		if(i < j) {
			r1 = x[j];
			s1 = y[j];
			x[j] = x[i];
			y[j] = y[i];
			x[i] = r1;
			y[i] = s1;
		}

		k = n / 2;
		while(k < (j+1)) {
			j = j - k;
			k = k / 2;
		}
		j = j + k;
	}
}
