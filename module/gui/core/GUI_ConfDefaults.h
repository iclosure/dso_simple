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
File        : GUI_ConfDefaults.h
Purpose     : Defaults for GUI config switches.
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/

#ifndef  GUI_CONFDEFAULTS_H
#define  GUI_CONFDEFAULTS_H

#include "GUIConf.h"

/**********************************************************************
*
*       Defaults for config switches
*
***********************************************************************
*/

/* Define "universal pointer". Normally, this is not needed (define will expand to nothing)
   However, on some systems (AVR - IAR compiler) it can be necessary ( -> __generic),
   since a default pointer can access RAM only, not the built-in Flash
*/
#ifndef GUI_UNI_PTR
  #define GUI_UNI_PTR
  #define GUI_UNI_PTR_USED 0
#else
  #define GUI_UNI_PTR_USED 1
#endif

/* Define const storage. Normally, this is not needed (define will expand to const)
   However, on some systems (AVR - IAR compiler) it can be necessary ( -> __flash const),
   since otherwise constants are copied into RAM
*/

#ifndef GUI_SUPPORT_UNICODE
  #define GUI_SUPPORT_UNICODE 1
#endif

#ifndef GUI_SUPPORT_ARABIC
  #define GUI_SUPPORT_ARABIC 0
#endif

#ifndef GUI_ALLOC_SIZE
  #define GUI_ALLOC_SIZE      1000
#endif

#ifndef GUI_MAXBLOCKS
  #define GUI_MAXBLOCKS (2 + GUI_ALLOC_SIZE / 32)
#endif

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

#ifndef GUI_SUPPORT_TOUCH
  #define GUI_SUPPORT_TOUCH   0
#endif

#ifndef GUI_SUPPORT_MOUSE
  #define GUI_SUPPORT_MOUSE   0
#endif

#ifndef GUI_SUPPORT_AA
  #define GUI_SUPPORT_AA      0
#endif

#ifndef GUI_SUPPORT_LARGE_BITMAPS
  #if GUI_ALLOC_SIZE > 65535
    #define GUI_SUPPORT_LARGE_BITMAPS 1
  #else
    #define GUI_SUPPORT_LARGE_BITMAPS 0
  #endif
#endif

#ifndef GUI_COMPATIBLE_MODE
  #define GUI_COMPATIBLE_MODE 1
#endif

/* Some compilers for very simple chips can not generate code for function pointers
with parameters. In this case, we do not use function pointers, but limit the functionality slightly */
#define GUI_COMPILER_SUPPORTS_FP 1
#define GUI_SUPPORT_ROTATION 1


/* Types used for memory allocation */
#if GUI_ALLOC_SIZE <32767
  #define GUI_ALLOC_DATATYPE   I16
  #define GUI_ALLOC_DATATYPE_U U16
#else
  #define GUI_ALLOC_DATATYPE   I32
  #define GUI_ALLOC_DATATYPE_U U32
#endif

#ifndef   GUI_MEMSET
  #define GUI_MEMSET GUI__memset
#endif


#endif   /* ifdef GUI_CONFDEFAULTS_H */
/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
