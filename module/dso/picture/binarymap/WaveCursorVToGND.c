
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
 File        : WaveCursorVToGND.c
 Purpose     : DSO : 用于波形显示窗口的游标[当工作于XY模式时作为Y通道接地]
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

const GUI_COLOR ColorsWaveCursorVToGND[] = {
	0x0000,GUI_YELLOW
};

const GUI_LOGPALETTE PalWaveCursorVToGND = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsWaveCursorVToGND[0]
};

static GUI_CONST_STORAGE unsigned char acWaveCursorVToGND[] = {
	____X___,________,
	___XXX__,________,
	__XXXXX_,________,
	_XXXXXXX,________,
	XXXXXXXX,X_______,
	____X___,________,
	____X___,________,
	____X___,________,
	____X___,________,
	____X___,________,
	____X___,________,
	XXXXXXXX,X_______,
	________,________,
	_XXXXXXX,________,
	________,________,
	___XXX__,________
};

const GUI_BITMAP bmWaveCursorVToGND = {
	9, /* XSize */
	16, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acWaveCursorVToGND,  /* Pointer to picture data (indices) */
	&PalWaveCursorVToGND  /* Pointer to palette */
};


