
/* ������ ��
 * ���ܣ�����������̬�ֲ��������
 * ���������
 * �������������һ��������̬�ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double lognormgen(double mu,    // ������̬�ֲ��Ĳ���mu
	          double sigma, // ������̬�ֲ��ľ�����sigma 
	          long * seed)  // ���������
{
	double x,y;

	y = normgen(mu,sigma,seed);
	x = exp(y);

	return x;
}
