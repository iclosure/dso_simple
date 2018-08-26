
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
 *               以下为示波器界面GUI的各类区域信息默认设置
 */
/****************************************************************
 *                       -- ALL --
 */
/*[default]一通道*/
#define CH1_COLOR			_24TO565(0xFF,0xFF,0x00)	/**/
/*[default]二通道*/
#define CH2_COLOR			_24TO565(0x32,0xFF,0x00)	/**/
/*[default]一通道*/
#define CH3_COLOR			_24TO565(0x55,0x78,0xFF)	/**/
/*[default]二通道*/
#define CH4_COLOR			_24TO565(0xFF,0x00,0x84)	/**/
/*[default]基本的字符颜色*/
#define BASE_FONTCOLOR		_24TO565(225,225,225)	/**/
#define BAR_POSEDGECOLOR	_24TO565(130,130,130)	/*信息栏阳面颜色*/
#define BAR_NEGEDGECOLOR	_24TO565( 80, 80, 80)   /*信息栏阴面颜色*/
#define BAR_FILLCOLOR		_24TO565( 24, 24, 24)   /*信息栏填充颜色*/
#define TITLEBAR_YSIZE		(20)                    /*标题栏默认高度*/
#define TITLEBAR_EDGECOLOR	_24TO565(130,130,130)   /*标题栏边框颜色*/
#define TITLEBAR_DOTCOLOR	(0xE71C)                /*标题栏*/
#define TITLEBAR_FILLCOLOR	(0x52CB)                /*标题栏填充颜色*/
#define DesktopBkColor		color_black				/*默认桌面背景颜色*/
/* --------------------  SINGLE --------------------- */

/****************************************************************
 *    [default]状态栏信息[界面顶部,主要显示项有: ]/
 */
#define STATUSBAR_SX		(6)
#define STATUSBAR_SY		(2)      /*初始二维坐标*/
#define STATUSBAR_EX		(LCD_XSIZE-3)
#define STATUSBAR_EY		(WAVEEXFRAME_SY-3)    /*终止二维坐标*/
#define STATUSBARE_BKIMG	(NULL)   /*背景图片句柄*/

/****************************************************************
 *    [default]波形区域外框信息[界面中间和左边部分,主要显示项有: ]
 */
#define WAVEWIN_XSIZE				(640)    /*波形区域水平宽度*/
#define WAVEWIN_YSIZE				(400)    /*波形区域垂直宽度*/
#define WAVEWIN_MIDDLE				(WAVEWIN_SY+WAVEWIN_YSIZE/2)  /*波形区域垂直中线位置*/
#define WAVEWIN_GRIDCOLOR			_24TO565( 50, 50, 50)		  /*默认网格颜色*/
/*外框属性*/
#define WAVEEXFRAME_DEFAULTCOLOR	color_white  /*线条默认颜色*/
#define WAVEEXFRAME_SX				(16)
#define WAVEEXFRAME_SY				(20)         /*外框初始二维坐标*/
#define WAVEEXFRAME_EX				(WAVEEXFRAME_SX+WAVEWIN_XSIZE+1)
#define WAVEEXFRAME_EY				(WAVEEXFRAME_SY+WAVEWIN_YSIZE+1)  /*外框终止二维坐标*/

/****************************************************************
 *    [default]波形区域信息[界面中间部分,主要显示项有: 波形,参数]/
 */
#define WAVEWIN_SX					(WAVEEXFRAME_SX+1)
#define WAVEWIN_SY					(WAVEEXFRAME_SY+1)  /*初始二维坐标*/
#define WAVEWIN_EX					(WAVEWIN_SX+WAVEWIN_XSIZE-1)
#define WAVEWIN_EY					(WAVEWIN_SY+WAVEWIN_YSIZE-1)  /*终止二维坐标*/
#define WAVEWIN_XMID				((WAVEWIN_SX+WAVEWIN_EX)/2)
#define WAVEWIN_YMID				((WAVEWIN_SY+WAVEWIN_EY)/2)   /*波形窗口的中心坐标*/
#define WAVEWIN_BKIMG				(bmwavewinbk)   /*背景图片句柄*/
#define WAVEWIN_ARROW_COLOR			color_yellow
/*网格*/
#define WAVEWIN_XGRIDNUM			(10)  /*X轴方向网格数*/
#define WAVEWIN_YGRIDNUM			(8)   /*Y轴方向网格数*/
#define WAVEWIN_XGRIDSIZE			(WAVEWIN_XSIZE/WAVEWIN_XGRIDNUM)  /*X轴方向网格宽度*/
#define WAVEWIN_YGRIDSIZE			(WAVEWIN_YSIZE/WAVEWIN_YGRIDNUM)  /*Y轴方向网格宽度*/
/*刻度线*/
#define WAVEWIN_XSCALENUM			(4)   /*X轴方向的一个网格的刻度数*/
#define WAVEWIN_YSCALENUM			(5)   /*Y轴方向的一个网格的刻度数*/
#define WAVEWIN_XSCALE_TOTALNUM		(WAVEWIN_XGRIDNUM*WAVEWIN_XSCALENUM)   /*X轴方向的刻度数*/
#define WAVEWIN_YSCALE_TOTALNUM		(WAVEWIN_YGRIDNUM*WAVEWIN_YSCALENUM)   /*Y轴方向的刻度数*/
#define WAVEWIN_XSCALESIZE			(5)   // X轴方向刻度线长度
#define WAVEWIN_YSCALESIZE			(5)   // Y轴方向刻度线长度
#define WAVEWIN_XSCALEINTERVAL		(WAVEWIN_XGRIDSIZE/WAVEWIN_XSCALENUM)  /*X轴方向刻度线间隔*/
#define WAVEWIN_YSCALEINTERVAL		(WAVEWIN_YGRIDSIZE/WAVEWIN_YSCALENUM)  /*Y轴方向刻度线间隔*/

