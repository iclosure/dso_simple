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
File        : GUI_DrawLine.c
Purpose     : Implementation of line drawing routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ABS(v) ((v>0) ? v : -v)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SwapInt
*/
static void _SwapInt(int* pa, int* pb) {
  int t;
  t = *pa;
  *pa = *pb;
  *pb = t;
}

/*********************************************************************
*
*       Abs
*/
static int Abs(int v) {
  return ABS(v);
}

/*********************************************************************
*
*       trigonometric functions
*
*  NOTE:
*   All trigonometric functions are for internal usage only and
*   use the following conventions:
*
*      Angles: 4096 <==> 360?
*
**********************************************************************
*/

#if TRIG_45DEG != 512
#error Wrong define for this library !
#endif
/*********************************************************************
*
*       sin / cos (internal)
*
*  Angle : 90/1024?
*  Data  : 1/1024
*/
static const U16 aSin[] = {
	0,       /*  0/16 *90?*/
	100,     /*  1/16 *90?*/
	200,     /*  2/16 *90?*/
	297,     /*  3/16 *90?*/
	392,     /*  4/16 *90?*/
	483,     /*  5/16 *90?*/
	569,     /*  6/16 *90?*/
	650,     /*  7/16 *90?*/
	724,     /*  8/16 *90?*/
	792,     /*  9/16 *90?*/
	851,     /* 10/16 *90?*/
	903,     /* 11/16 *90?*/
	946,     /* 12/16 *90?*/
	980,     /* 13/16 *90?*/
	1004,    /* 14/16 *90?*/
	1019,    /* 15/16 *90?*/
	1024     /* 16/16 *90?*/
};

/*********************************************************************
*
*       TRIG_sin
*/
/* angle :0 ~ 1024 */
int TRIG_sin(int angle) {
	
	char IsNeg =0;
	int i;
	U16 factor;
	U32 t;
	angle &= TRIG_360DEG_1;  /* reduce to 0-360 degrees */
	if (angle > TRIG_180DEG) {
		angle -= TRIG_180DEG;
		IsNeg =1;
	}
	if (angle > TRIG_90DEG)  /* between 90-180 */
		angle = TRIG_180DEG - angle;   /* use sine symetry */
	/* Now angle is reduced to 0?<= <= 90?*/
	i = angle>>6;
    factor = 64-(angle&63);
    t = aSin[i]*factor;
    if (factor != 64)
		t += aSin[i+1]*(64-factor);
	t = (t+32) >>6;   /* divide,incl. rounding */
	return (IsNeg) ? 0-t : t;
}

/*********************************************************************
*
*       TRIG_cos
*/
int TRIG_cos(int angle) {
	return TRIG_sin(angle+TRIG_90DEG);
}

/*******************************************************
*       FFT_sin [用户添加 只用于 void FFT(int x[], int m, int flag)]
*/
/* angle :0 ~ 1024/4 [that is 0 to pi/4] */
int FFT_sin(int angle) {
	int i;
	U16 factor;
	U32 t;

	i = angle>>6;
    factor = 64 - (angle&63);
    t = aSin[i]*factor;
    if (factor != 64)
		t += aSin[i+1]*(64-factor);
	return (t+32) >>6;   /* divide,incl. rounding [即四舍五入处理: t = t/64+0.5 = (t+32)>>6]*/
}

/*********************************************************************
*
*       atan() (internal)
*
*  Angle : 360/4096?
*/
const I16 aTan[] = {
  0,       /* atan(0/16) */
  41,      /* atan(1/16) */
  81,      /* atan(2/16) */
  121,     /* atan(3/16) */
  160,     /* atan(4/16) */
  197,     /* atan(5/16) */
  234,     /* atan(6/16) */
  269,     /* atan(7/16) */
  302,     /* atan(8/16) */
  334,     /* atan(9/16) */
  364,     /* atan(10/16) */
  393,     /* atan(11/16) */
  419,     /* atan(12/16) */
  445,     /* atan(13/16) */
  469,     /* atan(14/16) */
  491,     /* atan(15/16) */
  512      /* atan(1) = 45?= 512/1024 */
};

/*********************************************************************
*
*       _atan0_45
*
* Calculate arctan of q, where q is any where between 0 and 1024
*/
static int _atan0_45(int q) {
	int r, i, factor;
	/* Now angle is reduced to 0?<= <= 90?==>  0 <= <= 256*/
	/*q >>=2;    // make sure we do not exceed 16 bits in calculations
	i = q>>4;*/
	i = q>>6;
	factor = 16 - (q&15);
	r = aTan[i]*factor;
	if (factor != 15)
		r += aTan[i+1]*(16-factor);
	r = (r+8)>>4;   /* divide  incl. rounding */
	return r;
}

