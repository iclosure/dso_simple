
/*
 * ***************************************************
 *                  │╖  ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜  ╙ ╨ ╚══╛│
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     (c) Copyright 2011, Unic Inc., China, Sc
 *     (c) Copyright 2011, SEGGER Microcontroller Systeme GmbH
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may not be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : WaveCursorTriTime.c
 Purpose     : DSO : 用于波形显示窗口的游标[触发时基,指向下]
   ----------------------------------------------------------------------
 */


#include "GUI.h"
 /*   Palette
 The following are the entries of the palette table.
 Every entry is a 32-bit value (of which 24 bits are actually used)
 the lower   8 bits represent the Red component,
 the middle  8 bits represent the Green component,
 the highest 8 bits (of the 24 bits used) represent the Blue component
 as follows:   0xBBGGRR
*/

const GUI_COLOR ColorsWaveCursorTriTime[] = {
	0x0000,0xFC20
};

const GUI_LOGPALETTE PalWaveCursorTriTime = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsWaveCursorTriTime[0]
};

static GUI_CONST_STORAGE unsigned char acWaveCursorTriTime[] = {
	XXXXXXXX,XXX_____,
	_XXXXXXX,XX______,
	__XXXXXX,X_______,
	___XXXXX,________,
	____XXX_,________,
	_____X__,________
};

const GUI_BITMAP bmWaveCursorTriTime = {
	11, /* XSize */
	6, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acWaveCursorTriTime,  /* Pointer to picture data (indices) */
	&PalWaveCursorTriTime  /* Pointer to palette */
};


