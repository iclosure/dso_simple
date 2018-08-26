
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
 File        : MEAS_PreReady.c
 Purpose     : Ϊ����Ԥ����׼��[��ʼ����������ʱ��Ҫ������]
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
 *  ע�⣺�ڵ��ñ�����֮ǰ��Ҫ��֤CHxData�ѱ����£��Ҷ�Ӧͨ���Ĳ��λ�����Ϣ�Ѿ�������
 */
void meas_preReady(MEASURE_INFO *info) {
	// ��CHxData���ݿ�����info->sort
	memcpy(info->parent->sort, info->parent->sample, info->parent->sampleN*sizeof(t_ad));
	// ��������������������
	dsp_qsortup(info->parent->sort, info->parent->sampleN);
}


