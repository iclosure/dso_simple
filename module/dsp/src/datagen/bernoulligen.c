
/* ������ ��
 * ���ܣ�������Ŭ���ֲ��������
 * ���������
 * �������������һ����Ŭ���ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double bernoulligen(double p,   // ��Ŭ���ֲ��Ĳ���p
	               long * seed) // ���������
{
	int x;
	double u;

	u = homogen(0.,1.,seed);
	x = (u<=p)? 1:0;

	return x;
}