/*********************************************************************
*
*       _atan2
*/
static int _atan2(I32 x, I32 y) {
	U8 q = 0x00;
	int angle;
	/* first make sure we are in angle between 0 and 45?*/
	if (x<0) {
		q=0x01; x=-x;
	}
	if (y<0) {
		q<<=1; y=-y;
	}
	if (y>x) {
		int t = y;
		y=x; x=t;
		q<<=1;
	}
	y <<=10;
	y += x>>1;
	y /= x;
	angle = _atan0_45(y);
	if (q & 0x01)   /* x-reverse ?   */
		angle = TRIG_180DEG-angle;
	if (q & 0x02)   /* y-reverse ?   */
		angle = TRIG_360DEG-angle;
	if (q & 0x04)   /* y/x reverse ? */
		angle = TRIG_90DEG -angle;
	return angle;
}

/*********************************************************************
*
*       _SetLineColor
*/
static int _SetLineColor(int i) {
	switch (GUI_Context.LineStyle) {
	case GUI_LS_DASH:
		i = (i + 6) & 15; // that is i = (i + 6) % 16;
		return (i < 12);
	case GUI_LS_DOT:
		i &= 3; // that is i %= 4;
		return (i < 2);
	case GUI_LS_DASHDOT:
		i %= 20;
		if (i < 12)
			return 1;
		else if ((i >= 16) && (i < 18))
			return 1;
		return 0;
	case GUI_LS_DASHDOTDOT:
		i %= 24;
		if (i < 12)
			return 1;
		else if ((i >= 16) && (i < 18))
			return 1;
		else if ((i >= 20) && (i < 22))
			return 1;
		else
			return 0;
	}

	return 0;
}

/*********************************************************************
*
*       _CalcOrto
*/

static void _CalcOrto(int xDiff, int yDiff, I32 r, int*px, int*py) {
  I32 x,y;
  int Angle = _atan2(xDiff, yDiff);
  Angle += TRIG_90DEG;
  x = ( r*(I32)TRIG_cos(Angle));
  y = ( r*(I32)TRIG_sin(Angle));
  x = (x<0) ? -((-x+512)>>10) : ((x+512)>>10);
  y = (y<0) ? -((-y+512)>>10) : ((y+512)>>10);
  *px = x;
  *py = y;
}

