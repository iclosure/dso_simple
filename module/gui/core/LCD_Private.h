/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCD_Private.h
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef LCD_Private_H
#define LCD_Private_H

#include "LCD_ConfDefaults.h"            /* Configuration header file */
#include "LCD_Protected.h"
#include "GUI.h"

typedef struct {
  LCD_COLOR * paColor;
  I16         NumEntries;
} LCD_LUT_INFO;


#if GUI_COMPILER_SUPPORTS_FP

//extern const tLCDDEV_APIList LCD_aAPI;

//const tLCDDEV_APIList* LCD_SetAPI      (const tLCDDEV_APIList* pAPI, int Index);
//const tLCDDEV_APIList* LCD_SetAPIForAll(const tLCDDEV_APIList* pAPI, int Index);

#endif

#define LCD_BKCOLORINDEX GUI_Context.aColorIndex16[0]
#define LCD_COLORINDEX   GUI_Context.aColorIndex16[1]
#define LCD_ACOLORINDEX  GUI_Context.aColorIndex16

extern LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];

void LCD_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int xMul, int yMul,
                       int BitsPerPixel,
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pPixel,
                       const LCD_PIXELINDEX* pTrans);
void LCD_UpdateColorIndices(void);

/*********************************************************************
*
*          Support for Segment/COMLUTs
*
**********************************************************************
*/

#define LCD_TYPE_SEGTRANS U16
#define LCD_TYPE_COMTRANS U16

#ifdef LCD_LUT_COM
  #ifdef LCDCOLOR_C
    LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE] = { LCD_LUT_COM };
  #else
    extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE];
  #endif
#endif

#ifdef LCD_LUT_SEG
  #ifdef LCDCOLOR_C
    LCD_TYPE_SEGTRANS LCD__aCol2Seg0[LCD_XSIZE] = { LCD_LUT_SEG };
  #else
    extern LCD_TYPE_COMTRANS LCD__aCol2Seg0[LCD_XSIZE];
  #endif
#endif

#endif /* Avoid multiple inclusion */


/*************************** End of file ****************************/

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
