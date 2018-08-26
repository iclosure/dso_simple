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
File        : LCD_Protected.h
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef LCD_INTERN_H
#define LCD_INTERN_H

#include "LCD.h"

/*********************************************************************
*
*      Data types
*
**********************************************************************
*/

typedef struct {
  int              NumEntries; 
  const LCD_COLOR* pPalEntries; 
} LCD_PHYSPALETTE; 

/*********************************************************************
*
*      Data
*
**********************************************************************
*/
extern GUI_CONST_STORAGE U8 LCD_aMirror[256];


/********************************************************
*
*     Color conversion routines (used internally only !
*
*********************************************************
*/
U32 LCD_Index2Color_M565(U16 Index);
/*********************************************************************
*
*              Declarations for LCD_L0_
*
**********************************************************************

  Prefixes are as follows:
  LCD_L0_xxx       ... Driver for first  LCD
  LCD_L0_MAG_xxx   ... Driver for first  LCD, magnification level (calling LCD_L0_xxx after magnification)
  LCD_L0_DELTA_xxx ... Driver for first  LCD, delta mode

*/

//unsigned int LCDD_Color2Index       (LCD_COLOR Color);
//LCD_COLOR    LCDD_Index2Color       (int Index);
void         LCD_DrawHLine            (int y,  int x0, int x1);
//void         LCDD_MAG_DrawHLine     (int x0, int y0,  int x1);
//void         LCDD_DELTA_DrawHLine   (int x0, int y0,  int x1); 
void         LCD_DrawVLine            (int x,  int y0, int y1);
//void         LCDD_MAG_DrawVLine     (int x,  int y0, int y1);
//void         LCDD_DELTA_DrawVLine   (int x,  int y0, int y1);
void         LCD_FillRect             (int x0, int y0, int x1, int y1);
//void         LCDD_MAG_FillRect      (int x0, int y0, int x1, int y1);
//void         LCDD_DELTA_FillRect    (int x0, int y0, int x1, int y1);
unsigned int LCD_GetPixelIndex        (int x,  int y);
//unsigned int LCD_MAG_GetPixelIndex    (int x,  int y);
//unsigned int LCD_DELTA_GetPixelIndex  (int x,  int y);
void         LCD_GetRect              (LCD_RECT * pRect);
void         LCD_SetPixelIndex        (int x,  int y, int ColorIndex);
//void         LCD_MAG_SetPixelIndex    (int x,  int y, int ColorIndex);
//void         LCD_DELTA_SetPixelIndex  (int x,  int y, int ColorIndex);
void         LCD_XorPixel             (int x,  int y);
//void         LCD_DELTA_XorPixel       (int x,  int y);
int          LCD_Init                 (void);
//int          LCD_MAG_Init             (void);
//int          LCD_DELTA_Init           (void);
//void         LCD_On                   (void);
//void         LCD_Off                  (void);

void LCD_ReInit       (void); /* Reinitialize LCD using config-paramters */
void LCD_Refresh      (void); /* Refresh entire LCD */
                                 /* Refresh LCD partially. Could be one line, depends on what
                                    the LCD controller can handle efficiently */
void LCD_SetOrg       (int x, int y);


#endif /* LCD_INTERN_H */



/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
