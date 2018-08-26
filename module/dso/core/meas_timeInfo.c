
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
*      Function : �����X���λ�ÿ�ʼ��һ�������ڵ�������͸�����.
*        Inputs : *pCHxData-- ;
*                 *pPn -- X�����ʾ��ǰ�Ĳ������������(��һ��50%��ѹ���ڶ���50%��ѹ֮��ĵ���);
*                 *pNn -- X�����ʾ��ǰ�Ĳ��θ��������(�ڶ���50%��ѹ��������50%��ѹ֮��ĵ���);
*                 *pBn -- X�����ʾ��ǰ�Ĳ���⧷��������(��һ��50%��ѹ�����һ��50%��ѹ֮��ĵ���).
*        Output : true or false;
*   Description : >ͨ���ҵ�X��꿪ʼ֮�����������50%��ѹ��,
*                  ������ڵĻ�, �Ϳ��Բ�õ�ǰX�����ʵ�Ĳ�������.
*                 >����ֵ�Ե�����ʾ.
*                 >�����ش���.
********************************************************/
static int _calc_pulseWidth(MEASURE_INFO *info,U16 *pPn, U16 *pNn, U16 *pBn) {
    U16 temp= 0;
    U16 period;  /* �Ե�����ʾ�Ĳ������� */
    U16 i= info->parent->hcursor.x;  /* ���ڵ����������� */
    /* �ȴ���һ�������ص�, �Ҹպô���� 50%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_50) { /* ���һ��ʼ�ĵ�ѹ�ʹ���50%��ѹ */
        temp++;
        if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч���� */
            return -1; /* ���󷵻� */
    }
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) {
        temp++;
        if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч���� */
            return -1; /* ���󷵻� */
    }
    /* �ȴ���һ���½��ص�, �Ҹպõ��� 50%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) >= info->vt.per_50) {
        (*pPn)++;
        if(++i == info->parent->sampleN) { /* ����������, �򷵻���Ч������ */
            *pPn = 0; 
            return -1; /* ���󷵻� */
        }
    }
    /* �ȴ��ڶ��������ص�, �Ҹպô���� 50%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) {
        (*pNn)++;
        if(++i == info->parent->sampleN) {  /* ����������, �򷵻���Ч���� */   
            *pPn = 0; 
            *pNn = 0; 
            return -1; /* ���󷵻� */
        }
    }
    period = *pPn + *pNn;
    *pBn = i - info->parent->hcursor.x - temp;
    /* �ȴ����һ�������ص�, �Ҹպô���� 50%��ѹ */
    for( ; i<info->parent->sampleN; i++) { /* ����������, �򷵻���Ч���� */ 
        while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_50) { // �ж�������
            if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч����0.0 */   
                return 0; /* ��ȷ���� */
        }
        *pBn += period;
    }
    return 0;   /* ��ȷ���� */
}
/********************************************************
*          Name : _calc_edge
*      Function : �����X���λ�ÿ�ʼ��һ�������ڵ�����ʱ����½�ʱ��.
*        Inputs : *pRn -- X�����ʾ��ǰ�Ĳ�������ʱ�����;
*                 *pFn -- X�����ʾ��ǰ�Ĳ����½�ʱ�����;
*       Outputs : true or false;
*   Description : >����ʱ��Ϊ�������ϵ�10%��ѹ���90%��ѹ����ʱ���. 
*                  ������ʱ��Ĺؼ��������������, Ϊ�˼��㷨,�������εĵ�ֵ
*                  �״γ��ֵ�λ��, �Ӹõ�����ĵ�һ���ؿ϶���������, �ɴ�λ��Ϊ�����10%
*                  ��90%��ѹ��, ���������ʱ��.
*                 >����ֵ�Ե�����ʾ.
*                 >�����ش���.
********************************************************/
static int _calc_edge(MEASURE_INFO *info,U16 *pRn, U16 *pFn) {
    U16 i= info->parent->hcursor.x;    /* ���ڵ����������� */
    /* �ȴ���һ�������ص�, �Ҹպô���� 10%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_10) {  /* ���һ��ʼ�ĵ�ѹ�ʹ���10%��ѹ */
        if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч���� */
            return -1; /* ���󷵻� */
    }
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_10) {
        if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч���� */
            return -1; /* ���󷵻� */
    }
    /* �ȴ���һ�������ص�90%��ѹ��, �Ҹպô����90%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) < info->vt.per_90) {
        (*pRn)++;
        if(++i == info->parent->sampleN) { /* ����������, �򷵻���Ч������ */   
            *pRn = 0; 
            return -1; /* ���󷵻� */
        }
    }
    /* �ȴ���һ���½��ص�90%��ѹ��, �Ҹպõ���90%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_90) {
        if(++i == info->parent->sampleN)  /* ����������, �򷵻���Ч������ */   
            return -1; /* ���󷵻� */
    }
    /* �ȴ���һ���½��ص�10%��ѹ��, �Ҹպô���10%��ѹ */
    while(CONVTO_VOLT(info->parent->sample[i]) > info->vt.per_10) {
        (*pFn)++;
        if(++i == info->parent->sampleN) { /* ����������, �򷵻���Ч������ */   
            *pFn = 0; 
            return -1; /* ���󷵻� */
        }
    }
    return 0;  /* ��ȷ���� */
}

