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
File        : GUI_AddBin.c
Purpose     : Converts binary value 2 string
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
*       GUI_AddBin
*/
void GUI_AddBin(U32 v, U8 Len, char** ps) {
	char *s = *ps;

	(*ps) += Len;
	**ps   = '\0';     /* Make sure string is 0-terminated */
	while(Len--) {
		*(s + Len) = (char)('0' + (v & 1));
		v >>= 1;
	}
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
