
#include "meas.h"
#include "wave.h"
#include "dsp.h"
#include <math.h>  // use sqrt()
#include <string.h>

/*************************************************************
 * 
 *                     static code
 */

/********************************************************
*          Name : _calc_pulseWidth
*      Function : 计算从X光标位置开始的一个周期内的正脉宽和负脉宽.
*        Inputs : *pCHxData-- ;
*                 *pPn -- X光标显示当前的波形正脉宽点数(第一个50%电压到第二个50%电压之间的点数);
*                 *pNn -- X光标显示当前的波形负脉宽点数(第二个50%电压到第三个50%电压之间的点数);
*                 *pBn -- X光标显示当前的波形猝发脉宽点数(第一个50%电压到最后一个50%电压之间的点数).
*        Output : true or false;
*   Description : >通过找到X光标开始之后的连续三个50%电压点,
*                  如果存在的话, 就可以测得当前X光标现实的波形周期.
*                 >返回值以点数表示.
*                 >上升沿触发.
********************************************************/
static int _calc_pulseWidth(MEASURE_INFO *info,U16 *pPn, U16 *pNn, U16 *pBn) {
    U16 temp= 0;
    U16 period;  /* 以点数表示的波形周期 */
    U16 i= info->parent->hcursor.x;  /* 周期点数计数变量 */
    /* 等待第一个上升沿到, 且刚好大等于 50%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_50) { /* 如果一开始的电压就大于50%电压 */
        temp++;
        if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效脉宽 */
            return -1; /* 错误返回 */
    }
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) {
        temp++;
        if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效脉宽 */
            return -1; /* 错误返回 */
    }
    /* 等待第一个下降沿到, 且刚好低于 50%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) >= info->vt.per_50) {
        (*pPn)++;
        if(++i == info->parent->sampleN) { /* 如果点数溢出, 则返回无效正脉宽 */
            *pPn = 0; 
            return -1; /* 错误返回 */
        }
    }
    /* 等待第二个上升沿到, 且刚好大等于 50%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) {
        (*pNn)++;
        if(++i == info->parent->sampleN) {  /* 如果点数溢出, 则返回无效脉宽 */   
            *pPn = 0; 
            *pNn = 0; 
            return -1; /* 错误返回 */
        }
    }
    period = *pPn + *pNn;
    *pBn = i - info->parent->hcursor.x - temp;
    /* 等待最后一个上升沿到, 且刚好大等于 50%电压 */
    for( ; i<info->parent->sampleN; i++) { /* 如果点数溢出, 则返回无效脉宽 */ 
        while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) { // 判断上升沿
            if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效脉宽0.0 */   
                return 0; /* 正确返回 */
        }
        *pBn += period;
    }
    return 0;   /* 正确返回 */
}
/********************************************************
*          Name : _calc_edge
*      Function : 计算从X光标位置开始的一个周期内的上升时间和下降时间.
*        Inputs : *pRn -- X光标显示当前的波形上升时间点数;
*                 *pFn -- X光标显示当前的波形下降时间点数;
*       Outputs : true or false;
*   Description : >上升时间为上升沿上的10%电压点和90%电压点间的时间差. 
*                  求上升时间的关键变成了求上升沿, 为了简化算法,首先求波形的低值
*                  首次出现的位置, 从该点出发的第一个沿肯定是上升沿, 由此位置为起点求10%
*                  和90%电压点, 则求得上升时间.
*                 >返回值以点数表示.
*                 >上升沿触发.
********************************************************/
static int _calc_edge(MEASURE_INFO *info,U16 *pRn, U16 *pFn) {
    U16 i= info->parent->hcursor.x;    /* 周期点数计数变量 */
    /* 等待下一个上升沿到, 且刚好大等于 10%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_10) {  /* 如果一开始的电压就大于10%电压 */
        if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效脉宽 */
            return -1; /* 错误返回 */
    }
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_10) {
        if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效脉宽 */
            return -1; /* 错误返回 */
    }
    /* 等待下一个上升沿的90%电压到, 且刚好大等于90%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_90) {
        (*pRn)++;
        if(++i == info->parent->sampleN) { /* 如果点数溢出, 则返回无效正脉宽 */   
            *pRn = 0; 
            return -1; /* 错误返回 */
        }
    }
    /* 等待下一个下降沿的90%电压到, 且刚好低于90%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_90) {
        if(++i == info->parent->sampleN)  /* 如果点数溢出, 则返回无效正脉宽 */   
            return -1; /* 错误返回 */
    }
    /* 等待下一个下降沿的10%电压到, 且刚好大于10%电压 */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_10) {
        (*pFn)++;
        if(++i == info->parent->sampleN) { /* 如果点数溢出, 则返回无效正脉宽 */   
            *pFn = 0; 
            return -1; /* 错误返回 */
        }
    }
    return 0;  /* 正确返回 */
}

