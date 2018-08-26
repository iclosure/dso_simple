

#include "meas.h"
#include "wave.h"
#include "dsp.h"
#include <math.h>  // use sqrt()

/*************************************************************
 * 
 *                     static code
 */

/* Vmin (��С��ƽ) */
static void _calc_min(MEASURE_INFO *info) { info->param.i.v.min= CONVTO_VOLT(info->parent->sample[0]); }
/* Vmax (����ƽ) */
static void _calc_max(MEASURE_INFO *info) { info->param.i.v.max= CONVTO_VOLT(info->parent->sample[info->parent->sampleN-1]); }
/* VPP (��-��ֵ) */
static void _calc_pk_pk(MEASURE_INFO *info) { info->param.i.v.pk_pk= info->param.i.v.max-info->param.i.v.min; }
/* top/base (��/��ֵ) */
static void _calc_top_base (MEASURE_INFO *info) {
    I16 top,base;
	float mid= CONVTO_VOLT(info->parent->sort[0] + info->parent->sort[info->parent->sampleN-1]) / 2.0;  /* ��λֵ */;
    /* ����ֱ��ͼʽͳ�Ʒ�Ѱ�� ��ѹ��ֵ �� ��ѹ��ֵ */
    dsp_mostnum(info->parent->sort, info->parent->sampleN, mid, &top,&base);
    info->param.i.v.top  = CONVTO_VOLT(top);  /* ��ѹ��ֵ */
    info->param.i.v.base = CONVTO_VOLT(base);  /* ��ѹ��ֵ */
}
/* Amplitude (����) */
static void _calc_amplitude(MEASURE_INFO *info) { info->param.i.v.amplitude= info->param.i.v.top - info->param.i.v.base; }
/* RiseOvershoot (��ѹ�����ع��� (��λ: �ٷֱ�)) */
static void _calc_overShoot(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	if(v->max > v->top) {
		v->overShoot= (v->max - v->top) * 100 / v->amplitude;
	} else {
		v->overShoot= 0.0;
	}
}
/* FallOvershoot (��ѹ�½��ع��� (��λ: �ٷֱ�)) */
static void _calc_preShoot(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	if(v->min < v->base) {
		v->preShoot= (v->base - v->min) * 100 / v->amplitude;
	} else {
		v->preShoot= 0.0;
	}
}
/* Mean (ƽ��ֵ) */
static void _calc_average_FS(MEASURE_INFO *info) { 
	int i=info->parent->sampleN;
    I32 sum=0;
    while(i--)
		sum += info->parent->sample[i];
	info->param.i.v.average_FS= (CONVTO_VOLT(sum) / info->parent->sampleN);
}
/* DCrms ((һ���������������ϲ��ε�)������ֵ) */
static void _calc_DCrms_FS(MEASURE_INFO *info) { 
    int i=info->parent->sampleN;
	MEASVOLT_DATA *v=&info->param.i.v;
    v->DCrms_FS=0;
    while(i--)
        v->DCrms_FS += CONVTO_VOLT(info->parent->sample[i] * info->parent->sample[i]);
    v->DCrms_FS = sqrt(v->DCrms_FS / info->parent->sampleN);
}
/* ACrms (�Ƴ��� DC �����Ĳ��εľ�����) */
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
/* Mean and DCrms ((ͬʱ����)ƽ��ֵ��ֱ���ɷֵľ�����(ʡʱ)) */
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
/* �����ѹ��ֵ��Ϣ */
static void _calc_threshold(MEASURE_INFO *info) {
	MEASVOLT_DATA *v=&info->param.i.v;
	info->vt.per_10 = v->base + (v->top - v->base) * 0.1;  /* 10%��ѹ */    
	info->vt.per_50 = v->base + (v->top - v->base) * 0.5;  /* 50%��ѹ */
	info->vt.per_90 = v->base + (v->top - v->base) * 0.9;  /* 90%��ѹ */
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
    _calc_min(info)				;  /* ��С��ƽ */
    _calc_max(info)				;  /* ����ƽ */
    _calc_pk_pk(info)			;  /* ��-��ֵ */
	_calc_top_base(info)		;  /* ��/��ֵ */
	_calc_amplitude(info)		;  /* ���� */
	_calc_overShoot(info)		;  /* ��ѹ�����ع��� */
	_calc_preShoot(info)		;  /* ��ѹ�½��ع��� */
	_calc_average_DCrms_FS(info);  /* ƽ��ֵ��ֱ�������� */
    _calc_ACrms_FS(info)		;  /* ����������*/ 
	_calc_threshold(info)		;  /* �����ѹ��ֵ��Ϣ */
}
