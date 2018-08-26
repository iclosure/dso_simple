
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


GUI_RECT		InfoBarArea	; /*信息栏*/
GUI_RECT		SoftKeyArea	; /*波形绘制窗口*/
GUI_RECT		WaveWinArea	; /*波形绘制窗口*/

/******************************************************
 *   
 *                defined
 */
// 
#define BYTE_SET_BITS(base, data)         (base |= data)                   // [8位]置位bit位
#define BYTE_CLR_BITS(base, data)         (base &= (~(data)) & 0xFF)       // [8位]清除bit位
#define WORD_SET_BITS(base, data)         (base |= data)                   // [16位]置位bit位
#define WORD_CLR_BITS(base, data)         (base &= (~(data)) & 0xFFFF)     // [16位]清除bit位
#define DWORD_SET_BITS(base, data)        (base |= data)                   // [32位]置位bit位
#define DWORD_CLR_BITS(base, data)        (base &= (~(data)) & 0xFFFFFFFF) // [32位]清除bit位

/******************************************************
 *   
 *               窗口: 显示或隐藏标志定义
 */
#define WIN_FLAG_DISP        (1)  // 显示窗口
#define WIN_FLAG_HIDE        (2)  // 隐藏窗口

/**************************************************************
 * 
 *          DSO_InitGUI [初始化示波器主界面]
 * 
 */
void dso_reset(PROJECT_INFO *info);
void dso_init(PROJECT_INFO *info);
void dso_start(PROJECT_INFO *info);


/**************************************************************
 *
 *                  框图绘制相关函数
 *
 */
void dso_drawSmallBarBk(GUI_RECT rect, U16 FillColor);
void dso_drawLargeBarBk(GUI_RECT rect, U16 FillColor);
void dso_drawTitleBar(const char *title, int y0,int x0,int x1);
void dso_drawFrame(GUI_RECT rect, U16 FillColor, const char *title);
void dso_drawSKSelRect(int x0,int y0, int length);

/**************************************************************
 *
 *                       参数显示处理
 *                      [1/7/2012 lkh]
 */
/**************************************************************
 *
 *                       参数单位列表
 *                    [1/25/2012 robot]
 * 说明：第五列为常用单位
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
