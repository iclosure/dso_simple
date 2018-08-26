
/* ������ ��
 * ���ܣ�������Ŭ��-��˹�ֲ��������
 * ���������
 * �������������һ����Ŭ��-��˹�ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"

double bernoulligaussgen(double p,  // ��Ŭ���ֲ��Ĳ���p
	double mu,  // ��˹�ֲ�����mu
	double sigma,  // ��˹�ֲ��ľ�����sigma
	long int * seed)  // ���������
{
	double u,x;

	u = homogen(0.,1.,seed);
	if(u<=p)
		x = normgen(mu,sigma,seed);
	else
		x = 0.0;

	return x;
}
