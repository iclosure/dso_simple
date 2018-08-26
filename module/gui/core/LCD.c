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
File        : LCD.c
Purpose     : Link between GUI and LCD_L0
              Performs most of the clipping.
---------------------------END-OF-HEADER------------------------------
*/

#define LCD_C

#include <stdio.h>
#include "GUI_Private.h"
#include "LCD_Private.h"



// 虚拟屏幕[防止屏幕闪烁]
U16      LCD0[LCD_YSIZE*2][LCD_XSIZE];
U16    (*LCD1)[LCD_XSIZE]= & LCD0[0];
U16    (*LCD2)[LCD_XSIZE]= & LCD0[LCD_YSIZE];
U16    (*LCD)[LCD_XSIZE]; // 当前指定的虚拟屏
//U32		 LCD24[LCD_YSIZE][LCD_XSIZE]; // 24bpp真彩屏
static int  ActivateLCD;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define RETURN_IF_Y_OUT() \
  if (y < GUI_Context.ClipRect.y0) return;             \
  if (y > GUI_Context.ClipRect.y1) return;

#define RETURN_IF_X_OUT() \
  if (x < GUI_Context.ClipRect.x0) return;             \
  if (x > GUI_Context.ClipRect.x1) return;

#define CLIP_X() \
  if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
  if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }

#define CLIP_Y() \
  if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
  if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }


#define PIXELINDEX WORD


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetColorIndex
*/
static int _GetColorIndex(int i)  /* i is 0 or 1 */ {
  return  (GUI_Context.DrawMode & LCD_DRAWMODE_REV) ? i-1 : i;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_SetColorIndex
*/
void LCD_SetColorIndex(int Index) {
  LCD_ACOLORINDEX[_GetColorIndex(1)] = Index;
}

/*********************************************************************
*
*       LCD_SetBkColorIndex
*/
void LCD_SetBkColorIndex(int Index) {
  LCD_ACOLORINDEX[_GetColorIndex(0)] = Index;
}

/*********************************************************************
*
*       LCD_SetDrawMode
*/
LCD_DRAWMODE LCD_SetDrawMode(LCD_DRAWMODE dm) {
  LCD_DRAWMODE OldDM = GUI_Context.DrawMode;
  if ((GUI_Context.DrawMode^dm) & LCD_DRAWMODE_REV) {
    LCD_PIXELINDEX temp = LCD_BKCOLORINDEX;
    LCD_BKCOLORINDEX    = LCD_COLORINDEX;
    LCD_COLORINDEX = temp;
  }
  GUI_Context.DrawMode = dm;
  return OldDM;
}


///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*********************************************************************
 *
 *                选择当前虚拟屏 [0--LCD0; 1--LCD1; 2--LCD2]
 */
void LCD_SelectLCD(int n) {
	if(n == 0) {
		LCD= LCD0;
		ActivateLCD= 0;
	} else if(n == 1) {
		LCD= LCD1;
		ActivateLCD= 1;
	} else if(n == 2) {
		LCD= LCD2;
		ActivateLCD= 2;
	} else {
		LCD= LCD1;
		ActivateLCD= 1;
	}
}

// 获取当前活动LCD序号
int LCD_GetLCDIndex(void) {
	return ActivateLCD;
}

// 以LCD_COLORINDEX色清除某矩形区域快
void LCD_ClearRect(GUI_RECT rect) {
	I16 y;
	GUI_DRAWMODE PrevDraw;
	PrevDraw = LCD_SetDrawMode(GUI_DRAWMODE_REV);
	for(y=rect.y0; y<=rect.y1; y++) 
		GUI__memset16(LCD[y]+rect.x0, LCD_COLORINDEX, rect.x1-rect.x0+1);
	LCD_SetDrawMode(PrevDraw);
}

void LCD_SetPixelIndex(int x, int y, int ColorIndex) {
	SETPIXEL(x,y, ColorIndex);
}

void LCD_XorPixel     (int x, int y) {
	XORPIXEL(x,y);
}

/*********************************************************************
*
*       LCD_DrawPixel
*/
void LCD_DrawPixel(int x, int y) {
	RETURN_IF_Y_OUT();
	RETURN_IF_X_OUT();
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		XORPIXEL(x,y);
	} else {
		SETPIXEL(x,y, LCD_COLORINDEX);
	}
}


