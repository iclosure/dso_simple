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
 *  Project : DSC--H-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : integer.h
 Purpose     : integet types file.
   ----------------------------------------------------------------------
 */
#ifndef INTEGER_H
#define INTEGER_H

/* -----------------------------------------
 * ARM - S3C2410/S3C2440/S3C6410 : 
 *
 * sizeof(char)		= 1 byte ;
 * sizeof(short)	= 2 bytes;
 * sizeof(int)		= 4 bytes;
 * sizeof(long)		= 4 bytes;
 * sizeof(long long)= 8 bytes.
 * ----------------------------------------- */

// ::::::::::::::::::::::::::::::::::::::::::::
typedef signed char		I8	; /**/
typedef unsigned char	U8	; /**/
typedef signed short	I16	; /**/
typedef unsigned short  U16	; /**/
typedef signed long		I32	; /**/
typedef unsigned long	U32	; /**/
typedef I16				I16P; /**/
typedef U16				U16P; /**/
// ::::::::::::::::::::::::::::::::::::::::::::'
typedef U8				BYTE; /**/
typedef U16				WORD; /**/
typedef U32				DWORD; /**/
typedef I8				CHAR; /**/
typedef I32				LONG; /**/
// ::::::::::::::::::::::::::::::::::::::::::::
#define size_char		sizeof(char)
#define size_short		sizeof(short)
#define size_int		sizeof(int)
#define size_long		sizeof(long)
#define size_float		sizeof(float)
#define size_double		sizeof(double)
// ::::::::::::::::::::::::::::::::::::::::::::
#define size_I8			sizeof(I8)
#define size_U8			sizeof(U8)
#define size_I16		sizeof(I16)
#define size_U16		sizeof(U16)
#define size_I32		sizeof(I32)
#define size_U32		sizeof(U32)
#define size_I16P		sizeof(I16P)
#define size_U16P		sizeof(U16P)
// ::::::::::::::::::::::::::::::::::::::::::::
typedef char *			String	;  /**/
typedef const char *	SString	;  /**/
// ::::::::::::::::::::::::::::::::::::::::::::



#endif /* #ifndef INTEGER_H */

