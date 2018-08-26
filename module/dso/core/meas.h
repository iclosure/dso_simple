
/*
 * ***************************************************
 *                  │╖  ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜  ╙ ╨ ╚══╛│
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     (c) Copyright 2011, Unic Inc., China, Sc
 *     (c) Copyright 2011, SEGGER Microcontroller Systeme GmbH
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may not be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--H-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : Measure.h
 Purpose     : DSO measure file.
   ----------------------------------------------------------------------
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#include "dso_type.h"


/***************************************************************
 *                     defined
 *
 */
#define CONVTO_VOLT(data)    ((data)*(VoltRef)/((float)DATAMAX))  /*将采集的数据转换为真实电压值[转换后的单位跟参考电压单位相同]*/

/***************************************************************
 *
 *                  测量相关全局变量
 */
// VOLTTHRESHOLD_DATA  CH1VoltThreshold,CH2VoltThreshold	;  /*波形特殊电压阈值信息*/
// MEASVOLT_DATA       CH1VoltInfo,CH2VoltInfo				;  /*电压参数信息*/
// MEASTIME_DATA       CH1TimeInfo,CH2TimeInfo				;  /*时间参数信息*/
// CHANNEL_INFO       *pCHxData							;  /*当前测量需要的通道数据[需要在用时申请空间,用后释放]*/

/***************************************************************
 *                   
 *
 */
void meas_preReady(MEASURE_INFO *data);
void meas_voltInfo(MEASURE_INFO *info);
int  meas_timeInfo(MEASURE_INFO *info);
void meas_init(WAVE_INFO *info);
/*****************************************************************
 *
 *                     meas task
 */
void meas_task(WAVE_INFO *info);




#endif /*MEASURE_H_*/
