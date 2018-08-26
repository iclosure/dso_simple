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
File        : LCD.h
Purpose     : Declares LCD interface functions
----------------------------------------------------------------------
*/

#ifndef LCD_H
#define LCD_H

#include "GUI_ConfDefaults.h" /* Used for GUI_UNI_PTR */
#include "LCD_ConfDefaults.h" /* Used for GUI_UNI_PTR */
#include "LCDConf.h"
#include "integer.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*
  ********************************************************************
  *                                                                  *
  *                   Basic type defines                             *
  *                                                                  *
  ********************************************************************

The follwing are defines for types used in the LCD-driver and the
GUI layers on top of that. Since "C" does not provide data types of
fixed length which are identical on all platforms, this is done here.
For most 16/32 controllers, the settings will work fine. However, if
you have similar defines in other sections of your program, you might
want to change or relocate these defines, e.g. in a TYPE.h file.
*/

#include "utypes.h"

/*
  ********************************************************************
  *                                                                  *
  *               Settings for windows simulation                    *
  *                                                                  *
  ********************************************************************

Some settings in the configuration may conflict with the values required
in the Simulation. This is why we ignore the target settings for data
types and use the correct settings for the simulation.
(U32 could be defined as long, which would yield a 64 bit type on
the PC)
*/

#ifdef WIN32
	// Visual Studio C 6++ ->
	#pragma warning( disable : 4244 )  // Disable warning messages in simulation
	#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
	#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
	#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
	// Visual Studio 2008 ->
	#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif     
	

/*
      *********************************
      *                               *
      *      Drawing modes            *
      *                               *
      *********************************
*/

#define LCD_DRAWMODE_NORMAL (0)
#define LCD_DRAWMODE_XOR    (1<<0)
#define LCD_DRAWMODE_TRANS  (1<<1)
#define LCD_DRAWMODE_REV    (1<<2)


 
/*      *************************************************************
        *                                                           *
        *                Typedefs                                   *
        *                                                           *
        *************************************************************
*/

typedef int LCD_DRAWMODE;
typedef U16 LCD_COLOR;

 
/********************************************************
*
*     Data structures
*
*********************************************************
*/

typedef struct { I16P x,y; } GUI_POINT;
typedef struct { I16 x0,y0,x1,y1; } LCD_RECT;

typedef struct {
  int              NumEntries; 
  char             HasTrans;         
  const LCD_COLOR GUI_UNI_PTR * pPalEntries; 
} LCD_LOGPALETTE; 

/* This is used for the simulation only ! */
typedef struct {
  int x,y;
  unsigned char KeyStat;
} LCD_tMouseState;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// ÐéÄâÆÁÄ»[·ÀÖ¹ÆÁÄ»ÉÁË¸]
extern U16      LCD0[LCD_YSIZE*2][LCD_XSIZE];
extern U16    (*LCD1)[LCD_XSIZE];
extern U16    (*LCD2)[LCD_XSIZE];
extern U16    (*LCD)[LCD_XSIZE]; // µ±Ç°Ö¸¶¨µÄÐéÄâÆÁ
//extern U32		LCD24[LCD_YSIZE][LCD_XSIZE];
/*****************************************************************
 *   defined
 */
#define GETPIXEL(x,y)                  LCD[y][x]
#define SETPIXEL(x,y, c)               LCD[y][x]= c
#define XORPIXEL(x,y)                  LCD[y][x]= LCD_NUM_COLORS-1-GETPIXEL(x,y)


void LCD_SelectLCD(int n);
int  LCD_GetLCDIndex(void);
void LCD_ClearRect(LCD_RECT rect);
void lcd_displayRect(LCD_RECT rect,int x0,int y0);
void lcd_display(void);
//void lcd_display24(void);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

/*********************************************************************
*
*      LCDDEV function table
*
**********************************************************************

  Below the routines which need to in an LCDDEV routine table are
  defined. All of these routines have to be in the low-level driver
  (LCD_L0) or in the memory device which can be used to replace the
  driver.
  The one exception to this is the SetClipRect routine, which would
  be identical for all drivers and is therefor contained in the
  level above (LCD).
*/
typedef void tLCDDEV_DrawBitmap   (int x0, int y0, int xsize, int ysize,
								   int BitsPerPixel, int BytesPerLine,
								   const U8 GUI_UNI_PTR * pData, int Diff,
								   const void* pTrans);   /* Really LCD_PIXELINDEX, but is void to avoid compiler warnings*/

