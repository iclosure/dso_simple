

#include "GUI.h"
#include "GUI_Protected.h"
#include "LCD_Private.h"
#include "dso_confDefaults.h"


/**********************************************************
 *                隐藏信息栏背景
 */
void dso_hideBar(GUI_RECT rect) {
	GUI_SetColor(DesktopBkColor);
	LCD_ClearRect(rect);
}

/**********************************************************
 *                绘制小尺寸信息栏背景
 */
void dso_drawSmallBarBk(GUI_RECT rect, U16 FillColor) {
	int i;
	// 绘制上下两根填充短线
	GUI_SetColor(FillColor);
	GUI_DrawHLine(rect.y0+1,rect.x0+2,rect.x1-2);
	GUI_DrawHLine(rect.y1-1,rect.x0+2,rect.x1-2);
	// 绘制剩余填充图
	for(i=rect.y0+2; i<=rect.y1-2; i++)
		GUI_DrawHLine(i, rect.x0+1,rect.x1-1);
	// 绘制左上方边框线[阳面]
	GUI_SetColor(BAR_POSEDGECOLOR);
	GUI_DrawHLine(rect.y0,rect.x0+2,rect.x1-2);
	GUI_DrawVLine(rect.x0,rect.y0+2,rect.y1-2);
	// 绘制右下方边框线[阴面]
	GUI_SetColor(BAR_NEGEDGECOLOR);
	GUI_DrawHLine(rect.y1,rect.x0+2,rect.x1-2);
	GUI_DrawVLine(rect.x1,rect.y0+2,rect.y1-2);
	GUI_SetColor(BAR_POSEDGECOLOR);
	GUI_DrawPoint(rect.x0+1, rect.y1-1);  // 左下角点
	GUI_DrawPoint(rect.x0+1, rect.y0+1);  // 左上角点
	GUI_DrawPoint(rect.x1-1, rect.y0+1);  // 右上角点
	GUI_SetColor(BAR_NEGEDGECOLOR);
	GUI_DrawPoint(rect.x1-1, rect.y1-1);  // 右下角点
}

/**********************************************************
 *                绘制大尺寸信息栏背景
 */
void dso_drawLargeBarBk(GUI_RECT rect, U16 FillColor) {
	int i;
	// 绘制上下两根填充短线
	GUI_SetColor(FillColor);
	GUI_DrawHLine(rect.y0+1,rect.x0+4,rect.x1-4);
	GUI_DrawHLine(rect.y1-1,rect.x0+4,rect.x1-4);
	// 绘制次上下四根填充短线
	for(i=2; i<=3; i++) {
		GUI_DrawHLine(rect.y0+i,rect.x0+2,rect.x1-2);
		GUI_DrawHLine(rect.y1-i,rect.x0+2,rect.x1-2);
	}
	// 绘制剩余填充图
	for(i=rect.y0+4; i<=rect.y1-4; i++)
		GUI_DrawHLine(i, rect.x0+1,rect.x1-1);
	// 绘制左上方边框线[阳面]
	GUI_SetColor(BAR_POSEDGECOLOR);
	GUI_DrawHLine(rect.y0,rect.x0+4,rect.x1-4);
	GUI_DrawVLine(rect.x0,rect.y0+4,rect.y1-4);
	// 绘制右下方边框线[阴面]
	GUI_SetColor(BAR_NEGEDGECOLOR);
	GUI_DrawHLine(rect.y1,rect.x0+4,rect.x1-4);
	GUI_DrawVLine(rect.x1,rect.y0+4,rect.y1-4);
	for(i=2; i<=3; i++) {
		GUI_SetColor(BAR_POSEDGECOLOR);
		GUI_DrawPoint(rect.x0+1, rect.y1-i);  // 左下角竖线
		GUI_DrawPoint(rect.x0+i, rect.y0+1);  // 左上角横线
		GUI_DrawPoint(rect.x0+1, rect.y0+i);  // 左上角竖线
		GUI_DrawPoint(rect.x1-i, rect.y0+1);  // 右上角横线
		GUI_SetColor(BAR_NEGEDGECOLOR);
		GUI_DrawPoint(rect.x0+i, rect.y1-1);  // 左下角横线
		GUI_DrawPoint(rect.x1-1, rect.y0+i);  // 右上角竖线
		GUI_DrawPoint(rect.x1-i, rect.y1-1);  // 右下角横线
		GUI_DrawPoint(rect.x1-1, rect.y1-i);  // 右下角竖线
	}
}

/**********************************************************
 *                绘制标题栏
 * 参数说明: 
 */
void dso_drawTitleBar(const char *title, int y0,int x0,int x1) {
	int i;
	// 绘制向下两根边框线
	GUI_SetColor(TITLEBAR_EDGECOLOR);
	GUI_DrawHLine(y0,x0,x1);
	GUI_DrawHLine(y0+TITLEBAR_YSIZE-1,x0,x1);
	// 绘制填充区
	GUI_SetColor(TITLEBAR_FILLCOLOR);
	for(i=y0+1; i<y0+TITLEBAR_YSIZE-1; i++) 
		GUI_DrawHLine(i, x0,x1);
	// 绘制填充区的几个特殊点
	GUI_SetColor(TITLEBAR_DOTCOLOR);
	for(i=y0+7; i<=y0+TITLEBAR_YSIZE-7; i+=3) {
		GUI_DrawPoint(x0+4, i);  // 
		GUI_DrawPoint(x0+7, i);  // 
		GUI_DrawPoint(x1-5, i);  // 
		GUI_DrawPoint(x1-8, i);  // 
	}
	if(title) {
		GUI_SetColor(BASE_FONTCOLOR);
		GUI_DispStringHCenterAt(title,(x0+x1+1)/2,y0+4);
	} else {
		return ;
	}
}
/**********************************************************
 *
 *            绘制带标题的框架(...)
 */
void dso_drawFrame(GUI_RECT rect, U16 FillColor, const char *title) {
	dso_drawLargeBarBk(rect,FillColor);
	dso_drawTitleBar(title, rect.y0,rect.x0,rect.x1);
}
/**********************************************************
 *                绘制标题栏
 * 参数说明: 绘制软键上的选中正方形框
 */
void dso_drawSKSelRect(int x0,int y0, int length) {
	GUI_COLOR c0=GUI_GetColor();
	GUI_SetColor(SOFTKEY_SELRECT_POSCOLOR);
	GUI_DrawHLine(y0, x0,x0+length-1);
	GUI_DrawVLine(x0, y0,y0+length-1);
	GUI_SetColor(SOFTKEY_SELRECT_NEGCOLOR);
	GUI_DrawHLine(y0+length-1, x0+1,x0+length-1);
	GUI_DrawVLine(x0+length-1, y0+1,y0+length-1);
	GUI_SetColor(c0);
}