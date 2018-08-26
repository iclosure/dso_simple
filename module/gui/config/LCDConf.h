/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf_2011_C8_C800x480.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE           (800)    /* X-resolution of LCD, Logical coor. for linux */
#define LCD_YSIZE           (480)    /* Y-resolution of LCD, Logical coor. for linux */
#define LCD_BITSPERPIXEL    (16)     /* for linux */
#define SIZEPERLINE         (LCD_XSIZE*(LCD_BITSPERPIXEL/8))
#define LCD_BYTESIZE        (LCD_XSIZE*LCD_YSIZE*LCD_BITSPERPIXEL/2)

#define LCD_SWAP_RB (1)              /* for linux, actually 1555 format */
#define LCD_FIXEDPALETTE    (565)    /* for linux, actually 1555 format */
#define LCD_CONTROLLER      (-1)     /* for linux */



#endif /* LCDCONF_H */