typedef void         tLCDDEV_DrawHLine    (int y, int x0, int x1);
typedef void         tLCDDEV_DrawVLine    (int x, int y0, int y1);
typedef void         tLCDDEV_FillRect     (int x0, int y0, int x1, int y1);
typedef unsigned int tLCDDEV_GetPixelIndex(int x, int y);
typedef void         tLCDDEV_SetPixelIndex(int x, int y, int ColorIndex);
typedef void         tLCDDEV_XorPixel     (int x, int y);
typedef void         tLCDDEV_FillPolygon  (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_FillPolygonAA(const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_GetRect      (LCD_RECT*pRect);
typedef int          tLCDDEV_Init         (void);

/*********************************************************************
*
*     Memory device API tables
*/

typedef struct tLCDDEV_APIList_struct {
  tLCDDEV_DrawBitmap*         pfDrawBitmap;
  tLCDDEV_DrawHLine*          pfDrawHLine;
  tLCDDEV_DrawVLine*          pfDrawVLine;
  tLCDDEV_FillRect*           pfFillRect;
  tLCDDEV_GetPixelIndex*      pfGetPixelIndex;
  tLCDDEV_GetRect*            pfGetRect;
  tLCDDEV_SetPixelIndex*      pfSetPixelIndex;
  tLCDDEV_XorPixel*           pfXorPixel;
} tLCDDEV_APIList, *ptLCDDEV_APIList;

/*      *************************************************************
        *                                                           *
        *                   Defines                                 *
        *                                                           *
        *    for device capabilities                                *
        *                                                           *
        *************************************************************

The following is the list of device capabilities which can, but do
not have to be implemented in the driver. This way the driver can be
enhanced in the future without affecting the driver interface,
keeping older drivers compatible.
More DevCaps can always be added in the future, as older drivers
are guaranteed to return 0 for all unimplemented features or queries.

The values below define the legal parameters to the LCD_GetDeviceCaps
and the LCD_GetpCapFunc routines.
*/

#define LCD_DEVCAP_NUMCOLORS    0x0     /* Quest number of colors
                                           which LCD can display */
#define LCD_DEVCAP_XSIZE        0x1     /* Quest horiz. res. of display */
#define LCD_DEVCAP_YSIZE        0x2     /* Quest vert. res. of display */
#define LCD_DEVCAP_VXSIZE       0x3     /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_VYSIZE       0x4     /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_XORG         0x5     /* X-origin ... usually 0 */
#define LCD_DEVCAP_YORG         0x6     /* Y-origin ... usually 0 */
#define LCD_DEVCAP_CONTROLLER   0x7     /* LCD Controller (Numerical) */
#define LCD_DEVCAP_BITSPERPIXEL 0x8     /* Bits per pixel ... 1/2/4/8 */
#define LCD_DEVCAP_NUMPAGES     0x10    /* Quest number of pages of display */

#define LCD_DEVCAP_COLOR        0x1000  /* Quest Color[0]
                                0x1001     Quest Color[1]
                                0x1002     Quest Color[2]
                                         ...                    */
 /* The next 4095 entries are reserved so up to 4096 colors
    can be queried          ...*/

int LCD_GetXSize(void);
int LCD_GetYSize(void);
int LCD_GetVXSize(void);
int LCD_GetVYSize(void);
U32 LCD_GetNumColors(void);
int LCD_GetBitsPerPixel(void);
int LCD_GetFixedPalette(void);
int LCD_GetXMag(void);
int LCD_GetYMag(void);

#define LCD_GET_XSIZE()        LCD_GetXSize()
#define LCD_GET_YSIZE()        LCD_GetYSize()
#define LCD_GET_VXSIZE()       LCD_GetVXSize()
#define LCD_GET_VYSIZE()       LCD_GetVYSize()
#define LCD_GET_BITSPERPIXEL() LCD_GetBitsPerPixel()

#define LCD_DEVFUNC_READRECT  0x1     /* Request of a function pointer for reading a rectangular display area */


/*********************************************************************
*
*      LCD_CLIP function table
*
**********************************************************************
*/
typedef void  tLCD_HL_DrawHLine(int y,  int x0, int x1);
typedef void  tLCD_HL_DrawPixel(int x0, int y0);

typedef struct {
  tLCD_HL_DrawHLine*          pfDrawHLine;
  tLCD_HL_DrawPixel*          pfDrawPixel;
} tLCD_HL_APIList;

void LCD_DrawHLine(int y,  int x0, int x1);
void LCD_DrawPixel(int x0, int y0);
void LCD_DrawVLine(int x,  int y0, int y1);



/*********************************************************************
*
*              Declarations for LCD_
*
**********************************************************************
*/

void LCD_SetClipRectEx(const LCD_RECT* pRect);
void LCD_SetClipRectMax(void);

/* Get device capabilities (0 if not supported) */
I32  LCD_GetDevCap(int Index);

/* Initialize LCD using config-paramters */
int LCDDEV_Init(void);

void LCD_SetBkColor   (LCD_COLOR Color); /* Set background color */
void LCD_SetColor     (LCD_COLOR Color); /* Set foreground color */
void LCD_SetPixelIndex(int x, int y, int ColorIndex);
void LCD_XorPixel     (int x, int y);

/* Palette routines (Not available on all drivers) */
void LCD_InitLUT(void);

/* Decompressors */
LCD_DRAWMODE LCD_SetDrawMode(LCD_DRAWMODE dm);
void LCD_SetColorIndex      (int Index);
void LCD_SetBkColorIndex    (int Index);
void LCD_FillRect           (int x0, int y0, int x1, int y1);
typedef void tLCD_SetPixelAA(int x, int y, U8 Intens);

void LCD_SetPixelAA        (int x, int y, U8 Intens);
void LCD_SetPixelAA_NoTrans(int x, int y, U8 Intens);

LCD_COLOR    LCD_AA_MixColors   (LCD_COLOR Color, LCD_COLOR BkColor, U8 Intens);
LCD_COLOR    LCD_MixColors256   (LCD_COLOR Color, LCD_COLOR BkColor, unsigned Intens);
#define LCD_GetPixelColor(x,y)  LCD_GetPixelIndex(x,y)  /* Get RGB color of pixel */
unsigned int LCD_GetPixelIndex  (int x, int y);
int          LCD_GetBkColorIndex(void);
int          LCD_GetColorIndex  (void);
void         LCD_GetRect(LCD_RECT *pRect);
/*********************************************************************
*
*       Optional support for rotatation
*
**********************************************************************
*/

#if GUI_SUPPORT_ROTATION

typedef void tLCD_DrawBitmap(int x0, int y0, int xsize, int ysize,
                             int xMul, int yMul, int BitsPerPixel, int BytesPerLine,
                             const U8 GUI_UNI_PTR * pPixel, const void * pTrans);
typedef void tRect2TextRect (LCD_RECT * pRect);

struct tLCD_APIList_struct {
  tLCD_DrawBitmap   * pfDrawBitmap;
  tRect2TextRect    * pfRect2TextRect;
};

typedef struct tLCD_APIList_struct tLCD_APIList;

extern tLCD_APIList LCD_APIListCCW;
extern tLCD_APIList LCD_APIListCW;
extern tLCD_APIList LCD_APIList180;

#define GUI_ROTATION   tLCD_APIList
#define GUI_ROTATE_CCW &LCD_APIListCCW
#define GUI_ROTATE_CW  &LCD_APIListCW
#define GUI_ROTATE_180 &LCD_APIList180
#define GUI_ROTATE_0   0
#endif


/*      *************************************************************
        *                                                           *
        *      LCD  publics not used by GUI                         *
        *                                                           *
        *************************************************************
  

The following functions can, but do not have to be defined in the LCD driver
as they are not used by the GUI level.

*/

#define LCD_ReInit      LCD_L0_ReInit

/*      *************************************************************
        *                                                           *
        *      LCD  imports                                         *
        *                  (for routines in LCDColor)               *
        *                                                           *
        *************************************************************
*/

#if defined(__cplusplus)
  }
#endif

#endif /* LCD_H */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
