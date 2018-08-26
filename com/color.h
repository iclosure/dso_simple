
#ifndef COLOR_H
#define COLOR_H

#include "integer.h"


/************************************************************************
 *
 *                     COLOR      
 *  [1/5/2012 lkh]
 */
typedef	U16					COLOR		;  /*颜色数据类型定义*/
typedef enum tagBASECOLOR	BASECOLOR	;  /*base color table*/

#define _24TO565(r,g,b)		((((r)>>3)<<11)| \
							 (((g)>>2)<< 5)| \
							 (((b)>>3)    ))
#define _565TO24(c)			((((((c)>>11)&31)*255/31)    )| \
							 (((((c)>> 5)&63)*255/63)<< 8)| \
							 (((((c)    )&31)*255/31)<<16))
typedef enum tagBASECOLOR {
	/*base colors*/
	color_black			= _24TO565(  0,  0,  0)	,
	color_u1			= _24TO565(  0,  0, 64) ,
	color_darkblue		= _24TO565(  0,  0,128) ,
	color_blue			= _24TO565(  0,  0,255) ,
	color_u4			= _24TO565(  0, 64,  0) ,
	color_u5			= _24TO565(  0, 64, 64) ,
	color_u6			= _24TO565(  0, 64,128) ,
	color_u7			= _24TO565(  0, 64,255) ,
	color_darkgreen		= _24TO565(  0,128,  0) ,
	color_u9			= _24TO565(  0,128, 64) ,
	color_darkcyan		= _24TO565(  0,128,128) ,
	color_u11			= _24TO565(  0,128,255) ,
	color_green			= _24TO565(  0,255,  0) ,
	color_u13			= _24TO565(  0,255, 64) ,
	color_u14			= _24TO565(  0,255,128) ,
	color_cyan			= _24TO565(  0,255,255) ,
	color_u16			= _24TO565( 64,  0,  0)	,
	color_u17			= _24TO565( 64,  0, 64) ,
	color_u18			= _24TO565( 64,  0,128) ,
	color_u19			= _24TO565( 64,  0,255) ,
	color_u20			= _24TO565( 64, 64,  0) ,
	color_darkgray		= _24TO565( 64, 64, 64) ,
	color_u22			= _24TO565( 64, 64,128) ,
	color_u23			= _24TO565( 64, 64,255) ,
	color_u24			= _24TO565( 64,128,  0) ,
	color_u25			= _24TO565( 64,128, 64) ,
	color_u26			= _24TO565( 64,128,128) ,
	color_u27			= _24TO565( 64,128,255) ,
	color_u28			= _24TO565( 64,255,  0) ,
	color_u29			= _24TO565( 64,255, 64) ,
	color_u30			= _24TO565( 64,255,128) ,
	color_u31			= _24TO565( 64,255,255) ,
	color_darkred		= _24TO565(128,  0,  0)	,
	color_u33			= _24TO565(128,  0, 64) ,
	color_darkpurple	= _24TO565(128,  0,128) ,
	color_u35			= _24TO565(128,  0,255) ,
	color_u36			= _24TO565(128, 64,  0) ,
	color_u37			= _24TO565(128, 64, 64) ,
	color_u38			= _24TO565(128, 64,128) ,
	color_u39			= _24TO565(128, 64,255) ,
	color_u40			= _24TO565(128,128,  0) ,
	color_u41			= _24TO565(128,128, 64) ,
	color_gray			= _24TO565(128,128,128) ,
	color_lightblue		= _24TO565(128,128,255) ,
	color_u44			= _24TO565(128,255,  0) ,
	color_u45			= _24TO565(128,255, 64) ,
	color_lightgreen	= _24TO565(128,255,128) ,
	color_lightcyan		= _24TO565(128,255,255) ,
	color_red			= _24TO565(255,  0,  0)	,
	color_u49			= _24TO565(255,  0, 64) ,
	color_u50			= _24TO565(255,  0,128) ,
	color_purple		= _24TO565(255,  0,255) ,
	color_u52			= _24TO565(255, 64,  0) ,
	color_u53			= _24TO565(255, 64, 64) ,
	color_u54			= _24TO565(255, 64,128) ,
	color_u55			= _24TO565(255, 64,255) ,
	color_u56			= _24TO565(255,128,  0) ,
	color_u57			= _24TO565(255,128, 64) ,
	color_lightred		= _24TO565(255,128,128) ,
	color_lightpurple	= _24TO565(255,128,255) ,
	color_yellow		= _24TO565(255,255,  0) ,
	color_u61			= _24TO565(255,255, 64) ,
	color_lightyellow	= _24TO565(255,255,128) ,
	color_white			= _24TO565(255,255,255) ,
	/*special colors*/
	color_brown			= _24TO565(165, 42, 42) ,
	color_orange		= _24TO565(  0,200,255) ,
	color_redorange		= _24TO565(  0, 40,255) ,

} tBASECOLOR;

/*****************************************************
 *
 *                24RGB --> 565RGB
 * [1/5/2012 lkh]
 */
U16 color_24RGBto565RGB(U8 r,U8 g,U8 b);
/*****************************************************
 *
 *                   565RGB --> 24BGR
 * [1/5/2012 lkh]
 */
U32 color_565RGBto24BGR(U16 c);



#endif /**/
