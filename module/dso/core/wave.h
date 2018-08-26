#ifndef WAVE_H_
#define WAVE_H_

#include "dso_type.h"


/***************************************************************
 *                     defined
 */
#define VoltRef           (3.3)    /* A/D参考电压 (单位 : 伏特) */
#define DATAMAX           (255)    /* 8位AD采样 */
#define _1DIVDATAMAX      (1.0 / (DATAMAX+1))   /* 8位AD采样最大值的倒数 (为快速计算准备) */

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
 *                   波形区域处理函数
 */
void wave_initBk(WAVE_INFO *info);
int  wave_setNetAndGrid(WAVE_INFO *info,U8 rate);
void wave_setColorToDefault(WAVE_INFO *info);
void wave_setReserveCnt(WAVE_INFO *info,I8 cnt);
void wave_setDefaultCnt(WAVE_INFO *info);
void wave_display(t_ad *data, int size,int xStep);
void wave_fresh(void);

/*****************************************************************
 *                   波形窗口外边框绘制[重绘]函数
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
