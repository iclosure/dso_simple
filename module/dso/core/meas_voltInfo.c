

#include "meas.h"
#include "wave.h"
#include "dsp.h"
#include <math.h>  // use sqrt()

/*************************************************************
 * 
 *                     static code
 */

/* Vmin (最小电平) */
static void _calc_min(MEASURE_INFO *info) { info->param.i.v.min= CONVTO_VOLT(info->parent->sample[0]); }
/* Vmax (最大电平) */
static void _calc_max(MEASURE_INFO *info) { info->param.i.v.max= CONVTO_VOLT(info->parent->sample[info->parent->sampleN-1]); }
/* VPP (峰-峰值) */
static void _calc_pk_pk(MEASURE_INFO *info) { info->param.i.v.pk_pk= info->param.i.v.max-info->param.i.v.min; }
/* top/base (高/低值) */
static void _calc_top_base (MEASURE_INFO *info) {
    I16 top,base;
	float mid= CONVTO_VOLT(info->parent->sort[0] + info->parent->sort[info->parent->sampleN-1]) / 2.0;  /* 中位值 */;
    /* 采用直方图式统计法寻找 电压高值 和 电压低值 */
    dsp_mostnum(info->parent->sort, info->parent->sampleN, mid, &top,&base);
    info->param.i.v.top  = CONVTO_VOLT(top);  /* 电压低值 */
    info->param.i.v.base = CONVTO_VOLT(base);  /* 电压高值 */
}
/* Amplitude (幅度) */
static void _calc_amplitude(MEASURE_INFO *info) { info->param.i.v.amplitude= info->param.i.v.top - info->param.i.v.base; }
/* RiseOvershoot (电压上升沿过冲 (单位: 百分比)) */
static void _calc_overShoot(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	if(v->max > v->top) {
		v->overShoot= (v->max - v->top) * 100 / v->amplitude;
	} else {
		v->overShoot= 0.0;
	}
}
/* FallOvershoot (电压下降沿过冲 (单位: 百分比)) */
static void _calc_preShoot(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	if(v->min < v->base) {
		v->preShoot= (v->base - v->min) * 100 / v->amplitude;
	} else {
		v->preShoot= 0.0;
	}
}
/* Mean (平均值) */
static void _calc_average_FS(MEASURE_INFO *info) { 
	int i=info->parent->sampleN;
    I32 sum=0;
    while(i--)
		sum += info->parent->sample[i];
	info->param.i.v.average_FS= (CONVTO_VOLT(sum) / info->parent->sampleN);
}
/* DCrms ((一个或多个完整周期上波形的)均方根值) */
static void _calc_DCrms_FS(MEASURE_INFO *info) { 
    int i=info->parent->sampleN;
	MEASVOLT_DATA *v=&info->param.i.v;
    v->DCrms_FS=0;
    while(i--)
        v->DCrms_FS += CONVTO_VOLT(info->parent->sample[i] * info->parent->sample[i]);
    v->DCrms_FS = sqrt(v->DCrms_FS / info->parent->sampleN);
}
/* ACrms (移除了 DC 分量的波形的均方根) */
static void _calc_ACrms_FS(MEASURE_INFO *info) { 
    int i=info->parent->sampleN;
    float temp;
	MEASVOLT_DATA *v=&info->param.i.v;
    v->ACrms_FS = 0;
    while(i--) {
		temp = CONVTO_VOLT(info->parent->sample[i]) - v->average_FS;
        v->ACrms_FS += temp * temp;
    }
	
    info->param.i.v.ACrms_FS = sqrt(info->param.i.v.ACrms_FS  / info->parent->sampleN);
}
/* Mean and DCrms ((同时计算)平均值和直流成分的均方根(省时)) */
static void _calc_average_DCrms_FS(MEASURE_INFO *info) { 
    int i=info->parent->sampleN;
    I32 sum=0;
	MEASVOLT_DATA *v=&info->param.i.v;
	v->DCrms_FS = 0;
    while(i--) {
		sum += info->parent->sample[i];
        v->DCrms_FS += CONVTO_VOLT(info->parent->sample[i] * info->parent->sample[i]);
    }
	v->average_FS= CONVTO_VOLT(sum) / info->parent->sampleN;
	v->DCrms_FS = sqrt(v->DCrms_FS / info->parent->sampleN);
}
/* 特殊电压阈值信息 */
static void _calc_threshold(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	info->vt.per_10 = v->base + (v->top - v->base) * 0.1;  /* 10%电压 */    
	info->vt.per_50 = v->base + (v->top - v->base) * 0.5;  /* 50%电压 */
	info->vt.per_90 = v->base + (v->top - v->base) * 0.9;  /* 90%电压 */
}
/*************************************************************
 * 
 *                     public code
 */

/*************************************************************
 *
 *            The Measurement of Voltage.
 */
void meas_voltInfo(MEASURE_INFO *info) {
    _calc_min(info)				;  /* 最小电平 */
    _calc_max(info)				;  /* 最大电平 */
    _calc_pk_pk(info)			;  /* 峰-峰值 */
	_calc_top_base(info)		;  /* 高/低值 */
	_calc_amplitude(info)		;  /* 幅度 */
	_calc_overShoot(info)		;  /* 电压上升沿过冲 */
	_calc_preShoot(info)		;  /* 电压下降沿过冲 */
	_calc_average_DCrms_FS(info);  /* 平均值和直流均方根 */
    _calc_ACrms_FS(info)		;  /* 交流均方根*/ 
	_calc_threshold(info)		;  /* 特殊电压阈值信息 */
}
