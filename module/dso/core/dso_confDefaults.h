
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
 File        : DSO_ConfDefaults.h
 Purpose     : Defaults for DSO config switches.
   ----------------------------------------------------------------------
 */

#ifndef DSO_CONFDEFAULTS_H_
#define DSO_CONFDEFAULTS_H_

#include "dso.h"
#include <stdlib.h>


/***********************************************************************
 * 
 *               ����Ϊʾ��������GUI�ĸ���������ϢĬ������
 */
/****************************************************************
 *                       -- ALL --
 */
/*[default]һͨ��*/
#define CH1_COLOR			_24TO565(0xFF,0xFF,0x00)	/**/
/*[default]��ͨ��*/
#define CH2_COLOR			_24TO565(0x32,0xFF,0x00)	/**/
/*[default]һͨ��*/
#define CH3_COLOR			_24TO565(0x55,0x78,0xFF)	/**/
/*[default]��ͨ��*/
#define CH4_COLOR			_24TO565(0xFF,0x00,0x84)	/**/
/*[default]�������ַ���ɫ*/
#define BASE_FONTCOLOR		_24TO565(225,225,225)	/**/
#define BAR_POSEDGECOLOR	_24TO565(130,130,130)	/*��Ϣ��������ɫ*/
#define BAR_NEGEDGECOLOR	_24TO565( 80, 80, 80)   /*��Ϣ��������ɫ*/
#define BAR_FILLCOLOR		_24TO565( 24, 24, 24)   /*��Ϣ�������ɫ*/
#define TITLEBAR_YSIZE		(20)                    /*������Ĭ�ϸ߶�*/
#define TITLEBAR_EDGECOLOR	_24TO565(130,130,130)   /*�������߿���ɫ*/
#define TITLEBAR_DOTCOLOR	(0xE71C)                /*������*/
#define TITLEBAR_FILLCOLOR	(0x52CB)                /*�����������ɫ*/
#define DesktopBkColor		color_black				/*Ĭ�����汳����ɫ*/
/* --------------------  SINGLE --------------------- */

/****************************************************************
 *    [default]״̬����Ϣ[���涥��,��Ҫ��ʾ����: ]/
 */
#define STATUSBAR_SX		(6)
#define STATUSBAR_SY		(2)      /*��ʼ��ά����*/
#define STATUSBAR_EX		(LCD_XSIZE-3)
#define STATUSBAR_EY		(WAVEEXFRAME_SY-3)    /*��ֹ��ά����*/
#define STATUSBARE_BKIMG	(NULL)   /*����ͼƬ���*/

/****************************************************************
 *    [default]�������������Ϣ[�����м����߲���,��Ҫ��ʾ����: ]
 */
#define WAVEWIN_XSIZE				(640)    /*��������ˮƽ���*/
#define WAVEWIN_YSIZE				(400)    /*��������ֱ���*/
#define WAVEWIN_MIDDLE				(WAVEWIN_SY+WAVEWIN_YSIZE/2)  /*��������ֱ����λ��*/
#define WAVEWIN_GRIDCOLOR			_24TO565( 50, 50, 50)		  /*Ĭ��������ɫ*/
/*�������*/
#define WAVEEXFRAME_DEFAULTCOLOR	color_white  /*����Ĭ����ɫ*/
#define WAVEEXFRAME_SX				(16)
#define WAVEEXFRAME_SY				(20)         /*����ʼ��ά����*/
#define WAVEEXFRAME_EX				(WAVEEXFRAME_SX+WAVEWIN_XSIZE+1)
#define WAVEEXFRAME_EY				(WAVEEXFRAME_SY+WAVEWIN_YSIZE+1)  /*�����ֹ��ά����*/

/****************************************************************
 *    [default]����������Ϣ[�����м䲿��,��Ҫ��ʾ����: ����,����]/
 */
#define WAVEWIN_SX					(WAVEEXFRAME_SX+1)
#define WAVEWIN_SY					(WAVEEXFRAME_SY+1)  /*��ʼ��ά����*/
#define WAVEWIN_EX					(WAVEWIN_SX+WAVEWIN_XSIZE-1)
#define WAVEWIN_EY					(WAVEWIN_SY+WAVEWIN_YSIZE-1)  /*��ֹ��ά����*/
#define WAVEWIN_XMID				((WAVEWIN_SX+WAVEWIN_EX)/2)
#define WAVEWIN_YMID				((WAVEWIN_SY+WAVEWIN_EY)/2)   /*���δ��ڵ���������*/
#define WAVEWIN_BKIMG				(bmwavewinbk)   /*����ͼƬ���*/
#define WAVEWIN_ARROW_COLOR			color_yellow
/*����*/
#define WAVEWIN_XGRIDNUM			(10)  /*X�᷽��������*/
#define WAVEWIN_YGRIDNUM			(8)   /*Y�᷽��������*/
#define WAVEWIN_XGRIDSIZE			(WAVEWIN_XSIZE/WAVEWIN_XGRIDNUM)  /*X�᷽��������*/
#define WAVEWIN_YGRIDSIZE			(WAVEWIN_YSIZE/WAVEWIN_YGRIDNUM)  /*Y�᷽��������*/
/*�̶���*/
#define WAVEWIN_XSCALENUM			(4)   /*X�᷽���һ������Ŀ̶���*/
#define WAVEWIN_YSCALENUM			(5)   /*Y�᷽���һ������Ŀ̶���*/
#define WAVEWIN_XSCALE_TOTALNUM		(WAVEWIN_XGRIDNUM*WAVEWIN_XSCALENUM)   /*X�᷽��Ŀ̶���*/
#define WAVEWIN_YSCALE_TOTALNUM		(WAVEWIN_YGRIDNUM*WAVEWIN_YSCALENUM)   /*Y�᷽��Ŀ̶���*/
#define WAVEWIN_XSCALESIZE			(5)   // X�᷽��̶��߳���
#define WAVEWIN_YSCALESIZE			(5)   // Y�᷽��̶��߳���
#define WAVEWIN_XSCALEINTERVAL		(WAVEWIN_XGRIDSIZE/WAVEWIN_XSCALENUM)  /*X�᷽��̶��߼��*/
#define WAVEWIN_YSCALEINTERVAL		(WAVEWIN_YGRIDSIZE/WAVEWIN_YSCALENUM)  /*Y�᷽��̶��߼��*/

