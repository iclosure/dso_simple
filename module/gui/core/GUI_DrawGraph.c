/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_DrawPolyline.c
Purpose     : Implementation of GUI_DrawPolyline
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
*       GUI_DrawGraph
*/
void GUI_DrawGraph(I16 *pay, int NumPoints, int xoff, int yoff) {
  int i;
  int y0, y1;
  int yClip0, yClip1;
  /* Perform high level clipping in x */
  yClip0 = GUI_Context.pClipRect_HL->y0;
  yClip1 = GUI_Context.pClipRect_HL->y1;
  i=0;
  if (GUI_Context.pClipRect_HL) {
    if (xoff < GUI_Context.pClipRect_HL->x0)
      i = GUI_Context.pClipRect_HL->x0 - xoff;
    if (xoff+NumPoints-1 > GUI_Context.pClipRect_HL->x1)
      NumPoints = GUI_Context.pClipRect_HL->x1 - xoff + 1;
  }
  /* Start drawing if there is something left to do after x-clipping */
  if (i < NumPoints) {
    y0 = *(pay + i++) + yoff;
    /* Iterate */
    for (; i < NumPoints; i++) {
      /* Perform high level clipping in y */
      y1 = *(pay + i) + yoff;
      if ((y0 >= yClip0) || (y1 >= yClip0)) {
        if ((y0 <= yClip1) || (y1 <= yClip1)) {
          int y01;
          y01 = (y1 + y0) / 2;
          if (y0 <= y1) {
            LCD_DrawVLine(i + xoff - 1, y0, y01);
            LCD_DrawVLine(i + xoff, y01, y1);
          } else {
            LCD_DrawVLine(i + xoff - 1, y01, y0);
            LCD_DrawVLine(i + xoff, y1, y01);
          }
        }
      }
      y0 = y1;
    }
  }
}

/*********************************************************************
*
*       GUI_DrawFoldLine 
*
*     ExPoints 是用户想要的宽度，也就是实际期望画的点数 [ExPoints最好是(NumPoints-1)的整数倍]
*/ 
void GUI_DrawFoldLine(I16* pay, int NumPoints, int xoff, int yoff, int ExPoints) {
	U16 i, dx= ExPoints / (NumPoints-1);
	GUI_MoveTo(xoff,pay[0]+yoff);
	for(i=1; i<NumPoints; i++)
		GUI_DrawLineRel(dx, pay[i]-pay[i-1]);
}

/*********************************************************************
*
*       GUI_AA_DrawGraph
*/

void GUI_AA_DrawGraph(I16 *pay, int NumPoints, int xoff, int yoff) {
	int i;
	int y0, y1;
	int yClip0, yClip1;
	/* Perform high level clipping in x */
	yClip0 = GUI_Context.pClipRect_HL->y0;
	yClip1 = GUI_Context.pClipRect_HL->y1;
	i=0;
	if (GUI_Context.pClipRect_HL) {
		if (xoff < GUI_Context.pClipRect_HL->x0)
			i = GUI_Context.pClipRect_HL->x0 - xoff;
		if (xoff+NumPoints-1 > GUI_Context.pClipRect_HL->x1)
			NumPoints = GUI_Context.pClipRect_HL->x1 - xoff + 1;
	}
	/* Start drawing if there is something left to do after x-clipping */
	if (i < NumPoints) {
		y0 = *(pay + i++) + yoff;
		/* Iterate */
		for (; i < NumPoints; i++) {
			/* Perform high level clipping in y */
			y1 = *(pay + i) + yoff;
			if ((y0 >= yClip0) || (y1 >= yClip0)) {
				if ((y0 <= yClip1) || (y1 <= yClip1)) {
					int y01;
					y01 = (y1 + y0) / 2;
					if (y0 <= y1) {
						GUI_AA_DrawLine(i + xoff - 1,y0,i + xoff - 1, y01);
						GUI_AA_DrawLine(i + xoff,y01,i + xoff, y1);
					} else {
						GUI_AA_DrawLine(i + xoff - 1,y01,i + xoff - 1, y0);
						GUI_AA_DrawLine(i + xoff,y1,i + xoff, y01);
					}
				}
			}
			y0 = y1;
		}
	}
}


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
