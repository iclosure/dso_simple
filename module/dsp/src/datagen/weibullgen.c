
/* ������ ��
 * ���ܣ�����Τ���ֲ��������
 * ���������
 * �������������һ��Τ���ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"  // ����homogeneous
#include <math.h>

double weibullgen(double alpha,  // Τ���ֲ��Ĳ���alpha
				  double beta,   // Τ���ֲ��ľ�����beta
	              long * seed)   // ���������
{
	double u,x;

	u = homogen(0.,1.,seed);
	u = - log(u);
	x = beta * pow(u,1.0 / alpha);

	return x;
}
