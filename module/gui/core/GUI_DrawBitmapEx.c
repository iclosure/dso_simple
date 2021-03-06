/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_DrawBitmapEx.c
Purpose     : Draws a bitmap with free magnification
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"
#include "stdlib.h"

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawBitmapEx
*/
void GUI_DrawBitmapEx(const GUI_BITMAP GUI_UNI_PTR * pBitmap, int x0, int y0,
                            int xCenter, int yCenter, int xMag, int yMag) {
  LCD_PIXELINDEX Index, IndexPrev = 0;
  LCD_COLOR Color;
  int x, y, xi, yi, xSize, ySize, xAct, xStart, xMagAbs, xiMag, yMin, yMax, yEnd, yPrev, yStep;
  char Cached, HasTrans = 0;
  /* Use clipping rect to reduce calculation */
  yMin = GUI_Context.ClipRect.y0;
  yMax = GUI_Context.ClipRect.y1;
  /* Init some values */
  xSize    = pBitmap->XSize;
  ySize    = pBitmap->YSize;
  xMagAbs  = ((xMag < 0) ? -xMag : xMag);
  x0      -= (I32)((xMag < 0) ? xSize - xCenter - 1 : xCenter) * (I32)(xMagAbs) / (I32)(1000);
  yEnd     = y0 + GUI__DivideRound32(((I32)(-yCenter) * (I32)(yMag)), 1000);
  yPrev    = yEnd + 1;
  yStep = (yMag < 0) ? -1 : 1;
  if (pBitmap->pPal) {
    if (pBitmap->pPal->HasTrans) {
      HasTrans = 1;
    }
  }
  for (yi = 0; yi < ySize; yi++) {
    y = yEnd;
    yEnd = y0 + GUI__DivideRound32(((I32)(yi + 1 - yCenter) * (I32)(yMag)), 1000);
    if (y != yPrev) {
      yPrev = y;
      do {
        if ((y >= yMin) && (y <= yMax)) {
          xStart = -1;
          x      =  0;
          xiMag  =  0;
          Cached =  0;
          for (xi = 0; xi < xSize; xi++) {
            xiMag += xMagAbs;
            if (xiMag >= 1000) {
              xAct  = (xMag > 0) ? xi : xSize - xi - 1;
              Index = GUI_GetBitmapPixelIndex(pBitmap, xAct, yi);
              if (Index != IndexPrev || xStart == -1) {
                if ((Index == 0) && HasTrans) {
                  /* Transparent color ... clear cache */
                  if (Cached) {
                    LCD_DrawHLine(y, x0 + xStart, x0 + x - 1);
                    Cached = 0;
                  }
                } else {
                  /* Another color ... draw contents of cache */
                  if (Cached && xStart != -1) {
                    LCD_DrawHLine(y, x0 + xStart, x0 + x - 1);
                  }
                  xStart    = x;
                  Cached    = 1;
                  if (pBitmap->pPal->pPalEntries)
					  Color = pBitmap->pPal->pPalEntries[Index];
				  else
					  Color = Index;
                  LCD_SetColorIndex(Color);
                }
                IndexPrev = Index;
              }
              do {
                x++;
                xiMag -= 1000;
              } while (xiMag >= 1000);
            }
          }
          /* Clear cache */
          if (Cached) {
            LCD_DrawHLine(y, x0 + xStart, x0 + x - 1);
          }
        }
        y += yStep;
      } while ((yMag < 0) ? (y > yEnd) : (y < yEnd));
    }
  }
}


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
