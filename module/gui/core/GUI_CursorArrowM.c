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
File        : GUI_CursorArrowM.C
Purpose     : Defines the arrow cursor, medium
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"

GUI_CONST_STORAGE unsigned char GUI_Pixels_ArrowM[60] = {
	0x40, 0x00, 0x00,
	0x50, 0x00, 0x00,
	0x64, 0x00, 0x00,
	0x69, 0x00, 0x00,
	0x6A, 0x40, 0x00,
	0x6A, 0x90, 0x00,
	0x6A, 0xA4, 0x00,
	0x6A, 0xA9, 0x00,
	0x6A, 0xAA, 0x40,
	0x6A, 0xAA, 0x90,
	0x6A, 0xAA, 0xA4,
	0x6A, 0xA9, 0x55,
	0x69, 0xA9, 0x00,
	0x64, 0x6A, 0x40,
	0x50, 0x6A, 0x40,
	0x40, 0x1A, 0x90,
	0x00, 0x1A, 0x90,
	0x00, 0x06, 0xA4,
	0x00, 0x06, 0xA4,
	0x00, 0x01, 0x50
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_CONST_STORAGE GUI_COLOR _aColor[] = {
	_24TO565(  0,  0,255), 
	_24TO565(  0,  0,  0), 
	_24TO565(255,255,255)
};

GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPal = {
	3,	/* number of entries */
	1, 	/* Has transparency */
	&_aColor[0]
};

GUI_CONST_STORAGE GUI_BITMAP GUI_BitmapArrowM = {
	12,                  /* XSize */
	20,                  /* YSize */
	3,                   /* BytesPerLine */
	2,                   /* BitsPerPixel */
	GUI_Pixels_ArrowM,   /* Pointer to picture data (indices) */
	&GUI_CursorPal       /* Pointer to palette */
};

GUI_CONST_STORAGE GUI_CURSOR GUI_CursorArrowM = {
	&GUI_BitmapArrowM, 0, 0
};

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
