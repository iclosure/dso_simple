
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
 File        : dsp.h
 Purpose     : DSO math file.
   ----------------------------------------------------------------------
 */

#ifndef DSP_H_
#define DSP_H_

#include "LCD.h"
#include "dso_type.h"
#include <math.h>
#include <stdlib.h>

/************************************************************
 *                 
 *                       defined
 */
#ifndef PI 
#define PI  3.1415926535897932  // (pi ?= 355/113)
#endif /* #ifndef PI  */

#ifndef SQRT
#define SQRT  
#define SQRT_2        (1.414213197969543)   /* 2的平方根 */
#define _1DIVSQRT_2   (0.707106963388370)   /* 2的平方根的倒数 */
#endif /* SQRT_2 */

/* 傅里叶变换算子,点数索引 */
#define FFTN(M)     (1L<<(M))

/************************************************************
 *                    FFT & IFFT
 */
void dsp_fft0(I16 data[], I8 m);
void dsp_fft (int x[], I8 m, I8 flag);  // 计算实序列的基二快速傅里叶变换.
void dsp_ifft(int x[], I8 m);           // 计算共轭对称实序列的基二快速傅里叶反变换，其变换结果是实数.

/************************************************************
 *                    快速卷积
 */
void dsp_fastconv(int x[], I8 m, int y[], I16 n, I16 r);

/************************************************************
 *                    FIR滤波
 */
void dsp_fir(int data[], I16 m);

/************************************************************
 *                    插值函数
 */
void  dsp_sincinterp(I16 sample[],U16 sampleN,/* I16 Interp[],*/I16 InterpN);  // 正弦内插函数
I16 dsp_lagrinterp(int n, I16 t, I16 x[], I16 y[]);

/************************************************************
 *                    快速排序函数[引自库函数]
 */
// 可变类型的比较函数
int dsp_compareup(const void *_key , const void *_base);    // 升序排序
int dsp_comparedown(const void *_key , const void *_base);  // 降序排序
// 新定义的可变类型的排序函数(默认为升序排序)
#define dsp_qsort(base, n)      qsort(base,n,sizeof(I16), dsp_compareup);
#define dsp_qsortup(base, n)    qsort(base,n,sizeof(I16), dsp_compareup);
#define dsp_qsortdown(base, n)  qsort(base,n,sizeof(I16), dsp_comparedown);
// Shell sort [希尔排序] 
void shellsort(char *item, int count);

// 寻找一个升序数组中的众数[最小众数和最大众数]
void dsp_mostnum(I16 data[], int n, float mid, I16 *pLarge, I16 *pSmall);


/************************************************************
 *                    测试函数
 */
void dsp_fft_test(void);
void dsp_sincinterp_test(WAVE_INFO *info);




#endif /* DSP_H_ */
