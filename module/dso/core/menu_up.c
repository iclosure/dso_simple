
#include "GUI_Private.h"
#include "dso_confDefaults.h"
#include "menu.h"
#include "dso.h"
#include "key.h"
#include "wave.h"
#include "thread.h"
#include "dpo.h"
#include <string.h>
#include <stdlib.h>


static U16 menubuff[MENUUP_YMAXSIZE][MENUUP_XMAXSIZE];  /*上拉菜单[和帮助菜单]数据缓冲区*/
static U16 areabuf[WAVEWIN_YSIZE][WAVEWIN_XSIZE];       /*区域显示缓冲区*/

/********************************************************************
* 
*                    static code
*
********************************************************************
*/
/********************************************************************
 * 
 *                       上拉菜单现象帮助信息显示
 */
static void _dispMenuItemHelp(MENUPAGE_INFO *info,U8 id) {
	int width,y;
	GUI_RECT r0,client,*helprect=&info->extFrame;
	MENUUP_DATA *menu= info->sk[info->id].menuup;
	// 确定帮助菜单区域
	if(menu->frame.x0-WAVEWIN_SX > WAVEWIN_EX-menu->frame.x1) {
		helprect->x0 = WAVEWIN_SX+2;
		helprect->x1 = menu->frame.x0-10;
	} else {
		helprect->x0 = menu->frame.x1+10;
		helprect->x1 = WAVEWIN_EX-2;
	}
	if(menu->frame.y0 < (WAVEWIN_SY+WAVEWIN_EY)/2) {
		helprect->y0 = menu->frame.y0+20;
		helprect->y1 = helprect->y0+50;
	} else {
		helprect->y1 = WAVEWIN_EY-20;
		helprect->y0 = helprect->y1-50;
	}
	client.x0 = helprect->x0 + 5;
	client.y0 = helprect->y0 + 22;
	width = GUI_GetStringDistX(menu->item[id].help);
	if(width < menu->MaxXSize)
		width = menu->MaxXSize;
	if(helprect->x0+width+19 < helprect->x1) {
		client.x1 = client.x0 + width;
		client.y1 = client.y0 + GUI_GetFontSizeY();
		helprect->x1 = client.x1 + 20;
		helprect->y1 = client.y1 + 20;
	} else {
		client.x1 = helprect->x1 - 20;
		client.y1 = width * (client.x1-client.x0)+10;
	}
	
	// 
	GUI_GetClientRect(&r0);
	GUI_SetClipRect(helprect);
	GUI_SetBkColor(DesktopBkColor);
	GUI_ClearRectEx(*helprect);
	// 绘制框架
	menu_drawDialog(menu->item[id].title, helprect);
	// 
	GUI_SetColor(color_lightyellow);
	GUI_DispStringInRect(menu->item[id].help,&client,GUI_TA_LEFT);
	// 
	for(y=helprect->y0; y<=helprect->y1; y++)
		memcpy(menubuff[y-helprect->y0]+menu->width, LCD[y]+helprect->x0,(helprect->x1 - helprect->x0+1)*size_U16);
	GUI_SetClipRect(&r0);
}
/********************************************************************
 * 
 *                       上拉菜单子软键处理
 */
static void menuup_Next(MENUPAGE_INFO *info,U8 id) {
	static I8 number=-1;  /*当前页的序号*/
	static I8 oldid=-1;
	static void *page;
	GUI_RECT r0;
	MENUITEM_DATA item= info->sk[info->id].menuup->item[id];
	GUI_GetClientRect(&r0);
	GUI_SetClipRect(&SoftKeyArea);
	if(item.next) {  // 绘制上拉菜单中菜单选项对应的子软键
		number	= info->number;
		oldid	= info->id;
		page	= info->now;
		menu_setNewSoftKey(info,item.next);
	} else if(oldid==info->id && number==info->number) {
		menu_setNewSoftKey(info,(MENUPAGE_DATA*)page);
		oldid	= -1;
	}
	GUI_SetClipRect(&r0);
}

