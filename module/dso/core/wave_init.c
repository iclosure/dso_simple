
#include "wave.h"
#include "picture.h"

/************************************************************************/
/*                    global variables                                  */
/************************************************************************/
WAVE_INFO waveinfo;  /*(��ǰ)������Ϣ*/

/************************************************************
 *
 *                   functions
 */
void wave_init(WAVE_INFO *info) {
	wave_setDefaultCnt(info);
	GUI_DrawBitmap(&bmWaveCursorHToGND,0,100);
	GUI_DrawBitmap(&bmWaveCursorToDown,0,200);

}