/*********************************************************************
*
*       _DrawLineEnd
*/
static void _DrawLineEnd(int x0, int y0) {
  switch (GUI_Context.PenShape) {
  case GUI_PS_ROUND:
    GUI_DrawPoint(x0,y0);
    break;
  case GUI_PS_FLAT:
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_DrawLine1Ex
*/
void GL_DrawLine1Ex(int x0, int y0, int x1, int y1, unsigned * pPixelCnt) {
  int xdiff = x1 - x0;
  int ydiff = y1 - y0;
  int xdiffby2;
  int i;
  char XYSwapped = 0;
  int Dir;
  int PixelCnt = * pPixelCnt;
/* check if no line */
  if (!(xdiff | ydiff)) {
    GUI_DrawPoint(x0, y0);
    return;
  }
/* check if we swap x and y for calculation */
  if (Abs(xdiff) < Abs(ydiff)) {
    _SwapInt(&xdiff, &ydiff);
    _SwapInt(&x0, &y0);
    _SwapInt(&x1, &y1);
    XYSwapped = 1;
  }
/* make sure line direction is positive */
  if (xdiff != Abs(xdiff)) {
    xdiff = -xdiff;
    ydiff = -ydiff;
    _SwapInt(&x0, &x1);
    _SwapInt(&y0, &y1);
    Dir = -1;
  } else {
    Dir = 1;
  }
/* Draw horizontal or vertical line if possible */
  if (ydiff == 0) {
    if (XYSwapped) {
      if (GUI_Context.LineStyle == GUI_LS_SOLID) {
        LCD_DrawVLine(y0, x0, x1);
      } else {
        for (i = 0; i <= xdiff; i++) {
          if (!_SetLineColor(PixelCnt++)) {
            LCD_HL_DrawPixel(y0, x0 + i);
          }
        }
        *pPixelCnt = PixelCnt - 1;
      }
    } else {
      if (GUI_Context.LineStyle == GUI_LS_SOLID) {
        LCD_HL_DrawHLine(y0, x0, x1);
      } else {
        for (i = 0; i <= xdiff; i++) {
          if (!_SetLineColor(PixelCnt++)) {
            LCD_HL_DrawPixel(x0 + i, y0);
          }
        }
        *pPixelCnt = PixelCnt - 1;
      }
    }
    return;
  }
  xdiffby2 = xdiff >>1;
  if (ydiff < 0) {
    xdiffby2 = -xdiffby2;
  }
/* Draw pixel by pixel solid*/
  if (GUI_Context.LineStyle == GUI_LS_SOLID) {
    for (i = 0; i <= xdiff; i++) {
      I32 l = ((I32)ydiff) * i + xdiffby2;
      int y = (ABS(l) < 32767) ? (y0 + ((int)l) / xdiff) : (y0 + l / xdiff);
      if (!XYSwapped) {
        LCD_HL_DrawPixel(x0+ i , y);
      } else {
        LCD_HL_DrawPixel(y, x0 + i);
      }
    }
/* Draw pixel by pixel with fill style */
  } else {
    if (Dir < 0) {
      *pPixelCnt += xdiff;
    }
    for (i = 0; i <= xdiff; i++) {
      long l = ((long)ydiff) * i + xdiffby2;
      int y = (ABS(l) < 32767) ? (y0 + ((int)l) / xdiff) : (y0 + l / xdiff);
      if (!_SetLineColor((*pPixelCnt) += Dir)) {
        if (!XYSwapped) {
          LCD_HL_DrawPixel(x0 + i, y);
        } else {
          LCD_HL_DrawPixel(y, x0 + i);
        }
      }
    }
    if (Dir < 0) {
      *pPixelCnt += xdiff;
    }
    *pPixelCnt -= Dir;
  }
}

/*********************************************************************
*
*       GL_DrawLine1
*/
void GL_DrawLine1(int x0, int y0, int x1, int y1) {
  unsigned PixelCnt;
  PixelCnt = 0;
  GL_DrawLine1Ex(x0, y0, x1, y1, &PixelCnt);
}

/*********************************************************************
*
*       GL_DrawLineEx
*/
void GL_DrawLineEx(int x0, int y0, int x1, int y1, unsigned * pPixelCnt) {
  if (GUI_Context.PenSize ==1) {
    GL_DrawLine1Ex(x0,y0,x1,y1,pPixelCnt);
  } else {
    int xdiff, ydiff;
    xdiff = x0-x1;
    ydiff = y0-y1;
    if (xdiff | ydiff) {
      GUI_POINT Poly[4];
      int xOff, yOff;
      int xOffP, yOffP, xOffM, yOffM;
      _CalcOrto(x0-x1,y0-y1, (I32)(GUI_Context.PenSize-1), &xOff, &yOff);
  /* Do rounding for offsets */
      if (xOff >0) {
        xOffP = (xOff+1) >>1;
        xOffM =  xOff   >>1;
      } else {
        xOffP =   xOff>>1;
        xOffM =  (xOff-1)   >>1;
      }
      if (yOff >0) {
        yOffP = (yOff+1)>>1;
        yOffM =  yOff   >>1;
      } else {
        yOffP =   yOff>>1;
        yOffM =  (yOff-1)   >>1;
      }
      Poly[0].x = x0+xOffP;
      Poly[0].y = y0+yOffP;
      Poly[1].x = x0-xOffM;
      Poly[1].y = y0-yOffM;
      Poly[2].x = x1-xOffM;
      Poly[2].y = y1-yOffM;
      Poly[3].x = x1+xOffP;
      Poly[3].y = y1+yOffP;
      GUI_FillPolygon(&Poly[0], 4, 0,0);
      _DrawLineEnd(x0,y0);
      _DrawLineEnd(x1,y1);
    }
  }
}

/*********************************************************************
*
*       GUI_DrawLine
*/
void GUI_DrawLine(int x0, int y0, int x1, int y1) {
  unsigned PixelCnt = 0;
  GL_DrawLineEx(x0, y0, x1, y1, &PixelCnt);
}

/*********************************************************************
*
*       Draw Line to group
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawLineRel
*/
void GUI_DrawLineRel(int dx, int dy) {
  GUI_DrawLine (GUI_Context.DrawPosX,    GUI_Context.DrawPosY,
               GUI_Context.DrawPosX+dx, GUI_Context.DrawPosY+dy);
  GUI_MoveRel(dx,dy);
}

/*********************************************************************
*
*       GL_DrawLineToEx
*/
void GL_DrawLineToEx(int x, int y, unsigned * pPixelCnt) {
  GL_DrawLineEx(GUI_Context.DrawPosX, GUI_Context.DrawPosY, x, y, pPixelCnt);
  GUI_Context.DrawPosX = x;
  GUI_Context.DrawPosY = y;
}

/*********************************************************************
*
*       GL_DrawLineTo
*/
void GL_DrawLineTo(int x, int y) {
  unsigned PixelCnt = 0;
  GL_DrawLineToEx(x, y, &PixelCnt);
}

/*********************************************************************
*
*       GUI_DrawLineTo
*/
void GUI_DrawLineTo(int x, int y) {
	unsigned PixelCnt = 0;
	GL_DrawLineEx(GUI_Context.DrawPosX, GUI_Context.DrawPosY, x, y, &PixelCnt);
	GUI_MoveTo(x,y);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