/*********************************************************************
*
*       LCD_DrawHLine
*/
void LCD_DrawHLine(int y, int x0, int x1) {
	/* Perform clipping and check if there is something to do */
	RETURN_IF_Y_OUT();
	CLIP_X();
	if (x1<x0)
		return;
	/* Call driver to draw */
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		for (;x0 <= x1; x0++)
			XORPIXEL(x0, y);
	} else {
		GUI__memset16(LCD[y]+x0, LCD_COLORINDEX, (x1-x0+1));
	}
}

/*********************************************************************
*
*       LCD_DrawVLine
*/
void LCD_DrawVLine(int x, int y0, int y1) {
	/* Perform clipping and check if there is something to do */
	RETURN_IF_X_OUT();
	CLIP_Y();
	if (y1 < y0)
		return;
	/* draw vert line*/
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		while (y0 <= y1) {
			XORPIXEL(x, y0);
			y0++;
		}
	} else {
		while (y0 <= y1) {
			SETPIXEL(x, y0, LCD_COLORINDEX);
			y0++;
		}
	}
}

/*********************************************************************
*
*       LCD_FillRect
*/
void LCD_FillRect(int x0, int y0, int x1, int y1) {
	/* Perform clipping and check if there is something to do */
	CLIP_X();
	if (x1<x0)
		return;
	CLIP_Y();
	if (y1<y0)
		return;
	/* draw */
	for(; y0<=y1; y0++)
		GUI__memset16(LCD[y0]+x0, LCD_COLORINDEX, (x1-x0+1));
}


/*********************************************************************
 *
 *                     Bitmap 
 */

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0, Index1;
  Index0 = *(pTrans + 0);
  Index1 = *(pTrans + 1);
  x+=Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      SETPIXEL(x++,y, (*p & (0x80>>Diff)) ? Index1 : Index0);
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80>>Diff))
        SETPIXEL(x,y, Index1);
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    do {
  		if (*p & (0x80>>Diff)) {
        int Pixel = GETPIXEL(x,y);
        SETPIXEL(x,y, LCD_NUM_COLORS-1-Pixel);
      }
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
	}
}
///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void _DrawBitLine2BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          SETPIXEL(x++, y, PixelIndex);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          SETPIXEL(x++, y, Index);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            SETPIXEL(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            SETPIXEL(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine4BPP
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void _DrawBitLine4BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          SETPIXEL(x++, y, PixelIndex);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          SETPIXEL(x++, y, Index);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            SETPIXEL(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            SETPIXEL(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine16BPP
*/
#if (LCD_BITSPERPIXEL > 8)
static void _DrawBitLine16BPP(int x, int y, U16 const * p, int xsize) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    for (;xsize > 0; xsize--,x++,p++) {
      SETPIXEL(x, y, *p);
    }
  } else {   /* Handle transparent bitmap */
    for (; xsize > 0; xsize--, x++, p++) {
      pixel = *p;
      if (pixel) {
        SETPIXEL(x + 0, y, pixel);
      }
    }
  }
}
#endif


/*********************************************************************
*
*       LCDDEV_DrawBitmap
*/
void LCDDEV_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /*
     Use DrawBitLineXBPP
  */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
        _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #if (LCD_MAX_LOG_COLORS > 2)
    case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        //_DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       LCD_DrawBitmap
