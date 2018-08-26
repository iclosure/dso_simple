
/* ������ ��
 * ���ܣ������Իع黬��ƽ��ARMA(p,q)�ֲ��������
 * ���������
 * �������������һ����Ŭ���ֲ��������
 * ˵����
 * ��ע��
 */

#include "datagen.h"
#include <malloc.h>
#include <math.h>

void armapqgen(double a[],  // ����Ϊ(p+1)��ARMA(p,q)ģ�͵��Իع�ϵ��
	double b[],  // ����Ϊ(q+1),ARMA(p,q)ģ�͵Ļ���ƽ��ϵ��
	int p,  // ARMA(p,q)ģ�͵Ļ����Իع�ϵ��
	int q,  // ARMA(p,q)ģ�͵Ļ���ƽ������
	double mu,  // �������������õ���̬�ֲ��ľ�ֵmu
	double sigma,  // �������������õ���̬�ֲ��ľ���ֵsigma
	long int * seed,   // ���������
	double x[],        // ����Ϊn�����ARMA(p,q)ģ�͵�����
	int n)             // ARMA(p,q)ģ�����ݳ���
{
	int i,k,m;
	double s, * w;

	w =  (double*)malloc(n * sizeof(double));
	for(k=0; k<n; k++)
	{ w[k] = normgen(mu,sigma,seed); }
	x[0] = b[0] * w[0];
	for(k=1; k<=p; k++) {
		s = 0.0;
		for(i=1; i<=k; i++) {
			s += a[i] *x[k-i]; }
		s = b[0] * w[k] - s;
		if(q == 0)  {
			x[k] = s;
			continue; }

		m = (k>q)? q:k;
		for(i=1; i<=m; i++) {
			s += b[i] * w[k-i]; }
		x[k] = s; }

	for(k=(p+1); k<n; k++) {
		s = 0.0;
		for(i=1; i<=p; i++) {
			s += a[i] * x[k-i]; }
		s = b[0] * w[k] - s;
		if(q == 0) {
			x[k] = s;
			continue; }
		for(i=1; i<=q; i++) {
			s += b[i] * w[k-i]; }
		x[k] = s; }

	free(w);
}
