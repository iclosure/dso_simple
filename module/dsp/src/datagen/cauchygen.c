
/* ������ ��
 * ���ܣ����������ֲ��������
 * ���������
 * �������������һ�������ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double cauchygen(double alpha,  // �����ֲ��Ĳ���alpha
				 double beta,   // �����ֲ��Ĳ���beta
	             long * seed)   // ���������
{
	double u,x;

	u = homogen(0.,1.,seed);
	x = alpha - beta / tan(3.1415926 * u);

	return x;
}