/* 周期 */
static void _calc_period(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.period= info->parent->hcursor.sens * (Pn+Nn); }
/* 频率 */
static void _calc_freq(MEASURE_INFO *info) { info->param.i.t.freq= 1.0 / info->param.i.t.period; }
/* 正脉宽 */
static void _calc_posWidth(MEASURE_INFO *info, U16 Pn) { info->param.i.t.posWidth= info->parent->hcursor.sens * Pn; }
/* 负脉宽 */
static void _calc_negWidth(MEASURE_INFO *info, U16 Nn) { info->param.i.t.negWidth= info->parent->hcursor.sens * Nn; }
/* 猝发宽度 */
static void _calc_burstWidth(MEASURE_INFO *info, U16 Bn) { info->param.i.t.burstWidth= info->parent->hcursor.sens * Bn; }
/* 正占空比 */
static void _calc_posDutyCycle(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.posDutyCycle= Pn*100.0 / (Pn+Nn); }
/* 负占空比 */
static void _calc_negDutyCycle(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.negDutyCycle= Nn*100.0 / (Pn+Nn); }
/* 上升时间 */
static void _calc_riseEdge(MEASURE_INFO *info, U16 Rn) { info->param.i.t.riseEdge= info->parent->hcursor.sens * Rn; }
/* 下降时间 */
static void _calc_fallEdge(MEASURE_INFO *info, U16 Fn) { info->param.i.t.fallEdge= info->parent->hcursor.sens * Fn; }

/*************************************************************
 * 
 *                     public code
 */

/*************************************************************
 *
 *            The Measurement of Time.
 */
int meas_timeInfo(MEASURE_INFO *info) {
	
    U16 Pn=0,Nn=0,Bn=0,Rn=0,Fn=0;
	
    /* 计算从X光标位置开始的一个周期内的正脉宽和负脉宽, 返回值以点数表示 */
    if(_calc_pulseWidth(info,&Pn,&Rn,&Bn) < 0) {
		//memset(info->param.i.t, 0, sizeof(MEAS_TIME_DATA));
		return 1;
	}
	_calc_period(info, Pn,Rn)		;  /* 周期 */
	_calc_freq(info)				;  /* 频率 */
	_calc_posWidth(info, Pn)		;  /* 正脉宽 */
	_calc_negWidth(info, Nn)		;  /* 负脉宽 */
	_calc_burstWidth(info, Bn)		;  /* 猝发宽度 */ 
	_calc_posDutyCycle(info, Pn,Nn)	;  /* 正占空比 */
	_calc_negDutyCycle(info, Pn,Nn)	;  /* 负占空比 */

	/* 计算从X光标位置开始的一个周期内的上升时间和下降时间, 返回值以点数表示 */
    if(_calc_edge(info, &Rn,&Fn) < 0) {
		// 
		return 2;
	}  
	_calc_riseEdge(info,Rn)			;  /* 上升时间 */
	_calc_fallEdge(info,Fn)			;  /* 下降时间 */

	return 0;
}
