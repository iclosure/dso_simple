
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
 File        : SoftKeyIndicator.c
 Purpose     : DSO : 软键子菜单指示器
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

const GUI_COLOR ColorsSoftKeyIndicator[] = {
	0x0000,_24TO565(0xE1,0xE1,0xE1)
};

const GUI_LOGPALETTE PalSoftKeyIndicator = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsSoftKeyIndicator[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acSoftKeyIndicator[] = {
	________,XXXXXXXX,XXXXX___,________,
	________,XXXXXXXX,XXXXX___,________,
	________,XXXXXXXX,XXXXX___,________,
	________,XXXXXXXX,XXXXX___,________,
	XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXX___,
	__XXXXXX,XXXXXXXX,XXXXXXXX,XXX_____,
	____XXXX,XXXXXXXX,XXXXXXXX,X_______,
	______XX,XXXXXXXX,XXXXXXX_,________,
	________,XXXXXXXX,XXXXX___,________,
	________,__XXXXXX,XXX_____,________,
	________,____XXXX,X_______,________,
	________,______X_,________,________
};

const GUI_BITMAP bmSoftKeyIndicator = {
	29, /* XSize */
	12, /* YSize */
	4, /* BytesPerLine */
	1, /* BitsPerPixel */
	acSoftKeyIndicator,  /* Pointer to picture data (indices) */
	&PalSoftKeyIndicator  /* Pointer to palette */
};
