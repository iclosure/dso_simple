
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
 File        : SlopeFallingEdge.c
 Purpose     : DSO: Ð±ÆÂ->ÏÂ½µÑØ
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

const GUI_COLOR ColorsSlopeFallingEdge[] = {
	0x0000,_24TO565(0xE1,0xE1,0xE1)
};

const GUI_LOGPALETTE PalSlopeFallingEdge = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsSlopeFallingEdge[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acSlopeFallingEdge[] = {
	XXXX____,
	___X____,
	___X____,
	___X____,
	XXXXXXX_,
	_XXXXX__,
	__XXX___,
	___X____,
	___X____,
	___X____,
	___XXXX_
};

const GUI_BITMAP bmSlopeFallingEdge = {
	7, /* XSize */
	11, /* YSize */
	1, /* BytesPerLine */
	1, /* BitsPerPixel */
	acSlopeFallingEdge,  /* Pointer to picture data (indices) */
	&PalSlopeFallingEdge  /* Pointer to palette */
};
