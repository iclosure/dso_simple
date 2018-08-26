
#include "wave.h"
#include <math.h>
#include <stdlib.h>


/********************************************************
*          Name : wave_getCHxBaseInfo
*      Function : 获取指定通道的基本信息.
*        Inputs : pInfo-- .
*        Output : None.
*   Description : None.
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/02/25
********************************************************/
void wave_getCHxBaseInfo(WAVEBASE_INFO *info)
{
    /* 获取FPGA采集的波形的基本信息 */
	info->Period = 1.0;   /* 周期(单位 : s)  */
	info->Vmax   = 5.0;   /* 最大电平 (波形显示的最高值。)(单位 : V) */
	info->Vmin   = 0.0;   /* 最小电平 (波形显示的最低值。)(单位 : V) */
    
	/* 获取示波器当前测量用的基本信息 */
	info->hSens = 1.0;    /* 示波器界面水平灵敏度 */
	info->vSens = 1.0;    /* 示波器界面垂直灵敏度 */
	/*...*/
}

/********************************************************
*          Name : wave_getCHxData
*      Function : 获取指定通道,指定长度的采样数据
*        Inputs : info-- ; id-- .
*        Output : None.
*   Description : None.
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/02/25
********************************************************/
#define RAND()	rand()
void wave_getCHxData(CHANNEL_INFO *info,U8 id) {

	/**
	 ** Example **
	 **/
	int i;
	double t=0.0;
	double Nt = 4;        
	double pi = 3.141592635;
	double f0 = 1024.0;
	double fs = ((info->ch[id].sampleN-1) * f0 / Nt);

	for(i=0; i<info->ch[id].sampleN; i++, t+=1.0/fs) {
		switch(id) {
		case 0: info->ch[id].sample[i] = (t_ad) (( 50+50*sin(1.*pi*f0*(t+RAND()%1000)) + RAND()%5)); break;
		case 1: info->ch[id].sample[i] = (t_ad) ((150+50*sin(2.*pi*f0*(t+RAND()%1000)) + RAND()%5)); break;
		case 2: info->ch[id].sample[i] = (t_ad) ((300+50*sin(3.*pi*f0*(t+RAND()%1000)) + RAND()%5)); break;
		case 3: info->ch[id].sample[i] = (t_ad) ((350+50*sin(4.*pi*f0*(t+RAND()%1000)) + RAND()%5)); break;
		default: break;
		}
	}
}
