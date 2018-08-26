	
/*
 * ***************************************************
 *                  ©¦¨Z  ¨W ¨X¨T¨T¨[ ¨i ¨X¨T¨T¨Y©¦
 *                  ©¦¨^¨T¨T¨a ¨`  ¨] ¨l ¨^¨T¨T¨_©¦
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
 File        : icon_menu_unknown.c
 Purpose     : DSO : unknow logo
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

const GUI_COLOR Colorsicon_menu_unknown[] = {
	0x0000,0x262A2D
};

const GUI_LOGPALETTE Palicon_menu_unknown = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&Colorsicon_menu_unknown[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acicon_menu_unknown[] = {
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

const GUI_BITMAP bmicon_menu_unknown = {
	10, /* XSize */
	9, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acicon_menu_unknown,  /* Pointer to picture data (indices) */
	&Palicon_menu_unknown  /* Pointer to palette */
};
