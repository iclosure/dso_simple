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
File        : GUI2DLib.C
Purpose     : Main part of the 2D graphics library
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MoveRel
*/
void GUI_MoveRel(int dx, int dy) { /*tbd: GL_LinePos. */
	GUI_Context.DrawPosX += dx;
	GUI_Context.DrawPosY += dy;
}

/*********************************************************************
*
*       GUIMoveTo
*/
void GUI_MoveTo(int x, int y) {
	GUI_Context.DrawPosX = x;
	GUI_Context.DrawPosY = y;
}
/*********************************************************************
*
*       Rectangle filling / inverting
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawRect
*/
void GUI_DrawRect(int x0, int y0, int x1, int y1) {
	LCD_DrawHLine(y0, x0, x1);
	LCD_DrawHLine(y1, x0, x1);
	LCD_DrawVLine(x0, y0+1, y1-1);
	LCD_DrawVLine(x1, y0+1, y1-1);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
