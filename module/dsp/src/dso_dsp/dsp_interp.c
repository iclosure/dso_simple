
#include "GUI_Protected.h"
#include "LCD.h"
#include "dsp.h"
#include <string.h>



/*********************************************************
 *                         ���Ҳ�ֵ
 *
 *   ����˵����->I16 -- signed short;  TRIG_sin -- �������Ҳ�����sin();
 *             ->���м������ȫ��Ϊ������㡣
 *             ->ֻҪ���� (SampleN-1)�ܱ�InterpN�������ܻ���൱�ߵĲ�ֵ��ȷ�ȡ�
 *             ->�����е�(<<11)��Ϊ����߾�ȷ�ȶ��Ŵ����ݵġ�
 *             ->sample[m]*355 -- 355/226=?pi/2,��������sum* 226/355;
 *             ->sample[m]*TRIG_sin(angle)*226 /angle -- sample[m]*sin(angle)/angle
 *   author : lkh     date : 10/10/2011
 */
void dsp_sincinterp(I16 sample[],  // ����ֵ����
				    U16 sampleN,  // ����ֵ���ݵ���
				    //I16 Interp[],  // ��ֵ������
				    I16 interpN)   // ��ֵ�����ݵ���
{
	I16 i,m;
	I16 factor= interpN / (sampleN-1);  // ������(sampleN-1)Ӧ�ñ�interpN����ʱ����ȷ
	int angle,sum;
	I16 *_sample = (I16*)malloc(sampleN*sizeof(I16));

	memcpy(_sample, sample, sampleN*sizeof(I16));

	for(i=0; i<interpN; i++) {
		sum = 0;
		for(m=0; m<sampleN; m++) {
			angle = (m<<11) - (i<<11) / factor;  // angle = pi*(m-i*factor) * (2048/pi) 
			sum += (angle==0)? _sample[m]*355 : _sample[m]*TRIG_sin(angle)*226 /angle;
		}	                                     
		sample[i] = sum / 355;  // sum�ٳ���pi/2����Ϊ���Ҳ��ǰ���Ŵ���pi/2 * 1024 ->... 
	}                              // ...-> ����TRIG_sin(angle) /angle�Ѿ�������(*1024)
}
/*  ����ԭ�� OK
#include <math.h>
void dsp_sincinterp(I16 sample[],int sampleN, I16 Interp[], int interpN) {
	int i,m;
	float angle,sum;
	int factor= interpN / (sampleN-1);

	for(i=0; i<interpN; i++) {
		sum = 0.0;
		for(m=0; m<sampleN; m++) {
			angle = pi*(m-i/(float)factor);
			if(angle == 0)
				sum += sample[m];
			else
				sum += sin(angle) * sample[m] / angle;
		}
		Interp[i] = sum;
	}
}*/

/*********************************************************
 *          ��������(����)��ֵ[�׳�����������ֵ]
 *   ��������һ��16λ���κ���ֵ������ֵ�� t ���Ľ���ֵ
 *   author : lkh     date : 10/13/2011
 */
I16 dsp_lagrinterp(int n,        // �������ĸ���
					  I16 t,      // ָ����ֵ���ֵ
					  I16 x[],    // ��Ÿ��� n ������ֵ(��С����)
					  I16 y[])    // ��Ÿ��� n ������ϵĺ���ֵ
{
	int i,j,k,m;
	I16 z=0,s;
	if(n < 1)   /* ���������ԣ����� */
		return 0;
	if(n == 1)  /* ֻ��һ����㣬ȡֵ���� */
		return y[0];
	if(n == 2)  /* ֻ�������ڵ㣬�������Բ�ֵ�󷵻� */
		return (y[0] * (t-x[1]) - y[1] * (t-x[0])) / (x[0]-x[1]);
	if(t <= x[1]) {  /* ȡ��ǰ��������� */
		k=0; m=2;
	} else if(t >= x[n-2]) {  /* ȡ�м�������ڵ� */
		k= n-3; m= n-1; 
	} else {
		k=1; m=n;
		while((m-k) != 1) {
			i= (k+m) / 2;
			if(t < x[i-1])
				m=i;
			else
				k=i;
		}
		k--; m--;
		if(abs(t-x[k]) < abs(t-x[m]))
			k--;
		else
			m++;
	}
	z= 0;
	for(i=k; i<=m; i++) {  /* ����������β�ֵ */
		s= 1;
		for(j=k; j<=m; j++) {
			if(j != i)
				s *= (t-x[j]) / (x[i]-x[j]);
			z += s*y[i];
		}
	}
	return z;
}

/*********************************************************
 *                    �����ز�ֵ��
 *   ��������һ��˫����ʵ�ͺ���ֵ������ֵ�� t ���ĺ�������ֵ
 *   author : xxx     date : 10/13/2011
 */
float HermiteInterp(int n,       // �������ĸ���
				 	float t,     // ָ����ֵ���ֵ
				 	float x[],   // ��Ÿ��� n ������ֵ(��С����)
				 	float y[],   // ��Ÿ��� n ������ϵĺ���ֵ
				 	float dy[])  // ��Ÿ��� n ������ϵ�һ�׵���ֵ
{
	int i,j;
	float p,q,s,z;
	
	z = 0.0;
	for(i=1; i<=n; i++)
	{
		s = 1.0;
		for(j=1; j<=n; j++)
			if(j != i) 
				s = s * (t - x[j-1]) / (x[i-1] - x[j-1]);
			s = s * s;
			p = 0.0;
			for(j=1; j<=n; j++)
				if(j != i) p = p + 1.0 / (x[i-1] - x[j-1]);
				q = y[i-1] + (t - x[i-1]) * (dy[i-1] - 2.0 * y[i-1] * p);
				z = z + q * s;          /* �����ۼ� */
				
	}
	
	return (z);
	
}

/*********************************************************
 *           ���Ҳ�ֵ���Ժ���
 */
#include "wave.h"
#include "dso_confDefaults.h"

void dsp_sincinterp_test(WAVE_INFO *info) {
	CHANNEL_DATA *ch = info->ch->action;

	dsp_sincinterp(ch->sample,ch->sampleN,WAVEWIN_XSIZE);
	ch->sampleN = WAVEWIN_XSIZE;
	
	GUI_SetColor(GUI_RED);
	wave_display(ch->sample,WAVEWIN_XSIZE, 1);

}
/*********************************************************
 *           �����ز�ֵ�����Ժ���
 */

void dsp_hermiteinterp_test(void) {


}