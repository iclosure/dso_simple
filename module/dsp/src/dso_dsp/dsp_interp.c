
#include "GUI_Protected.h"
#include "LCD.h"
#include "dsp.h"
#include <string.h>



/*********************************************************
 *                         正弦插值
 *
 *   函数说明：->I16 -- signed short;  TRIG_sin -- 定点正弦查表计算sin();
 *             ->所有计算过程全部为定点计算。
 *             ->只要满足 (SampleN-1)能被InterpN整除就能获得相当高的插值精确度。
 *             ->函数中的(<<11)是为了提高精确度而放大数据的。
 *             ->sample[m]*355 -- 355/226=?pi/2,补偿最后的sum* 226/355;
 *             ->sample[m]*TRIG_sin(angle)*226 /angle -- sample[m]*sin(angle)/angle
 *   author : lkh     date : 10/10/2011
 */
void dsp_sincinterp(I16 sample[],  // 待插值数据
				    U16 sampleN,  // 待插值数据点数
				    //I16 Interp[],  // 插值后数据
				    I16 interpN)   // 插值后数据点数
{
	I16 i,m;
	I16 factor= interpN / (sampleN-1);  // 理论上(sampleN-1)应该被interpN整除时结果最精确
	int angle,sum;
	I16 *_sample = (I16*)malloc(sampleN*sizeof(I16));

	memcpy(_sample, sample, sampleN*sizeof(I16));

	for(i=0; i<interpN; i++) {
		sum = 0;
		for(m=0; m<sampleN; m++) {
			angle = (m<<11) - (i<<11) / factor;  // angle = pi*(m-i*factor) * (2048/pi) 
			sum += (angle==0)? _sample[m]*355 : _sample[m]*TRIG_sin(angle)*226 /angle;
		}	                                     
		sample[i] = sum / 355;  // sum再除以pi/2是因为正弦查表前被放大了pi/2 * 1024 ->... 
	}                              // ...-> 而且TRIG_sin(angle) /angle已经抵消了(*1024)
}
/*  函数原型 OK
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
 *          拉格朗日(三点)插值[俗称三次样条插值]
 *   函数返回一个16位整形函数值，即插值点 t 处的近似值
 *   author : lkh     date : 10/13/2011
 */
I16 dsp_lagrinterp(int n,        // 给定结点的个数
					  I16 t,      // 指定插值点的值
					  I16 x[],    // 存放给定 n 个结点的值(从小到大)
					  I16 y[])    // 存放给定 n 个结点上的函数值
{
	int i,j,k,m;
	I16 z=0,s;
	if(n < 1)   /* 结点个数不对，返回 */
		return 0;
	if(n == 1)  /* 只有一个结点，取值返回 */
		return y[0];
	if(n == 2)  /* 只有两个节点，进行线性插值后返回 */
		return (y[0] * (t-x[1]) - y[1] * (t-x[0])) / (x[0]-x[1]);
	if(t <= x[1]) {  /* 取最前的三个结点 */
		k=0; m=2;
	} else if(t >= x[n-2]) {  /* 取中间的三个节点 */
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
	for(i=k; i<=m; i++) {  /* 进行三点二次插值 */
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
 *                    厄米特插值法
 *   函数返回一个双精度实型函数值，即插值点 t 处的函数近似值
 *   author : xxx     date : 10/13/2011
 */
float HermiteInterp(int n,       // 给定结点的个数
				 	float t,     // 指定插值点的值
				 	float x[],   // 存放给定 n 个结点的值(从小到大)
				 	float y[],   // 存放给定 n 个结点上的函数值
				 	float dy[])  // 存放给定 n 个结点上的一阶导数值
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
				z = z + q * s;          /* 进行累加 */
				
	}
	
	return (z);
	
}

/*********************************************************
 *           正弦插值测试函数
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
 *           厄米特插值法测试函数
 */

void dsp_hermiteinterp_test(void) {


}