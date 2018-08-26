
#include "menuFunc.h"
#include "menu.h"
#include "wave.h"
#include "dso_unit.h"
#include "dso_confDefaults.h"
#include <string.h>
#include "GUI_Protected.h"

/**************************************************************
 *
 *                       参数单位列表
 *                    [1/25/2012 robot]
 * 说明：第五列为常用单位
 */
static const char **measure_param_unit[] = {
	param_unit_volt, // 峰-峰值
	param_unit_volt, // 最大电平
	param_unit_volt, // 最小电平
	param_unit_volt, // 幅度
	param_unit_volt, // 高值
	param_unit_volt, // 低值
	param_unit_rate, // 过冲
	param_unit_rate, // 前冲
	param_unit_volt, // 平均 - 周期
	param_unit_volt, // 平均 - 全屏
	param_unit_volt, // DC-RMS - 周期
	param_unit_volt, // DC-RMS - 全屏
	param_unit_volt, // AC-RMS - 周期
	param_unit_volt, // AC-RMS - 全屏(标准差)
	param_unit_rate, // 比例
	param_unit_time, // 周期
	param_unit_freq, // 频率
	param_unit_degree, // 相位
	param_unit_time, // + 脉宽
	param_unit_time, // - 脉宽
	param_unit_time, // 促发脉宽
	param_unit_rate, // 占空比
	param_unit_time, // 上升时间
	param_unit_time, // 下降时间
	param_unit_time, // X@Min
	param_unit_time, // X@Max
	param_unit_none, // + 脉冲计数
	param_unit_none, // - 脉冲计数
	param_unit_time, // 上升沿
	param_unit_time, // 下降沿
	param_unit_time, // 区域 - 周期
	param_unit_time, // 区域 - 全屏
};
/*************************************************************
 *
 *                      static code 
 *
 *************************************************************
 */

/************************************************************
 *
 *                        显示参数快照
 *                     [1/25/2012 robot]
 */
static void* mfMeasure_fastView(PROJECT_INFO *info,I8 id) {
	SOFTKEY_DATA *sk=info->page_info->sk;
	MENUPAGE_INFO *page_info=info->page_info;
	MENUUP_DATA *menu1=page_info->sk[1].menuup;
	CHANNEL_DATA *ch_list=&info->wave_info->ch->ch[sk[0].menuup->index];
	t_param *paramlist=ch_list->measure.param.list;
	int dy=0,lcdindex = LCD_GetLCDIndex();
	char str[20];
	int index=0;
	GUI_RECT r0;
	LCD_SelectLCD(2);
	GUI_GetClientRect(&r0);
	GUI_SetClipRect(&page_info->extClient);

	GUI_SetBkColor(BAR_FILLCOLOR);
	GUI_ClearRectEx(page_info->extClient);
	GUI_SetTextMode(GUI_DRAWMODE_NORMAL);
	GUI_GotoXY(page_info->extClient.x0,page_info->extClient.y0);
	while(index < 32) {
		GUI_SetColor(BASE_FONTCOLOR);
		GUI_DispString(menu1->item[menuup_calcItemIndex(*menu1,index)].kword);
		GUI_DispStringAt(": ",page_info->extClient.x0+dy+80,GUI_GetDispPosY());
		param_toStringWithUnit(str,&paramlist[index],measure_param_unit[index]);
		strcat(str,"\n");
		GUI_SetColor(color_lightyellow);
		GUI_DispString(str);
		if(++index == 16) {
			GUI_GotoY(page_info->extClient.y0);
			dy = 200;
		}
		GUI_GotoXY(page_info->extClient.x0+dy,GUI_GetDispPosY() + 2);
	}
	GUI_SetTextMode(GUI_DRAWMODE_TRANS);
	// 
	menu_copyToAreaBuff(&page_info->extFrame);

	GUI_SetClipRect(&r0);
	LCD_SelectLCD(lcdindex);
	if(ch_list->status == 0) {
		page_info->enExt = 0;
	}

	return NULL;
}
/*************************************************************
 *
 *                     public code 
 *
 *************************************************************
 */
