
/*
 * ***************************************************
 *                  ���Z    �W �X�T�T�[ �i �X�T�T�Y��
 *                  ���^�T�T�a �`    �] �l �^�T�T�_��
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     (c) Copyright 2011, Unic Inc., China, Sc
 *     (c) Copyright 2011, SEGGER Microcontroller Systeme GmbH
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may ont be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--H-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : target.h
 Purpose     : hardware target define file.
   ----------------------------------------------------------------------
 */

#ifndef TARGET_H_
#define TARGET_H_


#include "integer.h"


// �����������ϵͳ[��ѡһ]
#if defined(WIN32)
	#define OS_UCOS
#endif

// ����ϵͳͷ�ļ�
#if defined(OS_UCOS)  /*uCOS System*/

#include "ucos_ii.h"
#include "SystemConfig.h"

#else                 /*Linux System*/

#include <unistd.h>   
#include <sys/time.h>
#include <pthread.h>
#endif


/**************************************************************
 *
 *
 */
void delay_us(U32 n);  // ΢����ʱ����
void delay_ms(U32 n);  // ������ʱ����
void NOP(void);





#endif /*TARGET_H_*/
