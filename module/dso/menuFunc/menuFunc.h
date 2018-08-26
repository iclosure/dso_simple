#ifndef MENUFUNC_H
#define MENUFUNC_H

#include "global.h"
#include <stdio.h>

/**************************************************************
 *
 *                   Analyze menu functions
 *  [1/18/2012 robot]
 */
void* mfLanguage_AutoSet(PROJECT_INFO *info,I8 id);
void* mfLanguage_Enter(PROJECT_INFO *info,I8 id);

/**************************************************************
 *
 *                   AutoScale menu functions
 *  [1/18/2012 robot]
 */
void* mfAutoScale_SelChannels(PROJECT_INFO *info,I8 id);

/**************************************************************
 *
 *                   ChannelInfo menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   CursorSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   DigitalChannel menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   DislpaySet menu functions
 *  [1/18/2012 robot]
 */
void* mf_SetGrid(PROJECT_INFO *info,I8 id);

/**************************************************************
 *
 *                   FileLoad menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   HorizontalSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Language menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Lister menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Measure menu functions
 *  [1/18/2012 robot]
 */
void* mfMeasure_dispFastView(PROJECT_INFO *info,I8 id);
void* mfMeasure_addMeas(PROJECT_INFO *info,I8 id);
void* mfMeasure_delMeas(PROJECT_INFO *info,I8 id);
void mfMeasure_freshSKTitle(MENUPAGE_INFO *info);

/**************************************************************
 *
 *                   NewLabel menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Pattern menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   PrintSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   ReferWaveform menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   SamplingSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   ScreenSaveSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Service menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   TimeSet menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   Trigger menu functions
 *  [1/18/2012 robot]
 */
void* mfTrigger_slop(PROJECT_INFO *info,I8 id);

/**************************************************************
 *
 *                   TriggerCoupling menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   WaveformGen menu functions
 *  [1/18/2012 robot]
 */
/**************************************************************
 *
 *                   WaveformMath menu functions
 *  [1/18/2012 robot]
 */



#endif /* MENUFUNC_H */
