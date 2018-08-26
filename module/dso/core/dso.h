
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
 File        : DSO.h
 Purpose     : DSO APP include file
   ----------------------------------------------------------------------
 */

#ifndef DSO_H_
#define DSO_H_

#include "dso_config.h"
#include "dso_paraConf.h"
#include "dso_confDefaults.h"
#include "dso_type.h"
#include "picture.h"
#include "color.h"


GUI_RECT		InfoBarArea	; /*��Ϣ��*/
GUI_RECT		SoftKeyArea	; /*���λ��ƴ���*/
GUI_RECT		WaveWinArea	; /*���λ��ƴ���*/

/******************************************************
 *   
 *                defined
 */
// 
#define BYTE_SET_BITS(base, data)         (base |= data)                   // [8λ]��λbitλ
#define BYTE_CLR_BITS(base, data)         (base &= (~(data)) & 0xFF)       // [8λ]���bitλ
#define WORD_SET_BITS(base, data)         (base |= data)                   // [16λ]��λbitλ
#define WORD_CLR_BITS(base, data)         (base &= (~(data)) & 0xFFFF)     // [16λ]���bitλ
#define DWORD_SET_BITS(base, data)        (base |= data)                   // [32λ]��λbitλ
#define DWORD_CLR_BITS(base, data)        (base &= (~(data)) & 0xFFFFFFFF) // [32λ]���bitλ

/******************************************************
 *   
 *               ����: ��ʾ�����ر�־����
 */
#define WIN_FLAG_DISP        (1)  // ��ʾ����
#define WIN_FLAG_HIDE        (2)  // ���ش���

/**************************************************************
 * 
 *          DSO_InitGUI [��ʼ��ʾ����������]
 * 
 */
void dso_reset(PROJECT_INFO *info);
void dso_init(PROJECT_INFO *info);
void dso_start(PROJECT_INFO *info);


/**************************************************************
 *
 *                  ��ͼ������غ���
 *
 */
void dso_drawSmallBarBk(GUI_RECT rect, U16 FillColor);
void dso_drawLargeBarBk(GUI_RECT rect, U16 FillColor);
void dso_drawTitleBar(const char *title, int y0,int x0,int x1);
void dso_drawFrame(GUI_RECT rect, U16 FillColor, const char *title);
void dso_drawSKSelRect(int x0,int y0, int length);

/**************************************************************
 *
 *                       ������ʾ����
 *                      [1/7/2012 lkh]
 */
/**************************************************************
 *
 *                       ������λ�б�
 *                    [1/25/2012 robot]
 * ˵����������Ϊ���õ�λ
 */
const char **param_unit[4];

void param_init(PROJECT_INFO *info);
void param_dislpay(MEASURE_INFO *info);
void param_toStringWithUnit(char* dest,t_param *src,const char *unit[]);

/**************************************************************
 *
 *                      dso task
 */
void dso_task(PROJECT_INFO *info);

/******************************************************
 *   
 *                defined
 */



#endif /*DSO_H_*/