// 绘制上拉菜单的每一条选项[包括标题,分隔线,菜单项]
static void _DrawItem(MENUPAGE_INFO *info,U8 id, int y0, int x0,int x1) {
	MENUITEM_DATA *item = &info->sk[info->id].menuup->item[id];
	GUI_SetColor(BAR_POSEDGECOLOR);
	switch(item->option) {
	case MENUUP_IF_TITLE:
		dso_drawTitleBar(item->title,y0,x0,x1);
		break;
	case MENUUP_IF_MENU: {
		int text_x0=x0+26, midy;
		if(item->icon) {   // 有图标
			if(item->icon->BitsPerPixel == 1) {   // 二值Bitmap[没有外框]
				if(GUI_GetFontSizeY() > item->icon->YSize)
					midy = GUI_GetFontSizeY();
				else
					midy = item->icon->YSize;
				text_x0 += item->icon->XSize+5;
				midy /= 2;
			} else {  // 彩图[有外框]
				text_x0 += MENUUP_ICONFRAME_XSIZE+5;
				midy = MENUUP_ICONFRAME_YSIZE/2;
			}
		} else {  // 没有图片
			midy = GUI_GetFontSizeY()/2;
		}
		if(item->status) {  // 是否被选中
			// 绘制选中项背景色
			GUI_SetColor(MENUUP_SELBKCOLOR);
			GUI_FillRect(x0+3,y0-MENUUP_MENU_SPACEHALF,x1-3, y0+midy*2+MENUUP_MENU_SPACEHALF);

			// 绘制选中项指示器
			if(item->icon && item->icon->BitsPerPixel > 1)
				GUI_DrawBitmap(&bmMenuIndicatorSel, x0+11,y0+midy-bmMenuIndicatorSel.YSize/2);
			else
				GUI_DrawBitmap(&bmMenuSelHook, x0+11,y0+midy-bmMenuSelHook.YSize/2);
			/******    上拉菜单子软键处理    *****/
			menuup_Next(info,id);
			/****** 上拉菜单选项帮助信息显示 *****/
			if(info->enExt==1 && item->help)
				_dispMenuItemHelp(info,id);
			// 在软键上显示对应的选中项提示
			menu_displaykword(info,info->id);
			// 调用执行函数
			if(info->sk[info->id].menuup->task) {
				info->sk[info->id].menuup->task(info->parent,id);
			} else if(info->sk[info->id].task) {
				info->sk[info->id].task(info->parent,id);
			}
		}
		if(item->icon) {
			if(item->icon->BitsPerPixel == 1) {  // 二值Bitmap[没有外框]
				GUI_DrawBitmap(item->icon, x0+26, y0+midy-item->icon->YSize/2);
			} else {  // 彩图[有外框]
				GUI_RECT r;
				r.x0= x0+26; r.x1= x0+77;
				r.y0= y0;    r.y1= y0+40;
				dso_drawSmallBarBk(r, MENUUP_ICONFRAMEBKCOLOR);
				GUI_DrawBitmap(item->icon, r.x1-item->icon->XSize-1,r.y1-item->icon->YSize);
			}
		}
		GUI_SetColor(BASE_FONTCOLOR);
		GUI_DispStringAt(item->title, text_x0, y0+midy-GUI_GetFontSizeY()/2);
		}
		break;
	case MENUUP_IF_SEPARATOR:
		GUI_DrawHLine(y0, x0+3,x1-3);
		break;
	default: break;
	}
}
// 下翻[往上显示]
static void _DrawFromDown(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	int y0 = menu->client.y1;
	I8 top = menu->base;
	I8 index = menuup_calcItemIndex(*menu,top);
	while(top >= menu->top-1) {
		y0 -= menu_calcItemYSize(menu->item[index])+MENUUP_MENU_SPACEHALF;
		_DrawItem(info,index, y0,menu->client.x0, menu->client.x1);
		y0 -= MENUUP_MENU_SPACEHALF;
		if(menu->item[index--].option == MENUUP_IF_MENU)
			top --;
	}
}
// 上翻[往下显示]
static void _DrawFromUp(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	int y1 = menu->client.y0;
	I8 base = menu->top;
	I8 index;
	if(base == 0)
		index = 0;
	else
		index = menuup_calcItemIndex(*menu,base);
	while(base <= menu->base+1) {
		y1 += MENUUP_MENU_SPACEHALF;
		_DrawItem(info,index, y1,menu->client.x0, menu->client.x1);
		y1 += menu_calcItemYSize(menu->item[index])+MENUUP_MENU_SPACEHALF;
		if(menu->item[index++].option == MENUUP_IF_MENU)
			base ++;
	}
}
// 
static void _DrawMenuUp(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	int y1 = menu->client.y0;
	I8 index = 0;
	while(index < menu->itemn) {
		y1 += MENUUP_MENU_SPACEHALF;
		_DrawItem(info,index, y1,menu->client.x0, menu->client.x1);
		y1 += menu_calcItemYSize(menu->item[index++])+MENUUP_MENU_SPACEHALF;
	}
}
/*清除上拉菜单残余图像*/
static void _clearMenuUp(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	// 重绘波形边框中被之前的上拉菜单覆盖的部分
	if(menu->frame.x0 <= WAVEWIN_EX) {
		if(menu->frame.x1 > WAVEWIN_EX) {
			GUI_SetColor(DesktopBkColor);
			GUI_FillRect(menu->frame.x0,menu->frame.y0,menu->frame.x1,SOFTKEY_SY-1);
			infobar_init(info->parent->infobar);
			menu->frame.x1 = WAVEWIN_EX;
		}
		GUI_SetColor(WAVEEXFRAME_DEFAULTCOLOR);
		GUI_DrawHLine(WAVEEXFRAME_EY, menu->frame.x0, menu->frame.x1);
	} else {
		GUI_SetColor(DesktopBkColor);
		GUI_FillRect(menu->frame.x0,menu->frame.y0,menu->frame.x1,SOFTKEY_SY-1);
		infobar_init(info->parent->infobar);
	}
	// 清除波形区域以外的上拉菜单残余图像
	GUI_SetColor(DesktopBkColor);
	GUI_FillRect(menu->frame.x0,WAVEEXFRAME_EY+1,menu->frame.x1, SOFTKEY_SY-1);
	// 显示当前菜单主题
	menu_displayPageTitle(*info);
}
/********************************************************************
* 
*                    public code
*
********************************************************************
*/
/********************************************************************
 *
 *                      绘制对话框框架和标题栏
 */
