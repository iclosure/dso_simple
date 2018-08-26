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
File        : GUI_Private.h
Purpose     : GUI internal declarations
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/

#ifndef  GUI_PRIVATE_H
#define  GUI_PRIVATE_H

#include "GUI_Protected.h"
#include "LCD_Private.h"   /* Required because of LCD_PIXELINDEX, which depends on LCDConf */


void LCDDEV_DrawBitmap(int x0, int y0, int xsize, int ysize, 
					   int BitsPerPixel, int BytesPerLine, 
                       const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX* pTrans);
void LCD_MAG_DrawBitmap(int x0, int y0, int xsize, int ysize, 
                           int BitsPerPixel, int BytesPerLine, 
                           const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX* pTrans);
void LCD_DELTA_DrawBitmap(int x0, int y0, int xsize, int ysize, 
                           int BitsPerPixel, int BytesPerLine, 
                           const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX* pTrans);

LCD_PIXELINDEX*  LCD_GetpPalConvTable(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal);
LCD_PIXELINDEX*  LCD_GetpPalConvTableUncached(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal);


#endif   /* ifdef GUI_H */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
