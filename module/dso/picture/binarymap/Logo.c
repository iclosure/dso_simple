
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
 File        : DATA_Logo.c
 Purpose     : DSO : ²úÆ·Logo
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

const GUI_COLOR ColorsLogo[] = {
	_24TO565(0x18,0x18,0x18),_24TO565(0xDF,0xDF,0xDF)
};

const GUI_LOGPALETTE PalLogo = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsLogo[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acLogo[] = {
	XXXXX___,XXXXXXXX,XX______,________,________,________,________,________,
	XXXXX___,XXXXXXXX,XX______,________,________,________,________,________,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXX__XX,__XXX___,_XXXXX__,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXX__XX,__XXX___,XXXXXXX_,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXX__XX,__XXX___,XXX_XXX_,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXXX_XX,__XXX___,XXX_XXX_,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXXX_XX,__XXX___,XXX_XXX_,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXXX_XX,__XXX___,XXX_____,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XXXXXXX,__XXX___,XXX_____,
	XXXXX___,XXXXXXXX,XX______,______XX,X_XXXX__,_XX_XXXX,__XXX___,XXX_XXX_,
	XXXXX___,________,________,______XX,X_XXXX__,_XX_XXXX,__XXX___,XXX_XXX_,
	XXXXX___,________,________,______XX,X_XXXX__,_XX_XXXX,__XXX___,XXX_XXX_,
	XXXXXXXX,XXXXXXXX,XXXX____,______XX,X_XXXX__,_XX__XXX,__XXX___,XXX_XXX_,
	XXXXXXXX,XXXXXXXX,XXXX____,______XX,X_XXXX__,_XX__XXX,__XXX___,XXXXXX__,
	XXXXXXXX,XXXXXXXX,XXXX____,________,XXXX____,_XX__XXX,__XXX___,_XXXX___,
	XXXXXXXX,XXXXXXXX,XXXX____,________,________,________,________,________,
	XXXXXXXX,XXXXXXXX,XXXX____,________,________,________,________,________,
};

const GUI_BITMAP bmLogo = {
	63, /* XSize */
	17, /* YSize */
	8, /* BytesPerLine */
	1, /* BitsPerPixel */
	acLogo,  /* Pointer to picture data (indices) */
	&PalLogo  /* Pointer to palette */
};
