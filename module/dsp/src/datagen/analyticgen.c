
/* ������ ��
 * ���ܣ����������ź�
 * ���������
 * �������������һ����Ŭ���ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include "../dataproc/fourier/fourier.h"
#include <math.h>

void analyticgen(double x[],  // ����Ϊn����ʼ���ʵ�������źţ�����Ž����źŵ�ʵ����ʵ���ϣ���û�б仯����ԭ����ȫ��ͬ��
	double y[],  // ����Ϊn����Ž����źŵ��鲽
	int n)  // ����Ϊ2���������ݣ���n=2^m
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
