
/*
 * ***************************************************
 *                  ©¶®Z  ®W ®X®T®T®[ ®i ®X®T®T®Y©¶
 *                  ©¶®^®T®T®a ®`  ®] ®l ®^®T®T®_©¶
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
 File        : SlopeAlternatingEdge.c
 Purpose     : DSO: –±∆¬->Ωª±‰—ÿ
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

const GUI_COLOR ColorsSlopeAlternatingEdge[] = {
	0x0000,_24TO565(0xE1,0xE1,0xE1)
};

const GUI_LOGPALETTE PalSlopeAlternatingEdge = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsSlopeAlternatingEdge[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acSlopeAlternatingEdge[] = {
	___X____,__X_____,
	__XXX___,__X_____,
	_XXXXX__,__X_____,
	XXXXXXX_,__X_____,
	___X____,__X_____,
	___X____,__X_____,
	___X____,__X_____,
	___X___X,XXXXXX__,
	___X____,XXXXX___,
	___X____,_XXX____,
	___X____,__X_____
};

const GUI_BITMAP bmSlopeAlternatingEdge = {
	14, /* XSize */
	11, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acSlopeAlternatingEdge,  /* Pointer to picture data (indices) */
	&PalSlopeAlternatingEdge  /* Pointer to palette */
};