void menu_drawDialog(const char *title,GUI_RECT *frame) {
	// 绘制外框
	dso_drawLargeBarBk(*frame,BAR_FILLCOLOR);
	// 显示标题栏
	GUI_SetColor(BASE_FONTCOLOR);
	GUI_DispStringAt(title, frame->x0+5,frame->y0+4);
	GUI_SetColor(BAR_NEGEDGECOLOR);
	GUI_DrawHLine(frame->y0+19,frame->x0+1,frame->x1-1);
	GUI_SetColor(BAR_POSEDGECOLOR);
	GUI_DrawHLine(frame->y0+20,frame->x0+1,frame->x1-1);
}
/********************************************************************
 * 
 *                       绘制菜单基本框架
 */
void menu_drawFrame(MENUPAGE_INFO *info) {
	U16 c= GUI_GetColor();
	MENUUP_DATA *menu= info->sk[info->id].menuup;
	// 绘制框架
	menu_drawDialog(menu->title, &menu->frame);
	// 绘制指向父菜单的指示器
	{
		int i,temp= SOFTKEY_SX + (SOFTKEY_SPACE+bmsoftkeybk.XSize)*info->sk[info->id].id + bmsoftkeybk.XSize/2;
		GUI_SetColor(BAR_FILLCOLOR);
		for(i=0; i<10; i++) {
			LCD[menu->frame.y1+i][temp+9-i]= BAR_NEGEDGECOLOR;
			GUI_DrawHLine(menu->frame.y1+i,temp-8+i,temp+8-i);
			LCD[menu->frame.y1+i][temp-9+i]= BAR_POSEDGECOLOR;
		}
	}
	GUI_SetColor(c);
}
// 显示软键上的关键字
void menu_displaykword(MENUPAGE_INFO *info,U8 id) {
	SOFTKEY_DATA *sk=&info->sk[id];
	if(strcmp(sk->ktype,"nop") != 0) { // 显示关键字(图片/文字/参数)
		int sx = SOFTKEY_SX+(SOFTKEY_XSIZE+SOFTKEY_SPACE)*id;
		GUI_SetColor(BASE_FONTCOLOR);
		if(strstr(sk->ktype,"sicn")) {  // 关键字为软键数据中的图标
			GUI_DrawBitmap(sk->icon, sx+(bmsoftkeybk.XSize-sk->icon->XSize)/2,SOFTKEY_SY+SOFTKEY_KNOP_SY+GUI_GetFontSizeY()+3);
		} else {
			if(sk->menuup) {
				MENUITEM_DATA *item = &sk->menuup->item[menuup_calcItemIndex(*sk->menuup,sk->menuup->index)];
				if(strstr(sk->ktype,"micn")) {  // 关键字为上拉菜单选项中的图标
					GUI_DrawBitmap(item->icon, sx+(bmsoftkeybk.XSize-item->icon->XSize)/2,SOFTKEY_SY+SOFTKEY_KNOP_SY+GUI_GetFontSizeY()+3);
				} else if(strstr(sk->ktype,"text")) {  // 关键字为上拉菜单选项中的关键字
					GUI_DispStringHCenterAt(item->kword, sx+bmsoftkeybk.XSize/2,SOFTKEY_SY+SOFTKEY_KNOP_SY+GUI_GetFontSizeY()+3);
				}
			} else if(strstr(sk->ktype,"data")) {  // 关键字为数据

			}
		}
	}
}

