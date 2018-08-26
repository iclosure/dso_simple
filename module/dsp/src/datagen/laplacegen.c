
/* ������ ��
 * ���ܣ�����������˹�ֲ��������
 * ���������
 * �������������һ��������˹�ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double laplacegen(double beta,   // ������˹�ֲ��Ĳ���sigma
	              long * seed)   // ���������
{
	double u1,u2,x;

	u1 = homogen(0.0,1.0,seed);
	u2 = homogen(0.0,1.0,seed);
	if(u1 <=0.5)
		x = - beta * log(1. - u2);
	else 
		x = beta * log(u2);

	return x;
}
