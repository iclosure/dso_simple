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
File        : GUI_GetClientRect.c
Purpose     : Implementation of GUI_GetClientRect
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
*       GUI_GetClientRect
*/
void GUI_GetClientRect(GUI_RECT* pRect) {
	if (!pRect)
		return;
// 	pRect->x0 = 0;
// 	pRect->y0 = 0;
//  pRect->x1 = LCD_GET_VXSIZE();
//  pRect->y1 = LCD_GET_VYSIZE();
	pRect->x0 = GUI_Context.ClipRect.x0;
	pRect->y0 = GUI_Context.ClipRect.y0;
	pRect->x1 = GUI_Context.ClipRect.x1;
	pRect->y1 = GUI_Context.ClipRect.y1;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
