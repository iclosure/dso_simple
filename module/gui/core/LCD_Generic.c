/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCD_L0_Generic.c
Purpose     : Color conversion routines for LCD-drivers
              This file may not be compiled by itself, but needs
              to be included in every LCD driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef LCD_INCLUDEDRIVER_H     /* includes only for stand-alone compilation, not as included file */
  #include <stddef.h>           /* needed for definition of NULL */
  #include "LCD_Private.h"      /* private modul definitions & config */
  #include "GUI_Private.h"
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GETINDEXMASK()   LCD_GetIndexMask_M565()
#define INDEX2COLOR      LCD_Index2Color_M565


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_GetRect
*/
void LCD_GetRect(LCD_RECT *pRect) {
  pRect->x0 = 0;
  pRect->y0 = 0;
  pRect->x1 = LCD_VXSIZE - 1;
  pRect->y1 = LCD_VYSIZE - 1;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