/*******************************************************************
 *
 *                计算menuup->top
 */
void menuup_calcTop(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	int y0 = menu->client.y1;
	menu->top = menu->base;
	while(y0 > menu->client.y0) {
		y0 -= menu_calcItemYSize(menu->item[menuup_calcItemIndex(*menu,menu->top--)]);
		if(y0 <= menu->client.y0) break;
		y0 -= MENUUP_MENU_SPACE;
	}
	menu->top += 2;
}
/*******************************************************************
 *
 *                计算menuup->base
 */
void menuup_calcBase(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	int y1 = menu->client.y0;
	menu->base = menu->top;
	while(y1 < menu->client.y1) {
		y1 += menu_calcItemYSize(menu->item[menuup_calcItemIndex(*menu,menu->base++)]);
		if(y1 >= menu->client.y1) break;
		y1 += MENUUP_MENU_SPACE;
	};
	menu->base -= 2;
}
/********************************************************************
 * 
 *                       绘制上拉菜单
 */
void menu_preDraw1MenuUp(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	// 绘制框架
	menu_drawFrame(info);
	// 绘制菜单区内容
	if (menu->frame.y0 > WAVEWIN_SY) {
		_DrawMenuUp(info);
	} else {
		GUI_RECT r0;
		GUI_GetClientRect(&r0);
		GUI_SetClipRect(&menu->client);
		if(menu->dispdir == 0) {  // 之前为往下显示
			if(menu->index < menu->top) {  // 上移一项
				menu->top --;
				/*计算menu->base*/
				menuup_calcBase(info);
			} else if(menu->index > menu->base){  // 反向(往上)显示
				if(menu->index == menu->menun-1) { // 超过下限
					menu->base = menu->menun-1;
				} else { // 下移一项
					menu->base ++;
				}
				menu->dispdir = 1;  // 往上显示
				/*计算menu->top*/
				menuup_calcTop(info);
			}
		} else {  // 之前为往上显示
			if(menu->index > menu->base) {  // 下移一项
				menu->base ++;
				/*计算menu->top*/
				menuup_calcTop(info);
			} else if(menu->index < menu->top){  // 反向(往下)显示
				if(menu->index == 0) {
					menu->top = 0;
				} else { // 上移一项
					menu->top --;
				}
				menu->dispdir = 0;  // 往下显示
				/*计算menu->base*/
				menuup_calcBase(info);
			}
		}
		/*显示上拉菜单选项*/
		if(menu->dispdir == 0)
			_DrawFromUp(info);
		else
			_DrawFromDown(info);
		/*恢复...*/
		GUI_SetClipRect(&r0);
		// 绘制上下滑动指示器
		if(menu->top > 0) {
			GUI_DrawBitmap(&bmMenuIndicatorToUp,(menu->frame.x0+menu->frame.x1-bmMenuIndicatorToUp.XSize)/2,menu->frame.y0+23); // 
		}
		if(menu->base < menu->menun-1) {
			GUI_DrawBitmapEx(&bmMenuIndicatorToUp,(menu->frame.x0+menu->frame.x1)/2,menu->frame.y1-bmMenuIndicatorToUp.YSize/2-2, \
				bmMenuIndicatorToUp.XSize/2,bmMenuIndicatorToUp.YSize/2-1,1000,-1000);  //
		}
	}
	// 将刚才画到LCD的菜单[波形区域范围内部分]Copy到MenuUpBuff[]中暂存
	{
		int y;
		int size = (menu->frame.x1-menu->frame.x0+1)*size_U16;
		for(y=menu->frame.y0; y<=WAVEWIN_EY; y++)
			memcpy(menubuff[y-menu->frame.y0], LCD[y]+menu->frame.x0,size);
	}
	if(info->hide == 1) {
		_clearMenuUp(info);
	}
}  
// 恢复上次可能存在的被上拉菜单覆盖的静态画面
void menu_clearMenuUp(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	if(!menu) return ;
	thread_lock();
	info->hide = 1;
	info->enExt = 0;
	_clearMenuUp(info);
	// 刷新波形窗口
	wave_fresh();
	// 清DPO缓存
	dpo_clearAll(info->parent->wave_info->ch);
	thread_unlock();
}
// 将制给定区域像素集copy到给定的menubuff中
void menu_copyToAreaBuff(GUI_RECT *rect) {
	int y;
	int size = (rect->x1 - rect->x0+1)*size_U16;
	for(y=rect->y0; y<=rect->y1; y++)
		memcpy(areabuf[y-rect->y0],LCD[y]+rect->x0,size);
}
// 将当前菜单缓冲区的有效数Copy到虚拟屏对应位置
void menu_displayActivate(GUI_RECT *rect) {
	int y;
	int size = (rect->x1 - rect->x0+1)*size_U16;
	for(y=rect->y0; y<=WAVEWIN_EY; y++)
		memcpy(LCD[y]+rect->x0, menubuff[y-rect->y0],size);
}
// 将当前菜单缓冲区的有效数据Copy到虚拟屏对应位置
void menu_displayMenuHelp(MENUUP_DATA *menu,GUI_RECT *rect) {
	int y;
	int size = (rect->x1 - rect->x0+1)*size_U16;
	for(y=rect->y0; y<=rect->y1; y++)
		memcpy(LCD[y]+rect->x0, menubuff[y-rect->y0]+menu->width,size);
}
// 将当前菜单缓冲区的有效数据Copy到虚拟屏对应位置
void menu_displayArea(GUI_RECT *rect) {
	int y;
	int size = (rect->x1 - rect->x0+1)*size_U16;
	for(y=rect->y0; y<=rect->y1; y++)
		memcpy(LCD[y]+rect->x0, areabuf[y-rect->y0],size);
}
/*************************************************************
 *
 *                      menu task
 */
void menu_task(MENUPAGE_INFO *info) {
	MENUUP_DATA  *menu=info->sk[info->id].menuup;
	if (info->hide == 0) {
		if(info->enExt == 1){
			menu_displayMenuHelp(menu,&info->extFrame);
		}
		menu_displayActivate(&menu->frame);
	} else if(info->enExt == 1) {
		info->enhide = 0;
		menu_displayArea(&info->extFrame);
	}
}
