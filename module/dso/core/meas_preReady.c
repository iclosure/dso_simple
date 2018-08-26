
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
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : MEAS_PreReady.c
 Purpose     : 为测量预先做准备[初始化测量计算时需要的数据]
   ----------------------------------------------------------------------
 */

#include "dsp.h"
#include "meas.h"
#include "wave.h"
#include <stdlib.h>
#include <string.h>

/***********************************************************************
 * 
 *                     static code
 */


/***********************************************************************
 * 
 *                  public code
 *  注意：在调用本函数之前，要保证CHxData已被更新，且对应通道的波形基本信息已经被更新
 */
void meas_preReady(MEASURE_INFO *info) {
	// 将CHxData数据拷贝到info->sort
	memcpy(info->parent->sort, info->parent->sample, info->parent->sampleN*sizeof(t_ad));
	// 将采样数据组升序重排
	dsp_qsortup(info->parent->sort, info->parent->sampleN);
}


