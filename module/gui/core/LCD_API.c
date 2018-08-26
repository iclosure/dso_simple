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
File        : LCD_API.C
Purpose     : Selection of LCD display
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

/***********************************************************
*
*                 LCD_aAPI
*
* Purpose:
*  This table lists the available displays/layers by a single pointer.
*  It is important that these are non-constants, because some high level
*  software (such as the VNC server, but maybe also the mouse "Cursor" mdoule)
*  may need to override these pointers in order to link itself into the chain
*  of drawing routines.
*  However, the API tables may of course be constants.
*
*/

const tLCDDEV_APIList LCD_aAPI = {
  (tLCDDEV_DrawBitmap*)LCDDEV_DrawBitmap,
	LCD_DrawHLine,
	LCD_DrawVLine,
	LCD_FillRect,
	LCD_GetPixelIndex,
	LCD_GetRect,
	LCD_SetPixelIndex,
    LCD_XorPixel,
 };


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