/**/
void* mfMeasure_dispFastView(PROJECT_INFO *info,I8 id) {
	MENUUP_DATA *menu0=info->page_info->sk[0].menuup;
	MENUUP_DATA *menu1=info->page_info->sk[1].menuup;
	if(menu1->item[menu1->itemn-1].status==1 && info->wave_info->ch->ch[menu0->index].status==1) {
		MENUPAGE_INFO *page_info=info->page_info;
		GUI_RECT *extFrame=&page_info->extFrame;
		GUI_RECT *extClient=&page_info->extClient;
		GUI_RECT r0;
		I16 height;
		int lcdindex = LCD_GetLCDIndex();

		info->page_info->task = mfMeasure_fastView;
		info->page_info->hide  = 1;
		info->page_info->enExt = 1;

		GUI_GetClientRect(&r0);
		height = (GUI_GetFontSizeY()+2)*16+MENUUP_TOPTITLE_HEIGHT+10;
		extFrame->x0 = WAVEWIN_XMID-200;
		extFrame->y0 = WAVEWIN_YMID-height/2;
		extFrame->x1 = WAVEWIN_XMID+200;
		extFrame->y1 = WAVEWIN_YMID+height/2;
		extClient->x0 = extFrame->x0 + 5;
		extClient->y0 = extFrame->y0 + MENUUP_TOPTITLE_HEIGHT + 5;
		extClient->x1 = extFrame->x1 - 5;
		extClient->y1 = extFrame->y1 - 5;

		GUI_SetClipRect(extFrame);
		LCD_SelectLCD(2);
		// 绘制外框
		menu_drawDialog(menu0->item[menu0->index].title,extFrame);
		// 
		menu_copyToAreaBuff(extFrame);

		GUI_SetClipRect(&r0);
		LCD_SelectLCD(lcdindex);
	}
	return NULL;
}
/**/
void* mfMeasure_addMeas(PROJECT_INFO *info,I8 id) {
	SOFTKEY_DATA *sk=info->page_info->sk;
	INFOBAR_PARAMLIST *list=&info->infobar->param_list[info->infobar->param_n];
	if(info->wave_info->ch->ch[sk[0].menuup->index].status==1 && sk[1].menuup->status==1 && info->infobar->param_n<5) { // 还没有填满参数显示区
		U8 index=menuup_calcItemIndex(*sk[1].menuup,sk[1].menuup->index);
		if(index < sk[1].menuup->itemn-1) {
			const char *title=sk[4].next->sk[info->infobar->param_n].title;
			list->id	= sk[0].menuup->index;
			list->name	= &sk[1].menuup->item[index].kword;
			list->value	= &info->wave_info->ch->ch[list->id].measure.param.list[sk[1].menuup->index];
			list->unit	= measure_param_unit[sk[1].menuup->index];
			sk[4].next->sk[5].option = SOFTKEY_IF_STATIC;
			sk[4].next->sk[info->infobar->param_n].option = SOFTKEY_IF_STATIC;
			while(*title++ != '\n');
			sprintf((char*)title,"%s",*list->name);
			info->infobar->param_n++;
			infobar_initParamArea(info->infobar);
		} 
	}
	return NULL;
}
/**/
void* mfMeasure_delMeas(PROJECT_INFO *info,I8 id) {
	INFOBAR_INFO *infobar=info->infobar;
	if(infobar->param_n > 0) {
		INFOBAR_PARAMLIST *list;
		const char *title;
		infobar->param_n --;
		list = &infobar->param_list[infobar->param_n];
		title=info->page_info->sk[id].title;
		while(*title++ != '\n');
		sprintf((char*)title,"%s","<None>");
		if(infobar->param_n == 0)
			info->page_info->sk[id].option = SOFTKEY_IF_NOBK;
		info->page_info->sk[id].option = SOFTKEY_IF_NOBK;
		menu_drawOneSoftKey(info->page_info,0,id);
		infobar_initParamArea(infobar);
		if(id == 5) {
			infobar->param_n = 0;
			infobar_draw(infobar);
		}
	}
	return NULL;
}
/**/
void mfMeasure_freshSKTitle(MENUPAGE_INFO *info) {
	INFOBAR_INFO *infobar=info->parent->infobar;
	if(infobar->param_n > 0) {
		int index=0;
		const char *title;
		INFOBAR_PARAMLIST *list;
		do {
			list=&infobar->param_list[index];
			title=info->sk[4].next->sk[index].title;
			while(*title++ != '\n');
			sprintf((char*)title,"%s",*list->name);
		} while(++index < infobar->param_n);
	}
}
