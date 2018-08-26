
/* ������ ��
 * ���ܣ����������ʷֲ��������
 * ���������
 * �������������һ�������ʷֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double erlonggen(int m,         // �����ʷֲ��Ĳ���m
				 double beta,   // �����ʷֲ��Ĳ���beta
	             long * seed)   // ���������
{
	int i;
	double u,x;

	for(u=1.,i=0; i<m; i++)
		u = u * homogen(0.,1.,seed);
	x = - beta * log(u);

	return x;
}
