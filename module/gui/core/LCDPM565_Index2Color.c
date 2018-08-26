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
File        : LCDPM565_Index2Color.c
Purpose     : Color conversion routines
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */


/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 565, 65536 colors, RRRRRGGGGGGBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Index2Color_M565
*/

U32 LCD_Index2Color_M565(U16 c) {
	return (((c&0x001F)*255/0x1F)<<16)| \
		   ((((c>>5)&0x003F)*255/0x3F)<<8)| \
		   (((c>>11)&0x001F)*255/0x1F);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
