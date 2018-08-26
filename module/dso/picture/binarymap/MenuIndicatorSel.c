
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
 File        : MenuIndicatorSel.c
 Purpose     : DSO : 菜单选中指示器
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

const GUI_COLOR ColorsMenuIndicatorSel[] = {
	0x0000,_24TO565(0xE1,0xE1,0xE1)
};

const GUI_LOGPALETTE PalMenuIndicatorSel = {
	2,	/* number of entries */
	1, 	/* No transparency */
	ColorsMenuIndicatorSel
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acMenuIndicatorSel[] = {
	___X____,________,
	___XX___,________,
	___XXX__,________,
	___XXXX_,________,
	XXXXXXXX,________,
	XXXXXXXX,X_______,
	XXXXXXXX,XX______,
	XXXXXXXX,X_______,
	XXXXXXXX,________,
	___XXXX_,________,
	___XXX__,________,
	___XX___,________,
	___X____,________
};

const GUI_BITMAP bmMenuIndicatorSel = {
	10, /* XSize */
	13, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acMenuIndicatorSel,  /* Pointer to picture data (indices) */
	&PalMenuIndicatorSel  /* Pointer to palette */
};
