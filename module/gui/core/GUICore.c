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
File        : GUICore.C
Purpose     : Core routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */

#define  GL_CORE_C

#include "GUI_Private.h"


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#if GUI_SUPPORT_AA
static const tLCD_HL_APIList _HL_APIList = {
  LCD_DrawHLine,
  LCD_DrawPixel
};
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _InitContext
*
* Purpose
*   Initializes the given context.
*
* Special considerations
*   Make sure that no GUI functions are called, because locking is
*   not allowed here (GUITASK_INIT not yet called).
*/
static void _InitContext(GUI_CONTEXT* pContext) {
  /* memset(..,0,..) is not required, as this function is called only at startup of the GUI when data is 0 */
  pContext->pClipRect_HL = &GUI_Context.ClipRect;
  LCD_GetRect(&pContext->ClipRect);
  #if GUI_SUPPORT_AA
    pContext->pLCD_HL      = &_HL_APIList;
  #endif
  pContext->pAFont       = GUI_DEFAULT_FONT;
  pContext->pClipRect_HL = &GUI_Context.ClipRect;
  pContext->PenSize      = 1;
  /* Variables in GUI_AA module */
  #if GUI_SUPPORT_AA
    pContext->AA_Factor = 3;
  #endif
  pContext->BkColor = 0xFFFF;
  pContext->Color   = 0x0000;
  LCD_SetBkColor(0x0000);
  LCD_SetColor(0xFFFF);
  #if GUI_SUPPORT_UNICODE
    pContext->pUC_API = &GUI_UC_None;
  #endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ClearRect
*/
void GUI_ClearRect(int x0, int y0, int x1, int y1) {
  GUI_DRAWMODE PrevDraw;
  PrevDraw = LCD_SetDrawMode(GUI_DRAWMODE_REV);
  LCD_FillRect(x0,y0,x1,y1);
  LCD_SetDrawMode(PrevDraw);
}

/*********************************************************************
*
*       GUI_Clear
*/
void GUI_Clear(void) {
  GUI_GotoXY(0,0);     /* Reset text cursor to upper left */
  GUI_ClearRect(GUI_XMIN, GUI_YMIN, GUI_XMAX, GUI_YMAX);
}

/*********************************************************************
*
*       GUI_Init
*
* Purpose:
*   Init of GUI internal data structures & variables
*/
int GUI_Init(void) {
  int r;

  /* Init system wide globals first */
  GUI_DecChar = '.';
  /* Init context */
  _InitContext(&GUI_Context);
  r = LCD_Init();
  return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
