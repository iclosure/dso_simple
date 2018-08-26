
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
 *  Project : DSC--H-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : utypes.h
 Purpose     : all types file.
   ----------------------------------------------------------------------
 */

#ifndef UTYPES_H
#define UTYPES_H

#include "integer.h"  // 实数域类型重定义
//#include "complex.h"  // 复数域类型重

#ifdef WIN32
	// Visual Studio C 6++ ->
	#pragma warning( disable : 4244 )  // Disable warning messages in simulation
	#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
	#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
	#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
	// Visual Studio 2008 ->
	#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif     



// ::::::::::::::::::::::::::::::::::::::::::::::::::
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* #ifndef UTYPES_H */

