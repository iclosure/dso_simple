
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
 File        : WaveCursorTrigger.c
 Purpose     : DSO : 用于波形显示窗口的游标[触发游标]
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

const GUI_COLOR ColorsWaveCursorTrigger[] = {
	0x0000,GUI_YELLOW
};

const GUI_LOGPALETTE PalWaveCursorTrigger = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsWaveCursorTrigger[0]
};

static GUI_CONST_STORAGE unsigned char acWaveCursorTrigger[] = {
	XXXXXXX_,
	___X____,
	___X____,
	___X____,
	___X____,
	___X____,
	___X____,
	___X____,
	___X____,
	________,
	________,
	___X____,
	___XX___,
	___XXX__,
	___XXXX_,
	___XXXXX,
	___XXXX_,
	___XXX__,
	___XX___,
	___X____
};

const GUI_BITMAP bmWaveCursorTrigger = {
	8, /* XSize */
	20, /* YSize */
	1, /* BytesPerLine */
	1, /* BitsPerPixel */
	acWaveCursorTrigger,  /* Pointer to picture data (indices) */
	&PalWaveCursorTrigger  /* Pointer to palette */
};


