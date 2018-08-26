#ifndef WAVE_H_
#define WAVE_H_

#include "dso_type.h"


/***************************************************************
 *                     defined
 */
#define VoltRef           (3.3)    /* A/D�ο���ѹ (��λ : ����) */
#define DATAMAX           (255)    /* 8λAD���� */
#define _1DIVDATAMAX      (1.0 / (DATAMAX+1))   /* 8λAD�������ֵ�ĵ��� (Ϊ���ټ���׼��) */

/***************************************************************
 *
 *                     public code
 */
/************************************************************
 *
 *                     init
 */
void wave_init(WAVE_INFO *info);
/*****************************************************************
 *                       wave for channel
 */
int  channel_register(CHANNEL_INFO *info,U8 id);
int  channel_undo(CHANNEL_INFO *info,U8 id);
void channel_selectAction(CHANNEL_INFO *info,U8 id);
int  channel_select(CHANNEL_INFO *info,U8 id);
/************************************************************
 *
 *                   
 */
void wave_getCHxBaseInfo(WAVEBASE_INFO *pInfo);
void wave_getCHxData(CHANNEL_INFO *info,U8 id);

/***************************************************************
 *                   ������������
 */
void wave_initBk(WAVE_INFO *info);
int  wave_setNetAndGrid(WAVE_INFO *info,U8 rate);
void wave_setColorToDefault(WAVE_INFO *info);
void wave_setReserveCnt(WAVE_INFO *info,I8 cnt);
void wave_setDefaultCnt(WAVE_INFO *info);
void wave_display(t_ad *data, int size,int xStep);
void wave_fresh(void);

/*****************************************************************
 *                   ���δ�����߿����[�ػ�]����
 */
void wave_expFrameTop(int y0, int x0, int x1);
void wave_expFrameBottom(int y0, int x0, int x1);
void wave_expFrame(void);

/*****************************************************************
 *                       wave for vpo
 */


/*****************************************************************
 *                     wave task
 */
void wave_task(WAVE_INFO *info);




#endif /*WAVE_H_*/
