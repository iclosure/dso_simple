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
File        : GUI_Goto.c
Purpose     : Implementation of GUI_Goto... routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include <string.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GotoY
*/
char GUI_GotoY(int y) {
	GUI_Context.DispPosY = y;
	return 0;
}

/*********************************************************************
*
*       GUI_GotoX
*/
char GUI_GotoX(int x) {
	GUI_Context.DispPosX = x;
	return 0;
}

/*********************************************************************
*
*       GUI_GotoXY
*/
char GUI_GotoXY(int x, int y) {
	GUI_Context.DispPosX = x;
	GUI_Context.DispPosY = y;
	return 0;
}

/*********************************************************************
*
*       GUI_AddX
*/
char GUI_AddX(int dx) {
	GUI_Context.DispPosX += dx;
	return 0;
}
/*********************************************************************
*
*       GUI_AddY
*/
char GUI_AddY(int dy) {
	GUI_Context.DispPosY += dy;
	return 0;
}
/*********************************************************************
*
*       GUI_AddXY
*/
char GUI_AddXY(int dx, int dy) {
	GUI_Context.DispPosX += dx;
	GUI_Context.DispPosY += dy;
	return 0;
}
/*************************** End of file ****************************/