/****************************************************************
 *    [default]信息区域信息[界面右边部分,主要显示项有: ]/
 */
#define INFOBAR_SX				(WAVEEXFRAME_EX+3)
#define INFOBAR_SY				(WAVEEXFRAME_SY)      /*初始二维坐标*/
#define INFOBAR_EX				(LCD_XSIZE-2)
#define INFOBAR_EY				(WAVEEXFRAME_EY)     /*最大二维坐标*/
#define INFOBAR_XSIZE			(INFOBAR_EX-INFOBAR_SX+1)  /*尺寸*/
#define INFOBAR_YSIZE			(INFOBAR_EY-INFOBAR_SY+1)  /*最大二维坐标*/

#define INFOBAR_LOGO_HEIGHT		(bmLogo.YSize+10)  /*LOGO区域高度*/
#define INFOBAR_LOGO_SY			(INFOBAR_SY)

#define INFOBAR_ACQ_HEIGHT		(60)  /*采集区域客户区高度*/
#define INFOBAR_ACQ_SY			(INFOBAR_LOGO_SY+INFOBAR_LOGO_HEIGHT+3)

#define INFOBAR_CH_SY			(INFOBAR_ACQ_SY+INFOBAR_ACQ_HEIGHT+TITLEBAR_YSIZE-3)

#define INFOBAR_PARAM_HEIGHT	(60)  /*参数区域客户区高度*/

/****************************************************************
 *    [default]菜单行信息[界面底部(软键区域以上),主要显示项有: ]/
 */
#define MENULINE_ARROW_COLOR	color_white
#define MENULINE_SX				(3)
#define MENULINE_SY				(421)  /*初始二维坐标*/
#define MENULINE_EX				(796)
#define MENULINE_EY				(439)  /*最大二维坐标*/

/****************************************************************
 *    [default]软键区域信息[界面底部,主要显示项有: ]/
 */
#define SOFTKEY_SX					(7)
#define SOFTKEY_SY					(443)            /*初始二维坐标*/
#define SOFTKEY_EX					(792)
#define SOFTKEY_EY					(478)            /*最大二维坐标*/
#define SOFTKEY_BKIMG				(bmsoftkeybk)    /*背景图片句柄*/
#define SOFTKEY_KNOP_SX				(5)              /*软键旋钮状态图标的相对起始X坐标*/
#define SOFTKEY_KNOP_SY				(3)              /*软键旋钮状态图标的相对起始Y坐标*/
#define SOFTKEY_SPACE				(6)              /*两个软键之间的距离*/
#define SOFTKEY_XSIZE				(SOFTKEY_BKIMG.XSize)
#define SOFTKEY_YSIZE				(SOFTKEY_BKIMG.YSize)  /*软键尺寸*/
#define SOFTKEY_SELRECT_SY			(SOFTKEY_SY+20)
#define SOFTKEY_SELRECT_SIZE		(15)
#define SOFTKEY_SELFILLRECT_SIZE	(10)
#define SOFTKEY_SELRECT_POSCOLOR	_24TO565(130,130,130)
#define SOFTKEY_SELRECT_NEGCOLOR	_24TO565( 80, 80, 80)
#define SOFTKEY_SELCOLOR			(MENUUP_SELBKCOLOR)    /*RECT型软键被选中项的背景色*/

/****************************************************************
 *    [default]上拉菜单信息[主要显示项有: ]/
 */
#define MENUUP_XMAXSIZE				(WAVEWIN_XSIZE)
#define MENUUP_YMAXSIZE				(WAVEWIN_YSIZE)  /*上拉菜单的最大尺寸*/
#define MENUUP_EY					(433)     /*上拉菜单的下方Y坐标*/

#define MENUUP_TOPTITLE_HEIGHT		(20)      /*上拉菜单总标题高度*/
#define MENUUP_SUBTITLE_HEIGHT		(20)      /*上拉菜单子标题高度*/
#define MENUUP_MENU_SPACE			(4)       /*上拉菜单选项之间的间隔*/
#define MENUUP_MENU_SPACEHALF		(MENUUP_MENU_SPACE/2)  /*上拉菜单选项之间的间隔的一半*/
#define MENUUP_SEPARALINE_HEIGHT	(1)       /*上拉菜单分隔线宽度*/
#define MENUUP_FINGER_HEIGHT		(15)	  /*上拉菜单子上下滑动指示器所在行占用的高度*/
#define MENUUP_SELBKCOLOR			_24TO565(  0,130,170)  /*上拉菜单被选中项的背景色*/
#define MENUUP_ICONFRAME_XSIZE		(52)      /*[彩图]框架宽度*/
#define MENUUP_ICONFRAME_YSIZE		(41)      /*[彩图]框架高度*/
#define MENUUP_ICONFRAMEBKCOLOR		(0x2145)  /*[彩图]框架背景色*/

/****************************************************************
 *    [default][测量类参数快照信息]/
 */











#endif /*DSO_CONFDEFAULTS_H_*/
