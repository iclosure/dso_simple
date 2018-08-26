
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
 File        : dsp_fir.c
 Purpose     : FFT serial functions
   ----------------------------------------------------------------------
 */

#include "FilterCoeff.h"
#include "dsp.h"
#include "dsptype.h"
#include "integer.h"
#include <string.h>
#include <stdlib.h>

// +++++++++ FIRÂË²¨ +++++++++++++++++

void dsp_fir(int data[], I16 m)
{
	int *pFilterCoeff;
	pFilterCoeff = (int *) malloc(FFTN(m<<1) * size_int);
    memcpy(pFilterCoeff,FilterCoeff, FIRorder * size_int);    // ÔÝ´æÂË²¨Æ÷ÏµÊý // because sizeof(float) is 4
	dsp_fastconv(data, FFTN(m), pFilterCoeff,FIRorder, (m<<1));
}

