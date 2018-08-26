
#include "dso_confDefaults.h"
#include "GUI.h"
#include "GUI_Protected.h"

/***************************************************************
 *               �ػ沨��������߿�[�����ǹ��Ĳ���]���ϱ߽�
 *
 */
void wave_expFrameTop(int y0, int x0, int x1) {
	if(y0 <= WAVEEXFRAME_SY)  // ���֮ǰ�����ǹ����ػ汻���Ƕ�
		GUI_DrawHLine(WAVEEXFRAME_SY, x0, x1);
}
/***************************************************************
 *            �ػ沨��������߿�[�����ǹ��Ĳ���]���±߽�
 *
 */
void wave_expFrameBottom(int y0, int x0, int x1) {
	if(y0 >= WAVEEXFRAME_EY)  // ���֮ǰ�����ǹ����ػ汻���Ƕ�
		GUI_DrawHLine(WAVEEXFRAME_EY, x0, x1);
}
/***************************************************************
 *                     ���Ʋ���������߿�
 * 
 */
void wave_expFrame(void) {
	GUI_SetColor(WAVEEXFRAME_DEFAULTCOLOR);  // ����������ɫ
	GUI_DrawRect(WAVEEXFRAME_SX,WAVEEXFRAME_SY,WAVEEXFRAME_EX,WAVEEXFRAME_EY);
	GUI_DrawHLine(WAVEEXFRAME_SY,0,WAVEEXFRAME_SX-1);
	GUI_DrawHLine(WAVEEXFRAME_EY,0,WAVEEXFRAME_SX-1);
}