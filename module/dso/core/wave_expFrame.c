
#include "dso_confDefaults.h"
#include "GUI.h"
#include "GUI_Protected.h"

/***************************************************************
 *               重绘波形区域外边框[被覆盖过的部分]的上边界
 *
 */
void wave_expFrameTop(int y0, int x0, int x1) {
	if(y0 <= WAVEEXFRAME_SY)  // 如果之前被覆盖过则重绘被覆盖段
		GUI_DrawHLine(WAVEEXFRAME_SY, x0, x1);
}
/***************************************************************
 *            重绘波形区域外边框[被覆盖过的部分]的下边界
 *
 */
void wave_expFrameBottom(int y0, int x0, int x1) {
	if(y0 >= WAVEEXFRAME_EY)  // 如果之前被覆盖过则重绘被覆盖段
		GUI_DrawHLine(WAVEEXFRAME_EY, x0, x1);
}
/***************************************************************
 *                     绘制波形区域外边框
 * 
 */
void wave_expFrame(void) {
	GUI_SetColor(WAVEEXFRAME_DEFAULTCOLOR);  // 设置线条颜色
	GUI_DrawRect(WAVEEXFRAME_SX,WAVEEXFRAME_SY,WAVEEXFRAME_EX,WAVEEXFRAME_EY);
	GUI_DrawHLine(WAVEEXFRAME_SY,0,WAVEEXFRAME_SX-1);
	GUI_DrawHLine(WAVEEXFRAME_EY,0,WAVEEXFRAME_SX-1);
}