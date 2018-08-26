
#include "GUI_Protected.h"
#include "GUI.h"
#include "LCD_Private.h"
#include "menu.h"
#include "dso.h"
#include "key.h"
#include <string.h>


// 显示当前菜单页标题
void menu_displayPageTitle(MENUPAGE_INFO info) {
	GUI_SetColor(BASE_FONTCOLOR);
	GUI_DispStringAt(info.now->title, SOFTKEY_SX, SOFTKEY_SY-GUI_GetFontSizeY()-2);
}
/*******************************************************************
 *
 *                绘制一组软键
 */
// 
void menu_drawSoftKey(MENUPAGE_INFO *info) {
	int i;
	GUI_SetBkColor(DesktopBkColor);
	GUI_ClearRectEx(SoftKeyArea);
	for(i=0; i<6; i++) {
		menu_drawOneSoftKey(info,0,i);
	}
}
// 
void menu_drawOneSoftKey(MENUPAGE_INFO *info,I8 enTask,U8 id) {
	int sx= SOFTKEY_SX+(SOFTKEY_XSIZE+SOFTKEY_SPACE)*id;
	GUI_RECT rect0,rect1={sx, SOFTKEY_SY, sx+bmsoftkeybk.XSize-1, SOFTKEY_EY};
	SOFTKEY_DATA *sk=&info->sk[id];
	GUI_GetClientRect(&rect0);
	GUI_SetClipRect(&rect1);
	GUI_SetColor(BASE_FONTCOLOR);
	switch(sk->option) {
	case SOFTKEY_IF_EMPTY: {
		GUI_SetBkColor(DesktopBkColor);
		GUI_ClearRect(sx, SOFTKEY_SY, sx+SOFTKEY_XSIZE, SOFTKEY_EY);
		} break;
	case SOFTKEY_IF_NOBK:
		dso_drawLargeBarBk(rect1, BAR_FILLCOLOR);
		GUI_SetColor(BAR_NEGEDGECOLOR);
		GUI_DispStringHCenterAt(sk->title, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		menu_displaykword(info,id);
		break;
	case SOFTKEY_IF_NEXT:
		GUI_DrawBitmap(&bmsoftkeybk, sx,SOFTKEY_SY);
		GUI_DispStringHCenterAt(sk->title, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		GUI_DrawBitmap(&bmSoftKeyIndicator, sx+SOFTKEY_XSIZE/2-bmSoftKeyIndicator.XSize/2,SOFTKEY_EY-bmSoftKeyIndicator.YSize-2);
		break;
	case SOFTKEY_IF_RECT:
		GUI_DrawBitmap(&bmsoftkeybk, sx,SOFTKEY_SY);
		GUI_DispStringHCenterAt(sk->title, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		dso_drawSKSelRect(sx+(bmsoftkeybk.XSize-SOFTKEY_SELRECT_SIZE)/2,SOFTKEY_SELRECT_SY,SOFTKEY_SELRECT_SIZE);
		break;
	case SOFTKEY_IF_STATIC: 
		GUI_DrawBitmap(&bmsoftkeybkoff, sx,SOFTKEY_SY);
		GUI_DispStringHCenterAt(sk->title, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		menu_displaykword(info,id);
		break;
	case SOFTKEY_IF_SELRECT:
		rect1.x0 = sx+(bmsoftkeybk.XSize-SOFTKEY_SELRECT_SIZE)/2+2;
		rect1.y0 = SOFTKEY_SELRECT_SY+2;
		rect1.x1 = rect1.x0+SOFTKEY_SELRECT_SIZE-5;
		rect1.y1 = rect1.y0+SOFTKEY_SELRECT_SIZE-5;
		GUI_SetClipRect(&rect1);
		GUI_SetColor(SOFTKEY_SELCOLOR);
		GUI_FillRectEx(rect1);
		GUI_SetClipRect(&rect0);
		if(enTask==1 && sk->task)
			sk->task(info->parent,id);
		break;
	case SOFTKEY_IF_ACTIVATE:
	case SOFTKEY_IF_MENU: 
		GUI_DrawBitmap(&bmsoftkeybkoff, sx,SOFTKEY_SY);
		GUI_DrawBitmap(&bmSoftKeyKnobOn, sx+SOFTKEY_KNOP_SX,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		GUI_DispStringHCenterAt(sk->title, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY);
		menu_displaykword(info,id);
		GUI_SetClipRect(&rect0);
		if(enTask==1 && sk->task)
			sk->task(info->parent,id);
	default : break;
	}
	GUI_SetClipRect(&rect0);
}
// 
void menu_drawMenuUp(MENUPAGE_INFO *info) {
	MENUUP_DATA	*menu = info->sk[info->id].menuup;
	if(menu->index==0 && menu->status==0) {  // 之前没有选中的菜单项
		if(menu->frame.y0 <= WAVEWIN_SY) {
			menu->dispdir = 0;
			menu->top	= 0;
			menuup_calcBase(info);
		}
		menuup_setStatus(menu, 0);
	}
	info->hide = 0;
	menu_preDraw1MenuUp(info);
}