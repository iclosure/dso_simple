
/* ������ ��
 * ���ܣ���������ʽ�ֲ��������
 * ���������
 * �������������һ������ʽ�ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <math.h>

double binomialgen(int n,  // ����ʽ�ֲ��Ĳ���n
	double p,  // ����ʽ�ֲ��Ĳ���p
	long int * seed)  // ���������
{
	int i;
	double x;

	for(x=0,i=0; i<n; i++)
		x +=bernoulligen(p,seed);

	return x;
}
