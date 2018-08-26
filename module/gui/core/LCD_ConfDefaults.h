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
File        : LCD_ConfDefaults.h
Purpose     : Valid LCD configuration and defaults
----------------------------------------------------------------------
*/

#ifndef LCD_CONFIG_DEFAULTS_H
#define LCD_CONFIG_DEFAULTS_H

#include "LCDConf.h"            /* Configuration header file */
#include "GUI_ConfDefaults.h"   /* Needed for GUI_NUM_LAYERS */


#define LCD_NUM_COLORS (1UL<<LCD_BITSPERPIXEL)




/*********************************************************************
*
*      Map the defines for controller 0 to general defines
*
**********************************************************************
*/

/* Allow use of multiple physical lines for one logical line ...
   Used for delta-type LCDs, where value should be 2 */

#ifndef LCD_YMAG
  #define LCD_YMAG 1
#endif
#ifndef LCD_XMAG
  #define LCD_XMAG 1
#endif

#ifndef LCD_VXSIZE
  #define LCD_VXSIZE      (LCD_XSIZE*LCD_XMAG) /* virtual x-size */
#endif
#ifndef LCD_VYSIZE
  #define LCD_VYSIZE      (LCD_YSIZE*LCD_YMAG) /* virtual y-size */
#endif

#ifndef LCD_SWAP_BYTE_ORDER
  #define LCD_SWAP_BYTE_ORDER (0)    /* only for 16 bit bus, default is not swapped */
#endif

#ifndef  LCD_MAX_LOG_COLORS
  #define  LCD_MAX_LOG_COLORS (256)
#endif

/* Optionally swap red and blue components */
#ifndef LCD_SWAP_RB
  #define LCD_SWAP_RB 
#endif

/*********************************************************************
*
*      Defaults for Display 0 (first display)
*
**********************************************************************
*/

#ifndef LCD_MIRROR_X
  #define LCD_MIRROR_X   (0)    /* If active:  X -> -X */
#endif
#ifndef LCD_MIRROR_Y
  #define LCD_MIRROR_Y   (0)    /* If active:  Y -> -Y */
#endif
#ifndef LCD_SWAP_XY
  #define LCD_SWAP_XY    (0)    /* If active:  X <-> Y */
#endif
#ifndef LCD_BITSPERPIXEL_L0
  #define LCD_BITSPERPIXEL_L0 LCD_BITSPERPIXEL
#endif
#ifndef LCD_DELTA_MODE
  #define LCD_DELTA_MODE 0 /**/
#endif

/* Position data for controller 0 */
#ifndef LCD_XORG0
  #define LCD_XORG0     (0)     /* leftmost position covered by this controller */
#endif
#ifndef LCD_YORG0
  #define LCD_YORG0     (0)     /* topmost position covered by this controller */
#endif
#ifndef LCD_XSIZE0
  #define LCD_XSIZE0   (LCD_XSIZE)   /* horizontal size covered by this controller */
#endif
#ifndef LCD_YSIZE0
 #define LCD_YSIZE0    (LCD_YSIZE)   /* vertical size covered by this controller */
#endif
#ifndef LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0 (0)     /* first segment used by this controller */
#endif
#ifndef LCD_LASTSEG0
  #define LCD_LASTSEG0    (LCD_XSIZE-1) /* Contr.0: last segment line used */
#endif
#ifndef LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0 (0)     /* first com used by this controller */
#endif
#ifndef LCD_LASTCOM0
  #define LCD_LASTCOM0    (LCD_YSIZE-1) /* Contr.0: last com line used */
#endif

#if (!LCD_SWAP_XY)
  #define LCD_XSIZE_PHYS  LCD_XSIZE
  #define LCD_YSIZE_PHYS  LCD_YSIZE
  #define LCD_VXSIZE_PHYS LCD_VXSIZE
  #define LCD_VYSIZE_PHYS LCD_VYSIZE
#else
  #define LCD_XSIZE_PHYS  LCD_YSIZE
  #define LCD_YSIZE_PHYS  LCD_XSIZE
  #define LCD_VXSIZE_PHYS LCD_VYSIZE
  #define LCD_VYSIZE_PHYS LCD_VXSIZE
#endif


#define LCD_REVERSE 0
#define LCD_PHYSCOLORS_IN_RAM 0
#define LCD_PIXELINDEX U16


#endif /* LCD_INTERN_H */



	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