*/
void LCD_DrawBitmap(int x0, int y0, int xsize, int ysize, int xMul, int yMul,
                       int BitsPerPixel, int BytesPerLine,
                       const U8 GUI_UNI_PTR * pPixel, const LCD_PIXELINDEX* pTrans)
{
  U8  Data = 0;
  int x1, y1;
  /* Handle rotation if necessary */
  #if GUI_SUPPORT_ROTATION
  if (GUI_pLCD_APIList) {
    GUI_pLCD_APIList->pfDrawBitmap(x0, y0, xsize, ysize, xMul, yMul, BitsPerPixel, BytesPerLine, pPixel, pTrans);
    return;
  }
  #endif
  /* Handle the optional Y-magnification */
  y1 = y0 + ysize - 1;
  x1 = x0 + xsize - 1;
/*  Handle BITMAP without magnification */
  if ((xMul | yMul) == 1) {
    int Diff;
    /*  Clip y0 (top) */
    Diff = GUI_Context.ClipRect.y0 - y0;
    if (Diff > 0) {
      ysize -= Diff;
      if (ysize <= 0) {
		    return;
      }
      y0     = GUI_Context.ClipRect.y0;
      #if GUI_SUPPORT_LARGE_BITMAPS                       /* Required only for 16 bit CPUs if some bitmaps are >64kByte */
        pPixel += (U32)     Diff * (U32)     BytesPerLine;
      #else
        pPixel += (unsigned)Diff * (unsigned)BytesPerLine;
      #endif
    }
    /*  Clip y1 (bottom) */
    Diff = y1 - GUI_Context.ClipRect.y1;
    if (Diff > 0) {
      ysize -= Diff;
      if (ysize <= 0) {
		    return;
      }
    }
    /*        Clip right side    */
    Diff = x1 - GUI_Context.ClipRect.x1;
    if (Diff > 0) {
      xsize -= Diff;
    }
    /*        Clip left side ... (The difficult side ...)    */
    Diff = 0;
    if (x0 < GUI_Context.ClipRect.x0) {
		Diff = GUI_Context.ClipRect.x0 - x0;
		xsize -= Diff;
		switch (BitsPerPixel) {
		case 1:
  			pPixel+= (Diff>>3); x0 += (Diff>>3)<<3; Diff &=7;
			break;
		case 2:
	  		pPixel+= (Diff>>2); x0 += (Diff>>2)<<2; Diff &=3;
			break;
		case 4:
			pPixel+= (Diff>>1); x0 += (Diff>>1)<<1; Diff &=1;
			break;
		case 8:
			pPixel+= Diff;      x0 += Diff; Diff=0;
			break;
		case 16:
			pPixel+= (Diff<<1); x0 += Diff; Diff=0;
			break;
		}
    }
    if (xsize <=0)
		return;
    LCDDEV_DrawBitmap(x0,y0, xsize, ysize, BitsPerPixel, BytesPerLine, pPixel, Diff, pTrans);
  } else {
    /**** Handle BITMAP with magnification ***/
    int x,y;
    int yi;
    int Shift = 8-BitsPerPixel;
    for (y=y0, yi=0; yi<ysize; yi++, y+= yMul, pPixel+=BytesPerLine) {
      int yMax = y+yMul-1;
      /* Draw if within clip area (Optimization ... "if" is not required !) */
      if ((yMax >= GUI_Context.ClipRect.y0) && (y <= GUI_Context.ClipRect.y1)) {
        int BitsLeft =0;
        int xi;
        const U8 GUI_UNI_PTR * pDataLine = pPixel;
        for (x=x0, xi=0; xi<xsize; xi++, x+=xMul) {
          U8  Index;
          if (!BitsLeft) {
            Data = *pDataLine++;
            BitsLeft =8;
          }
          Index = Data>>Shift;
          Data    <<= BitsPerPixel;
          BitsLeft -= BitsPerPixel;
          if (Index || ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) ==0)) {
            LCD_PIXELINDEX  OldColor = LCD_COLORINDEX;
            if (pTrans) {
              LCD_COLORINDEX = *(pTrans+Index);
            } else {
              LCD_COLORINDEX = Index;
            }
            LCD_FillRect(x,y, x+xMul-1, yMax);
            LCD_COLORINDEX = OldColor;
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*       LCD_SetClipRectMax
*/
void LCD_SetClipRectMax(void) {
  LCD_GetRect(&GUI_Context.ClipRect);
}

/*********************************************************************
*
*       LCD_Init
*/
int LCD_Init(void) {
	int r = 0;
	LCD_SelectLCD(1);
	LCD_SetClipRectMax();
	r |= LCDDEV_Init();
#if (GUI_DEFAULT_BKCOLOR != GUI_INVALID_COLOR)
    /* Clear video memory */
    LCD_SetDrawMode(GUI_DRAWMODE_REV);
    LCD_FillRect(0,0, GUI_XMAX, GUI_YMAX);
    LCD_SetDrawMode(0);
#endif
    return r;
}


/*********************************************************************
*
*       LCD_SetBkColor
*/
void LCD_SetBkColor(GUI_COLOR color) {
	if (GUI_Context.BkColor != color) {
		GUI_Context.BkColor = color;
		LCD_SetBkColorIndex(color);
	}
}

/*********************************************************************
*
*       LCD_SetColor
*/
void LCD_SetColor(GUI_COLOR color) {
	if (GUI_Context.Color != color) {
		GUI_Context.Color = color;
		LCD_SetColorIndex(color);
	}
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