/****************************************************************
 *    [default]��Ϣ������Ϣ[�����ұ߲���,��Ҫ��ʾ����: ]/
 */
#define INFOBAR_SX				(WAVEEXFRAME_EX+3)
#define INFOBAR_SY				(WAVEEXFRAME_SY)      /*��ʼ��ά����*/
#define INFOBAR_EX				(LCD_XSIZE-2)
#define INFOBAR_EY				(WAVEEXFRAME_EY)     /*����ά����*/
#define INFOBAR_XSIZE			(INFOBAR_EX-INFOBAR_SX+1)  /*�ߴ�*/
#define INFOBAR_YSIZE			(INFOBAR_EY-INFOBAR_SY+1)  /*����ά����*/

#define INFOBAR_LOGO_HEIGHT		(bmLogo.YSize+10)  /*LOGO����߶�*/
#define INFOBAR_LOGO_SY			(INFOBAR_SY)

#define INFOBAR_ACQ_HEIGHT		(60)  /*�ɼ�����ͻ����߶�*/
#define INFOBAR_ACQ_SY			(INFOBAR_LOGO_SY+INFOBAR_LOGO_HEIGHT+3)

#define INFOBAR_CH_SY			(INFOBAR_ACQ_SY+INFOBAR_ACQ_HEIGHT+TITLEBAR_YSIZE-3)

#define INFOBAR_PARAM_HEIGHT	(60)  /*��������ͻ����߶�*/

/****************************************************************
 *    [default]�˵�����Ϣ[����ײ�(�����������),��Ҫ��ʾ����: ]/
 */
#define MENULINE_ARROW_COLOR	color_white
#define MENULINE_SX				(3)
#define MENULINE_SY				(421)  /*��ʼ��ά����*/
#define MENULINE_EX				(796)
#define MENULINE_EY				(439)  /*����ά����*/

/****************************************************************
 *    [default]���������Ϣ[����ײ�,��Ҫ��ʾ����: ]/
 */
#define SOFTKEY_SX					(7)
#define SOFTKEY_SY					(443)            /*��ʼ��ά����*/
#define SOFTKEY_EX					(792)
#define SOFTKEY_EY					(478)            /*����ά����*/
#define SOFTKEY_BKIMG				(bmsoftkeybk)    /*����ͼƬ���*/
#define SOFTKEY_KNOP_SX				(5)              /*�����ť״̬ͼ��������ʼX����*/
#define SOFTKEY_KNOP_SY				(3)              /*�����ť״̬ͼ��������ʼY����*/
#define SOFTKEY_SPACE				(6)              /*�������֮��ľ���*/
#define SOFTKEY_XSIZE				(SOFTKEY_BKIMG.XSize)
#define SOFTKEY_YSIZE				(SOFTKEY_BKIMG.YSize)  /*����ߴ�*/
#define SOFTKEY_SELRECT_SY			(SOFTKEY_SY+20)
#define SOFTKEY_SELRECT_SIZE		(15)
#define SOFTKEY_SELFILLRECT_SIZE	(10)
#define SOFTKEY_SELRECT_POSCOLOR	_24TO565(130,130,130)
#define SOFTKEY_SELRECT_NEGCOLOR	_24TO565( 80, 80, 80)
#define SOFTKEY_SELCOLOR			(MENUUP_SELBKCOLOR)    /*RECT�������ѡ����ı���ɫ*/

/****************************************************************
 *    [default]�����˵���Ϣ[��Ҫ��ʾ����: ]/
 */
#define MENUUP_XMAXSIZE				(WAVEWIN_XSIZE)
#define MENUUP_YMAXSIZE				(WAVEWIN_YSIZE)  /*�����˵������ߴ�*/
#define MENUUP_EY					(433)     /*�����˵����·�Y����*/

#define MENUUP_TOPTITLE_HEIGHT		(20)      /*�����˵��ܱ���߶�*/
#define MENUUP_SUBTITLE_HEIGHT		(20)      /*�����˵��ӱ���߶�*/
#define MENUUP_MENU_SPACE			(4)       /*�����˵�ѡ��֮��ļ��*/
#define MENUUP_MENU_SPACEHALF		(MENUUP_MENU_SPACE/2)  /*�����˵�ѡ��֮��ļ����һ��*/
#define MENUUP_SEPARALINE_HEIGHT	(1)       /*�����˵��ָ��߿��*/
#define MENUUP_FINGER_HEIGHT		(15)	  /*�����˵������»���ָʾ��������ռ�õĸ߶�*/
#define MENUUP_SELBKCOLOR			_24TO565(  0,130,170)  /*�����˵���ѡ����ı���ɫ*/
#define MENUUP_ICONFRAME_XSIZE		(52)      /*[��ͼ]��ܿ��*/
#define MENUUP_ICONFRAME_YSIZE		(41)      /*[��ͼ]��ܸ߶�*/
#define MENUUP_ICONFRAMEBKCOLOR		(0x2145)  /*[��ͼ]��ܱ���ɫ*/

/****************************************************************
 *    [default][���������������Ϣ]/
 */











#endif /*DSO_CONFDEFAULTS_H_*/
