
/* ������ ��
 * ���ܣ�������a,b)��������̬�ֲ��������
 * ���������
 * �������������һ����̬�ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"

double normgen(double mu,    // ��̬�ֲ��Ĳ���mu
	          double sigma, // ��̬�ֲ��ľ�����sigma 
	          long * seed)  // ���������
{
	int i;
	double x,y;

	for(i=0,x=0; i<12; i++)
		x += homogen(0.0,1.0,seed);
	x = x - 6.0;
	y = mu + x * sigma;

	return y;
}
