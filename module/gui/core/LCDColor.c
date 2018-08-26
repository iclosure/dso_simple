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
File        : LCDColor.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#define LCDCOLOR_C

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "LCD_Private.h"      /* inter modul definitions & Config */

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/

#ifndef  LCD_SIZEOF_COLORCACHE
  #define LCD_SIZEOF_COLORCACHE 0
#endif

#if  LCD_SIZEOF_COLORCACHE
  static  const LCD_LOGPALETTE * pLogPalCache;
#endif

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_GetpPalConvTableUncached
*/
LCD_PIXELINDEX* LCD_GetpPalConvTableUncached(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal) {
  if (pLogPal == NULL) {
    return NULL;
  }
  if (!pLogPal->pPalEntries) {
    return NULL;
  }
  /* Check if sufficient space is available */
  if (pLogPal->NumEntries > LCD_MAX_LOG_COLORS) {
    return NULL;
  }
  /* Build conversion table */
  {
    int i;
    int NumEntries = pLogPal->NumEntries;
    const LCD_COLOR GUI_UNI_PTR * pPalEntry = &pLogPal->pPalEntries[0];
    for (i=0; i< NumEntries; i++) {
      LCD__aConvTable[i] = *(pPalEntry+i);
    }
  }
  return &LCD__aConvTable[0];
}

/*********************************************************************
*
*       LCD_GetpPalConvTable
*/
LCD_PIXELINDEX* LCD_GetpPalConvTable(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal) {
/* Check cache */
  #if  LCD_SIZEOF_COLORCACHE
    if (pLogPalCache == pLogPal) {
      return &LCD__aConvTable[0];
    }
    pLogPalCache = pLogPal;
  #endif
  return LCD_GetpPalConvTableUncached(pLogPal);
}


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
