
#include "dso_type.h"
#include "dso_confDefaults.h"
#include "GUI.h"
#include "menu.h"
#include <stdlib.h>


GUI_RECT StatusBarArea= {STATUSBAR_SX,STATUSBAR_SY,STATUSBAR_EX,STATUSBAR_EY};  // �ұ���
/**********************************************************
 *
 *                 ϵͳ��Ϣ(������??)
 */
STATUSBAR_INFO	statusbar			;  /*״̬��������Ϣ*/

/************************************************************************/
/*                         static code                                  */
/************************************************************************/

/************************************************************************/
/*                         public code                                  */
/************************************************************************/
/********************************************************************
 *
 *                        ״̬����غ���
 */
/*��ʼ��״̬��*/
void statusbar_initStatic(STATUSBAR_INFO *info) {
	int i;
	/**/
	info->rect.x0	= STATUSBAR_SX;
	info->rect.y0	= STATUSBAR_SY;
	info->rect.x1	= STATUSBAR_EX;
	info->rect.y1	= STATUSBAR_EY;

	GUI_SetBkColor(DesktopBkColor);
	GUI_ClearRectEx(info->rect);
	for(i=0; i<info->parent->wave_info->ch->n; i++) {
		GUI_SetColor(info->parent->wave_info->ch->ch[i].color);
		GUI_DispDecAt(i+1,info->rect.x0+84*i,info->rect.y0,1);
		statusbar_dispChannelSens(info,i);
	}
	statusbar_dispDelayTime(info);
	statusbar_dispTimeDiv(info);
	statusbar_dispRunOrStop(info,NULL);
	statusbar_dispTriggerType(info,NULL);
	statusbar_dispTriggerSource(info,NULL);
	statusbar_dispTriggerLevel(info);
}
/*��ʾͨ���ֱ���*/
void statusbar_dispChannelSens(STATUSBAR_INFO *info,U8 id) {
	GUI_SetColor(BASE_FONTCOLOR);
	
}
/*��ʾ��ʱ*/
void statusbar_dispDelayTime(STATUSBAR_INFO *info) {
	GUI_DispStringAt("0.0s",430,info->rect.y0);
}
/*��ʾʱ��ֱ���*/
void statusbar_dispTimeDiv(STATUSBAR_INFO *info) {
	const GUI_FONT *font=GUI_GetFont();
	GUI_SetFont(&GUI_Font6x8);
	GUI_DispStringAt("u\n",502,info->rect.y0);
	GUI_GotoX(502);
	GUI_DispChar('v');
	GUI_SetFont(font);
	GUI_GotoY(info->rect.y0);
	GUI_DispChar('/');
}
/*��ʾ����(1)/ֹͣ״̬(0)*/
void statusbar_dispRunOrStop(STATUSBAR_INFO *info,const char *runstatus) {
	if(runstatus) {
		GUI_ClearStringAt("    ",599,info->rect.y0);
		info->runstatus = &runstatus;
	}
	GUI_SetColor(BASE_FONTCOLOR);
	GUI_DispStringAt(*info->runstatus,599,info->rect.y0);
}
/*��ʾ��������*/
void statusbar_dispTriggerType(STATUSBAR_INFO *info,const GUI_BITMAP *icon) {
	if(icon) {
		GUI_ClearBitmap(info->trigtype,info->rect.x0+665,info->rect.y0,DesktopBkColor);
		info->trigtype = icon;
	}
	GUI_DrawBitmap(info->trigtype,info->rect.x0+665,info->rect.y0);
}
/*��ʾ����Դ*/
void statusbar_dispTriggerSource(STATUSBAR_INFO *info,const char *trigsource) {
	if(trigsource) {
		GUI_ClearStringAt("    ",695,info->rect.y0);
		info->trigsource = &trigsource;
	}
	if(atoi(*info->trigsource) > 0)  /*�ų�"All"("ȫ��")*/
		GUI_SetColor(info->parent->wave_info->ch->ch[atoi(*info->trigsource)-1].color);
	GUI_DispStringAt(*info->trigsource,695,info->rect.y0);
}
/*��ʾ������ƽ��������ֵ*/
void statusbar_dispTriggerLevel(STATUSBAR_INFO *info) {
	GUI_SetColor(BASE_FONTCOLOR);
	GUI_DispStringAt("0.00V/",739,info->rect.y0);
}
