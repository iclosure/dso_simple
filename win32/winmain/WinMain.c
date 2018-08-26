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
File        : SIM_X.c
Purpose     : Windows Simulator externals
              The init routine in this file can be used to set up the
              simulator
---------------------------END-OF-HEADER------------------------------
*/

#include "Win.h"
#include "GUI.h"


#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"		          /* interface definitions */
#include "LCD_Private.h"      /* private modul definitions & config */
// LCD_GetNumLayers.c
int LCD_GetNumLayers(void) {return 1;}
// LCD_GetEx.c
int LCD_GetXSizeEx(int LayerIndex)  { return LCD_XSIZE;  }
int LCD_GetYSizeEx(int LayerIndex)  { return LCD_YSIZE;  }
int LCD_GetVXSizeEx(int LayerIndex) { return LCD_VXSIZE; }
int LCD_GetVYSizeEx(int LayerIndex) { return LCD_VYSIZE; }
int LCD_GetBitsPerPixelEx(int LayerIndex) { return LCD_BITSPERPIXEL; }
int LCD_GetBitsPerPixel_L0Ex(int LayerIndex) { return LCD_BITSPERPIXEL_L0; }
U32 LCD_GetNumColorsEx(int LayerIndex) { return LCD_NUM_COLORS; }
int LCD_GetYMagEx(int LayerIndex) { return LCD_YMAG; }
int LCD_GetXMagEx(int LayerIndex) { return LCD_XMAG; }
I32 LCD_GetFixedPaletteEx(int LayerIndex) { return LCD_FIXEDPALETTE; }
int LCD_GetMirrorXEx(int LayerIndex) { return LCD_MIRROR_X; }
int LCD_GetMirrorYEx(int LayerIndex) { return LCD_MIRROR_Y; }
int LCD_GetSwapXYEx(int LayerIndex)  { return LCD_SWAP_XY;  }
int LCD_GetSwapRBEx(int LayerIndex)  { return LCD_SWAP_RB;  }
int LCD_GetDeltaModeEx(int LayerIndex) { return LCD_DELTA_MODE; }
unsigned int LCD_Index2ColorEx(int index) { return index;}

// lib
int GUI_Delay(void) { return 0; }


void SIM_GUI_X_Init(void) {
	if (((LCD_GetDevCap(LCD_DEVCAP_XSIZE) * LCD_GetXMag()) < 1300) && 
		((LCD_GetDevCap(LCD_DEVCAP_YSIZE) * LCD_GetYMag()) < 760))
	{
		SIM_SetLCDPos(103,15);                 // Define the position of the LCD in the bitmap (large)
		SIM_SetTransColor(0xFF0000);          // Define the transparent color
	}
}


/*******************************************************************
*
*       MainTask 
*
*       Demonstrates the use of a memory device
*
********************************************************************
*/

#include "key.h"
#if defined(UCOSII)
#include "ucos_ii.h"
#endif

#include "global.h"
#include "dso.h"

#include <string.h>
#include <stdio.h>

void MainTask(void) {

	if(SIM_HARDKEY_GetNum() != KEY_NUM) exit(1);  // 检测按键是否设置正确
	// 模拟电源开关功能
	/********************************/
	while(SIM_HARDKEY_GetState(KEY_MENU_POWER)==0);  // 读取按键状态;
	/********************************/
	dso_init(&prj_info);  // 进入用户的主函数 [ WIN32 -- system:windows/*consle*/ ]
	dso_start(&prj_info);
}