/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_Pen.C
Purpose     : Getting / Setting pen attributes
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
*       GUI_SetPenSize
*/
U8 GUI_SetPenSize(U8 PenSize) {
	U8 r;
    r = GUI_Context.PenSize;
    GUI_Context.PenSize = PenSize;
	return r;
}

/*********************************************************************
*
*       GUI_SetPenShape
*/
U8 GUI_SetPenShape(U8 PenShape) {
	U8 r;
    r = GUI_Context.PenShape;
    GUI_Context.PenShape = PenShape;
	return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
