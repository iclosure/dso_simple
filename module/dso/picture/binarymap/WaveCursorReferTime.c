
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
 File        : WaveCursorReferTime.c
 Purpose     : DSO : 波形区顶端中央的时间参考
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

const GUI_COLOR ColorsWaveCursorReferTime[] = {
	0x0000,0xFC20
};

const GUI_LOGPALETTE PalWaveCursorReferTime = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsWaveCursorReferTime[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acWaveCursorReferTime[] = {
	XX______,_XX_____,
	_XX_____,XX______,
	__XX___X,X_______,
	___XX_XX,________,
	____XXX_,________,
	_____X__,________
};

const GUI_BITMAP bmWaveCursorReferTime = {
	11, /* XSize */
	6, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acWaveCursorReferTime,  /* Pointer to picture data (indices) */
	&PalWaveCursorReferTime  /* Pointer to palette */
};
