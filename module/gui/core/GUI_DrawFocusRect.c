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
File        : GUI_DrawFocusRect.C
Purpose     : Implementation of GUI_DrawFocusRect
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawFocusRect
*/
void GUI_DrawFocusRect(const GUI_RECT *pRect, int Dist) {
	int i;
	GUI_RECT r;

	GUI__ReduceRect(&r, pRect, Dist);
	for (i = r.x0; i <= r.x1; i += 2) {
		LCD_DrawPixel(i, r.y0);
		LCD_DrawPixel(i, r.y1);
	}
	for (i = r.y0; i <= r.y1; i += 2) {
		LCD_DrawPixel(r.x0, i);
		LCD_DrawPixel(r.x1, i);
	}
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