/* ���� */
static void _calc_period(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.period= info->parent->hcursor.sens * (Pn+Nn); }
/* Ƶ�� */
static void _calc_freq(MEASURE_INFO *info) { info->param.i.t.freq= 1.0 / info->param.i.t.period; }
/* ������ */
static void _calc_posWidth(MEASURE_INFO *info, U16 Pn) { info->param.i.t.posWidth= info->parent->hcursor.sens * Pn; }
/* ������ */
static void _calc_negWidth(MEASURE_INFO *info, U16 Nn) { info->param.i.t.negWidth= info->parent->hcursor.sens * Nn; }
/* ⧷���� */
static void _calc_burstWidth(MEASURE_INFO *info, U16 Bn) { info->param.i.t.burstWidth= info->parent->hcursor.sens * Bn; }
/* ��ռ�ձ� */
static void _calc_posDutyCycle(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.posDutyCycle= Pn*100.0 / (Pn+Nn); }
/* ��ռ�ձ� */
static void _calc_negDutyCycle(MEASURE_INFO *info, U16 Pn, U16 Nn) { info->param.i.t.negDutyCycle= Nn*100.0 / (Pn+Nn); }
/* ����ʱ�� */
static void _calc_riseEdge(MEASURE_INFO *info, U16 Rn) { info->param.i.t.riseEdge= info->parent->hcursor.sens * Rn; }
/* �½�ʱ�� */
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
	
    /* �����X���λ�ÿ�ʼ��һ�������ڵ�������͸�����, ����ֵ�Ե�����ʾ */
    if(_calc_pulseWidth(info,&Pn,&Rn,&Bn) < 0) {
		//memset(info->param.i.t, 0, sizeof(MEAS_TIME_DATA));
		return 1;
	}
	_calc_period(info, Pn,Rn)		;  /* ���� */
	_calc_freq(info)				;  /* Ƶ�� */
	_calc_posWidth(info, Pn)		;  /* ������ */
	_calc_negWidth(info, Nn)		;  /* ������ */
	_calc_burstWidth(info, Bn)		;  /* ⧷���� */ 
	_calc_posDutyCycle(info, Pn,Nn)	;  /* ��ռ�ձ� */
	_calc_negDutyCycle(info, Pn,Nn)	;  /* ��ռ�ձ� */

	/* �����X���λ�ÿ�ʼ��һ�������ڵ�����ʱ����½�ʱ��, ����ֵ�Ե�����ʾ */
    if(_calc_edge(info, &Rn,&Fn) < 0) {
		// 
		return 2;
	}  
	_calc_riseEdge(info,Rn)			;  /* ����ʱ�� */
	_calc_fallEdge(info,Fn)			;  /* �½�ʱ�� */

	return 0;
}
