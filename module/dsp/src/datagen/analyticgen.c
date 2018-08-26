
/* 函数名 ：
 * 功能：产生解析信号
 * 输入参数：
 * 输出参数：返回一个贝努力分布的随机数
 * 说明：
 * 备注：
 */

#include "datagen.h"
#include "../dataproc/fourier/fourier.h"
#include <math.h>

void analyticgen(double x[],  // 长度为n，开始存放实数输入信号，最后存放解析信号的实部（实际上，它没有变化，与原来完全相同）
	double y[],  // 长度为n，存放解析信号的虚步
	int n)  // 必须为2的整数次幂，即n=2^m
{
	int i,n1;

	n1 = n / 2;
	for(i=0; i<n; i++)
		y[i] = 0.0;

	fft(x,y,n,1);
	for(i=1; i<n1; i++)
	{
		x[i] = 2 * x[i];
		y[i] = 2 * y[i];
	}
	for(i=n1; i<n; i++)
	{
		x[i] = 0.0;
		y[i] = 0.0;
	}

	fft(x,y,n,-1);

}
