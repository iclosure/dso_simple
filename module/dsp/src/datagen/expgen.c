
/* ������ ��
 * ���ܣ�����ָ���ֲ��������
 * ���������
 * �������������һ��ָ���ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double expgen(double beta,       // ָ���ֲ��Ĳ���sigma
	              long * seed)   // ���������
{
	double u,x;

	u = homogen(0.0,1.0,seed);
	x = - beta * log(u);

	return x;
}
