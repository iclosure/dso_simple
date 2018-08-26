
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
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : dsp_conv.c
 Purpose     : FFT serial functions
   ----------------------------------------------------------------------
 */

#include "dsp.h"
#include "FilterCoeff.h"
#include "integer.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* == �������� == */

/********************************************************
*          Name : dsp_fastconv
*      Function : �û������ٸ���Ҷ�任�����������޳����е����Ծ��.
*        Inputs : x[] -- ˫����ʵ��һά���顣����Ϊlen����ʼʱ���ʵ����x(i),��������Ծ����ֵ��
*                 m   -- ���ͱ���������x(i)�ĳ��ȡ�
*                 y[] -- ˫����ʵ��һά���顣����Ϊn���������y(i)��
*                 n   -- ��������������y(i)�ĳ��ȡ�
*                 r -- ���ͱ��������Ծ���ĳ��ȡ�len >= m+n-1���ұ�����2���������ݣ���len=2^r��
*        Output : None.
*   Description : None.
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/03/06
********************************************************/
void dsp_fastconv(int x[], I8 m, int y[], I16 n, I16 r)
{
    unsigned int i, len, len2;
    int t;

    len = FFTN(r);
    
    memset(&x[m], 0x00, (len-m)*size_int);
    memset(&y[n], 0x00, (len-n)*size_int);
    
    dsp_fft(x, r, 0);
    dsp_fft(y, r, 0);
    
    len2 = len >> 1;
    x[0]    = x[0]*y[0] >>10;
    x[len2] = x[len2]*y[len2] >>10;
    for(i=1; i<len2; i++)
    {
        t = (x[i] * y[i] - x[len-i] * y[len-i]) >>10;
        x[len-i] = (x[i] * y[len-i] + x[len-i] * y[i]) >>10;
        x[i] = t;
    }

    dsp_ifft(x,r);
    
    // ���ھ������Ƶ�װ���[����λ],����Ϊ�˲���ϵ��������һ��[�ɶԳ��Կ���֪]
    memmove(x, &x[FIRorder>>1], (len-(FIRorder>>1))*size_int);
}


