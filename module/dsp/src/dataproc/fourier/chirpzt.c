
/* ������ ��
 * ���ܣ���Zƽ�浥λԲ�ϼ������޳����е�z�任�Ĳ���ֵ
 * ���������
 * ���������
 * ˵����
 * ��ע��
 */

#include "fourier.h"
#include <malloc.h>
#include <math.h>

void chirpzt(double xr[],  /* ���ȴ����(n+m+1)������2���������ݡ�
						   ��ʼ�����������ʵ��������ű任�����ʵ�� */
	double xi[],  /* ���ȴ����(n+m+1)������2���������ݡ�
				  ��ʼ������������鲿������ű任������鲿 */
	int n,  // �������ݳ���
	int m,  // ������ݳ��ȣ���Ƶ�ʲ�������
	double f1,  // ��ʼ����Ƶ�ʣ���Ӧ�ڹ�ʽ�е�omega0/(2*pi)����λΪHz-s
	double f2)  // ��ֹ����Ƶ�ʣ���Ӧ�ڹ�ʽ�е�omega0+(M-1)*elta_omega/(2*pi)����λΪHz-s
{
	int i,j,n1,n2,len;
	double e,t,ar,ai,ph,pi,tr,ti;
	double *wr,*wr1,*wi,*wi1;

	len = n + m - 1;
	for(j=1,i=1; i<16; i++)
	{
		j = 2 * j;
		if(j > len)  { len = j; break; }
	}

	wr = (double*)malloc(len*sizeof(double));
	wi = (double*)malloc(len*sizeof(double));
	wr1= (double*)malloc(len*sizeof(double));
	wi1= (double*)malloc(len*sizeof(double));

	pi = 3.14159265358979;
	ph = 2. * pi * (f2 - f1) / (m - 1);
	n1 = (n >= m)? n : m;
	for(i=0; i<n1; i++)
	{
		e = ph * i * i / 2.0;
		wr[i] = cos(e);
		wi[i] = sin(e);
		wr1[i] = wr[i];
		wi1[i] = - wi[i];
	}

	n2 = len - n + 1;
	for(i=m; i<n2; i++)
	{
		wr[i] = 0.;
		wi[i] = 0.;
	}
	for(i=n2; i<len; i++)
	{
		j = len - i;
		wr[i] = wr[j];
		wi[i] = wi[j];
	}
	fft(wr,wi,len,1);
	ph = - 2. * pi * f1;
	for(i=0; i<n; i++)
	{
		e = ph * i;
		ar = cos(e);
		ai = sin(e);
		tr = ar * wr1[i] - ai * wi1[i];
		ti = ai * wr1[i] + ar * wi1[i];
		t = xr[i] * tr - xi[i] * ti;
		xi[i] = xr[i] * ti + xi[i] * tr;
		xr[i] = t;
	}

	for(i=n; i<len; i++)
	{
		xr[i] = 0.;
		xi[i] = 0.;
	}

	fft(xr,xi,len,1);
	for(i=0; i<len; i++)
	{
		tr = xr[i] * wr[i] - xi[i] * wi[i];
		xi[i] = xr[i] * wi[i] + xi[i] * wr[i];
		xr[i] = tr;
	}

	fft(xr,xi,len,-1);
	for(i=0; i<m; i++)
	{
		tr = xr[i] * wr1[i] - xi[i] * wi1[i];
		xi[i] = xr[i] * wi1[i] + xi[i] * wr1[i];
		xr[i] = tr;
	}

	free(wr);
	free(wi);
	free(wr1);
	free(wi1);
}