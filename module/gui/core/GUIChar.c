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
File        : GUIChar.C
Purpose     : Implementation of character and string services
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include "GUI_Protected.h"
 
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispNextLine
*/
void GUI_DispNextLine(void) {
  GUI_Context.DispPosY += GUI_GetFontDistY();
  GUI_Context.DispPosX  = GUI_Context.LBorder;
}

/*********************************************************************
*
*       GUI_DispChar
*/
void GUI_DispChar(U16 c) {
  /* check for control characters */
  if (c == '\n') {
    GUI_DispNextLine();
  } else {
    if (c != '\r') {
      GUI_Context.pAFont->pfDispChar(c);
      if (GUI_pfDispCharStyle) {
        GUI_pfDispCharStyle(c);
      }
    }
  }
}

/*********************************************************************
*
*       GUI_GetYAdjust
*
* Returns adjustment in vertical (Y) direction
*
* Note: The return value needs to be subtracted from
*       the y-position of the character.
*/
int GUI_GetYAdjust(void) {
  int r = 0;
  switch (GUI_Context.TextAlign & GUI_TA_VERTICAL) {
	case GUI_TA_BOTTOM:
		r = GUI_Context.pAFont->YSize - 1;
    break;
	case GUI_TA_VCENTER:
		r = GUI_Context.pAFont->YSize / 2;
    break;
	case GUI_TA_BASELINE:
		r = GUI_Context.pAFont->YSize / 2;
	}
  return r;
}

/*********************************************************************
*
*       GUI_GetFontDistY
*/
int GUI_GetFontDistY(void) {
  return GUI_Context.pAFont->YDist;
}

/*********************************************************************
*
*       GUI_GetCharDistX
*/
int GUI_GetCharDistX(U16 c) {
  return GUI_Context.pAFont->pfGetCharDistX(c);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
