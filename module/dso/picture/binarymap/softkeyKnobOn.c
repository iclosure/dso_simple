
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
 File        : SoftKeyKnobOn.c
 Purpose     : DSO : 软键旋钮使能标志
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

const GUI_COLOR ColorsSoftKeyKnobOn[] = {
	0x0000,0xB7E0
};

const GUI_LOGPALETTE PalSoftKeyKnobOn = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsSoftKeyKnobOn[0]
};
// 
static GUI_CONST_STORAGE unsigned char acSoftKeyKnobOn[] = {
	_______X,XXXXX___,________,
	_______X,XXXXXX__,________,
	_______X,XXXXXXX_,________,
	___X____,____XXXX,________,
	__XXX___,_____XXX,________,
	_XXXXX__,______XX,X_______,
	XXXXXXX_,______XX,X_______,
	XXXXXXX_,______XX,X_______,
	__XXX___,______XX,X_______,
	___XXX__,_____XXX,________,
	___XXXX_,____XXXX,________,
	____XXXX,XXXXXXX_,________,
	_____XXX,XXXXXX__,________,
	_______X,XXXX____,________
};

const GUI_BITMAP bmSoftKeyKnobOn = {
	17, /* XSize */
	14, /* YSize */
	3, /* BytesPerLine */
	1, /* BitsPerPixel */
	acSoftKeyKnobOn,  /* Pointer to picture data (indices) */
	&PalSoftKeyKnobOn  /* Pointer to palette */
};
