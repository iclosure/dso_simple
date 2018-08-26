
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
 File        : MenuSelHook.c
 Purpose     : DSO : 菜单向上翻页指示器
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

const GUI_COLOR ColorsMenuSelHook[] = {
	0x0000,_24TO565(0xE1,0xE1,0xE1)
};

const GUI_LOGPALETTE PalMenuSelHook = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsMenuSelHook[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acMenuSelHook[] = {
	________,_X______,
	________,XX______,
	_______X,X_______,
	______XX,________,
	_____XX_,________,
	X___XX__,________,
	XX_XX___,________,
	_XXX____,________,
	__X_____,________
};

const GUI_BITMAP bmMenuSelHook = {
	10, /* XSize */
	9, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acMenuSelHook,  /* Pointer to picture data (indices) */
	&PalMenuSelHook  /* Pointer to palette */
};
