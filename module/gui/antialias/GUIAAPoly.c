/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : GUIPolyAA.C
Purpose     : Draw Polygon routines with Antialiasing
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#if GUI_SUPPORT_AA

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_AA_FillPolygon
*/
void GUI_AA_FillPolygon(GUI_POINT* paPoint, int NumPoints, int x, int y) {
  int i;
  int Stat;
  int x0,x1;
  int PosFactor = GUI_Context.AA_HiResEnable ? 1 : GUI_Context.AA_Factor;
/* Calc horizontal limits and init GUI_AA */
  x0 = x1 = paPoint[0].x;
  for (i=1; i< NumPoints; i++) {
    int x =  paPoint[i].x;
    if (x<x0)
      x0 = x;
    if (x>x1)
      x1 = x;
  }
  if (!GUI_Context.AA_HiResEnable) {
    Stat = GUI_AA_Init(x0+x,x1+x);
  } else {
    Stat = GUI_AA_Init((x0+x)/GUI_Context.AA_Factor,(x1+x)/GUI_Context.AA_Factor);
  }
  if (Stat ==0) {
    /* Modify pointlist */
    if (!GUI_Context.AA_HiResEnable) {
      for (i=0; i< NumPoints; i++) {
        paPoint[i].x *= GUI_Context.AA_Factor;
        paPoint[i].y *= GUI_Context.AA_Factor;
      }
    }
    GUI_FillPolygon(paPoint, NumPoints, x * PosFactor, y * PosFactor);
    /* Restore pointlist */
    if (!GUI_Context.AA_HiResEnable) {
      for (i=0; i< NumPoints; i++) {
        paPoint[i].x /= GUI_Context.AA_Factor;
        paPoint[i].y /= GUI_Context.AA_Factor;
      }
    }
    /* Cleanup */
  }
  GUI_AA_Exit();
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAPoly_C(void);
  void GUIAAPoly_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
