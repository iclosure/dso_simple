
/*
 * ***************************************************
 *                  ���Z  �W �X�T�T�[ �i �X�T�T�Y��
 *                  ���^�T�T�a �`  �] �l �^�T�T�_��
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
#define SQRT_2        (1.414213197969543)   /* 2��ƽ���� */
#define _1DIVSQRT_2   (0.707106963388370)   /* 2��ƽ�����ĵ��� */
#endif /* SQRT_2 */

/* ����Ҷ�任����,�������� */
#define FFTN(M)     (1L<<(M))

/************************************************************
 *                    FFT & IFFT
 */
void dsp_fft0(I16 data[], I8 m);
void dsp_fft (int x[], I8 m, I8 flag);  // ����ʵ���еĻ������ٸ���Ҷ�任.
void dsp_ifft(int x[], I8 m);           // ���㹲��Գ�ʵ���еĻ������ٸ���Ҷ���任����任�����ʵ��.

/************************************************************
 *                    ���پ��
 */
void dsp_fastconv(int x[], I8 m, int y[], I16 n, I16 r);

/************************************************************
 *                    FIR�˲�
 */
void dsp_fir(int data[], I16 m);

/************************************************************
 *                    ��ֵ����
 */
void  dsp_sincinterp(I16 sample[],U16 sampleN,/* I16 Interp[],*/I16 InterpN);  // �����ڲ庯��
I16 dsp_lagrinterp(int n, I16 t, I16 x[], I16 y[]);

/************************************************************
 *                    ����������[���Կ⺯��]
 */
// �ɱ����͵ıȽϺ���
int dsp_compareup(const void *_key , const void *_base);    // ��������
int dsp_comparedown(const void *_key , const void *_base);  // ��������
// �¶���Ŀɱ����͵�������(Ĭ��Ϊ��������)
#define dsp_qsort(base, n)      qsort(base,n,sizeof(I16), dsp_compareup);
#define dsp_qsortup(base, n)    qsort(base,n,sizeof(I16), dsp_compareup);
#define dsp_qsortdown(base, n)  qsort(base,n,sizeof(I16), dsp_comparedown);
// Shell sort [ϣ������] 
void shellsort(char *item, int count);

// Ѱ��һ�����������е�����[��С�������������]
void dsp_mostnum(I16 data[], int n, float mid, I16 *pLarge, I16 *pSmall);


/************************************************************
 *                    ���Ժ���
 */
void dsp_fft_test(void);
void dsp_sincinterp_test(WAVE_INFO *info);




#endif /* DSP_H_ */
