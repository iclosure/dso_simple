
/****************************************************************
 *                  信息区域信息显示类函数功能实现
 */
#include "GUI.h"
#include "GUI_Protected.h"
#include "dso.h"
#include "menu.h"
#include "wave.h"
#include "dso_fileDir.h"
#include "target.h"
#include "thread.h"
#include <string.h>
#include <stdio.h>


/**********************************************************
 *
 *                 系统信息(变量、??)
 */
INFOBAR_INFO	infobar			;  /*信息栏数据信息*/

/************************************************************************/
/*                         public code                                  */
/************************************************************************/
// 信息栏数据初始化
void infobar_init(INFOBAR_INFO *info) {
	/**/
	info->logo_rect.x0	= INFOBAR_SX;
	info->logo_rect.y0	= INFOBAR_SY;
	info->logo_rect.x1	= INFOBAR_EX;
	info->logo_rect.y1	= INFOBAR_SY+INFOBAR_LOGO_HEIGHT+6;
	/**/
	info->acq_rect.x0	= INFOBAR_SX;
	info->acq_rect.y0	= INFOBAR_ACQ_SY;
	info->acq_rect.x1	= INFOBAR_EX;
	info->acq_rect.y1	= INFOBAR_ACQ_SY+INFOBAR_ACQ_HEIGHT+TITLEBAR_YSIZE+3;
	/**/
	info->ch_rect.x0	= INFOBAR_SX;
	info->ch_rect.y0	= INFOBAR_CH_SY;
	info->ch_rect.x1	= INFOBAR_EX;
	info->ch_rect.y1	= INFOBAR_CH_SY+(GUI_GetFontSizeY()*4+10)+TITLEBAR_YSIZE+2;
	/**/
	info->param_rect.x0	= INFOBAR_SX;
	info->param_rect.y0	= info->ch_rect.y1-4;
	info->param_rect.x1	= INFOBAR_EX;
	info->param_rect.y1	= WAVEWIN_EY-10;
	info->param_client.x0	= info->param_rect.x0+4;
	info->param_client.y0	= info->param_rect.y0+TITLEBAR_YSIZE+4;
	info->param_client.x1	= info->param_rect.x1-4;
	info->param_client.y1	= info->param_rect.y1-5;
	/*LOGO显示*/
	dso_drawLargeBarBk(info->logo_rect,BAR_FILLCOLOR);
	GUI_DrawBitmap(&bmLogo,info->logo_rect.x0+(INFOBAR_XSIZE-bmLogo.XSize)/2,\
		info->logo_rect.y0+(INFOBAR_LOGO_HEIGHT+5-bmLogo.YSize)/2);
	/*动态参数显示*/
	infobar_draw(info);
}
/*绘制信息栏*/
void infobar_draw(INFOBAR_INFO *info) {
	char str[80];
	/*采集信息显示*/
	dso_drawFrame(info->acq_rect,BAR_FILLCOLOR,menuAutoScale.sk[3].title);
	sprintf(str,"%s\n%.2f%s",*info->acq_mode,12.5,"MSa/s");
	GUI_DispStringHCenterAt(str,info->acq_rect.x0+INFOBAR_XSIZE/2,info->acq_rect.y0+TITLEBAR_YSIZE+2);
	/*通道信息显示*/
	dso_drawFrame(info->ch_rect,BAR_FILLCOLOR,menuAutoScale.sk[2].title);
	infobar_dispChannel(info);
	/*数据显示*/
	infobar_initParamArea(info);
}
/**/
void infobar_dispAcq(INFOBAR_INFO *info) {

}
/**/
void infobar_dispChannel(INFOBAR_INFO *info) {
	int i;
	char str[80];
	const GUI_FONT *font0=GUI_GetFont();
	GUI_GotoY(info->ch_rect.y0+TITLEBAR_YSIZE+5);
	GUI_SetFont(font_all[eSimplifiedChinese]);
	for(i=0; i<4; i++) {  /**/
		GUI_SetColor(info->ch_data[i].color);
		GUI_GotoX(info->ch_rect.x0+INFOBAR_XSIZE/2+1);
		sprintf(str,"DC     %10.1f:1\n",info->ch_data[i].zoom);
		GUI_SetTextAlign(GUI_TA_HCENTER);
		GUI_DispString(str);
	}
	GUI_SetFont(font0);
}
/*初始化信息栏中参数显示的静态部分*/
void infobar_initParamArea(INFOBAR_INFO *info) {
	if(info->param_n > 0) {
		int i;
		char str[80];
		dso_drawFrame(info->param_rect,BAR_FILLCOLOR,info->parent->page_info->now->kword);
		GUI_GotoY(info->param_client.y0);
		for(i=0; i<info->param_n; i++) {
			sprintf(str,"%s(",*info->param_list[i].name);
			GUI_DispStringAt(str,info->param_client.x0,GUI_GetDispPosY());
			GUI_SetColor(info->parent->wave_info->ch->ch[info->param_list[i].id].color);
			sprintf(str,"%d",info->param_list[i].id+1);
			GUI_DispString(str);
			GUI_SetColor(BASE_FONTCOLOR);
			GUI_DispString("): \n");
			GUI_GotoY(GUI_GetDispPosY()+GUI_GetFontSizeY()+7);
			//draw seperate line
			GUI_DrawHLine(GUI_GetDispPosY()-2,info->param_client.x0,info->param_client.x1);
		}
	}
}
/*向信息栏的参数列表增加一个参数*/
void infobar_addParam(INFOBAR_INFO *info,U8 id,t_param *value) {
	
}
/*从信息栏的参数列表删除一个参数*/
void infobar_delParam(INFOBAR_INFO *info,U8 id,t_param *value) {

}
/**/
void infobar_dispParam(INFOBAR_INFO *info) {
	if(info->param_n > 0) {
		int i;
		char str[80];
		GUI_COLOR c0=GUI_GetBkColor();
		GUI_SetBkColor(BAR_FILLCOLOR);
		GUI_SetColor(color_lightyellow);
		GUI_GotoY(info->param_client.y0);
		for(i=0; i<info->param_n; i++) {
			int x1= info->param_client.x1;
			GUI_GotoXY(x1,GUI_GetDispPosY()+GUI_GetFontSizeY()+5);
			GUI_ClearRect(info->param_client.x0,GUI_GetDispPosY(),x1,GUI_GetDispPosY()+GUI_GetFontSizeY()-1);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			param_toStringWithUnit(str,info->param_list[i].value,info->param_list[i].unit);
			GUI_DispString(str);
			GUI_GotoY(GUI_GetDispPosY()+GUI_GetFontSizeY()+2);
		}
		GUI_SetBkColor(c0);
	}
}
