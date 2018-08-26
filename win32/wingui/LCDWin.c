/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDWin.C
Purpose     : Driver for Simulator under Windows
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00a   031007 JE     a) LCD_L0_Init changed, filling not needed at
                         this point
2.00a   030613 JE     a) Parameter of SETPIXEL checked in debug version
                      b) _DrawBitLine2bpp and _DrawBitLine4bpp reworked
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.30c   000529 JE     a) Interface changed
1.30b   000428 RS     a) DIB class eliminated
                      b) Internal cleanups, support for high color
1.30a   000417 RS     a) Major cleanup in DIB class
1.30    000309 RS     a) Interface change for emWIn V1.30
                         (LCD_L0_SetLUTEntry, LCD_GetDevCap)
1.10a   000121 RS     a) RECTHEIGHT, RECTWIDTH modified in order to
                         fix bug which would at some time prevent
												 displaying the first line of the display.
1.10.00 000110 RS     a) Modifications in order to make it easy to
                         implement driver in any windows program
1.04.02 991118 RS     a) additional assertion added
                         LCD_MAX_LOG_COLORS
1.04.01 991018 RS     a) Support for LCD_FIXEDPALETTE added
                         with Anitaliasing enabled
1.04.00 991013 JE/RS  a) Support for LCD_FIXEDPALETTE added
                      b) Driver now accepts the same LCDConf.h as
											   the embedded system
											c) Bugfix for ..
1.02.02 990831 RS     a) Small optimization added for 16-color bitmaps
1.02.01 990726 RS     a) Transparency support for 16-color bitmpas
                         added
1.02.00 990212 RS     a) New interface version 1.02 supported
1.00    990118 RS     First release
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/

#include <windows.h>
#include "LCD.h"
#include "LCD_Private.h"              /* include LCDConf.h */
#include "LCDWin.h"
#include "GUI_Private.h"
#include "color.h"


/*********************************************************************
 *
 *                将虚拟屏LCD某个矩形区域映射到Framebuff显示
 */

void lcd_displayRect(LCD_RECT rect,int x0,int y0) {
	I16 x;
	for(; rect.y0<=rect.y1; rect.y0++,y0++)
		for(x=x0; x<=x0+rect.x1-rect.x0; x++)
			LCDSIM_SetPixelIndex(x, y0, _565TO24(LCD[rect.y0][rect.x0+x-x0]), 0);
}
/*********************************************************************
 *
 *                  将当前指定的虚拟屏映射到Framebuff显示
 */

void lcd_display(void) {
	I16 x,y;
	for(y=0; y<LCD_YSIZE; y++)
		for(x=0; x<LCD_XSIZE; x++) {
			LCDSIM_SetPixelIndex(x, y, _565TO24(LCD[y][x]), 0);
		}
}
/*
void lcd_display24(void) {
	I16 x,y;
	for(y=0; y<LCD_YSIZE; y++) 
		for(x=0; x<LCD_XSIZE; x++)
			LCDSIM_SetPixelIndex(x, y, LCD24[y][x], 0);
}
*/
/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCDSIM_Init
*/
int            LCDDEV_Init(void) { return 0; }
LCD_COLOR      LCD_L0_Index2Color(int Index) { return 0; }
unsigned int   LCD_L0_Color2Index(LCD_COLOR Color) { return 0; }
unsigned int   LCD_L0_GetIndexMask(void) { return 0; }
/*********************************************************************
*
*       LCD_SetOrg
*
*  Purpose:
*    Sets the original position of the virtual display.
*    Has no function at this point with the PC-driver.
*/
void LCD_SetOrg(int x, int y) {
  LCDSIM_SetOrg(x, y, 0);
}
