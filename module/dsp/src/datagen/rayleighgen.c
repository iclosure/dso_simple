
/* ������ ��
 * ���ܣ����������ֲ��������
 * ���������
 * �������������һ�������ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double raylieghgen(double sigma,   // �����ֲ��Ĳ���sigma
	               long * seed)    // ���������
{
	double u,x;

	u = homogen(0.,1.,seed);
	x = - 2. * log(u);
	x = sigma * sqrt(x);

	return x;
}
