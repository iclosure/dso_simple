/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : GUI_DrawBitmap.C
Purpose     : Implementation of GUI_DrawBitmap
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawBitmap
*
* Purpose:
*  Translates the external bitmap format into an internal
*  format. This turned out to be necessary as the internal
*  format is easier to create and more flexible for routines
*  that draw text-bitmaps.
*/
void GUI_DrawBitmap(const GUI_BITMAP GUI_UNI_PTR * pBitmap, int x0, int y0) {
  GUI_DRAWMODE PrevDraw;
  const GUI_LOGPALETTE GUI_UNI_PTR * pPal;
  pPal = pBitmap->pPal;
  PrevDraw = GUI_SetDrawMode(0);  /* No Get... at this point */
  GUI_SetDrawMode((pPal && pPal->HasTrans) ? (PrevDraw|GUI_DRAWMODE_TRANS) : PrevDraw &(~GUI_DRAWMODE_TRANS));
  if (pBitmap->pMethods) {
      pBitmap->pMethods->pfDraw(x0, y0, pBitmap->XSize ,pBitmap->YSize, (U8 const *)pBitmap->pData, pBitmap->pPal, 1, 1);
  } else {
	  const LCD_PIXELINDEX* pTrans;
	  pTrans = LCD_GetpPalConvTable(pBitmap->pPal);
	  if (!pTrans) {
		  pTrans = (pBitmap->BitsPerPixel != 1) ? NULL : &LCD_BKCOLORINDEX;
	  }
	  LCD_DrawBitmap( x0,y0
		  ,pBitmap->XSize ,pBitmap->YSize
		  ,1,1
		  ,pBitmap->BitsPerPixel
		  ,pBitmap->BytesPerLine
		  ,pBitmap->pData
		  ,pTrans);
  }
  GUI_SetDrawMode(PrevDraw);
}

/*********************************************************************
 *
 *       GUI_ClearBitmap
 *   [用户添加]: 清除一副指定位置的Bitmap
 *   参数说明: FillColor-- 清除图像时用的颜色, 如果Bitmap像素位宽为1则采用纯色清除图片,否则用FillColor
 */
void GUI_ClearBitmap(const GUI_BITMAP GUI_UNI_PTR * pBitmap, int x0, int y0, U16 FillColor) {
	U16 oldcolor= GUI_GetColor();
	if(pBitmap->BitsPerPixel == 1)
		FillColor= pBitmap->pPal->pPalEntries[0];
	GUI_SetColor(FillColor);
	GUI_FillRect(x0,y0, x0+pBitmap->XSize-1, y0+pBitmap->YSize-1);
	GUI_SetColor(oldcolor);
}
/*************************** End of file ****************************/
