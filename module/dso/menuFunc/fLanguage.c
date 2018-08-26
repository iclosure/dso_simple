
#include "menuFunc.h"
#include "menu.h"
#include "wave.h"
#include "dso.h"
#include <string.h>


void* mfLanguage_AutoSet(PROJECT_INFO *info,I8 id) {
	if(info->page_info->sk[0].menuup->status==0 || info->page_info->sk[0].menuup->index != eEnglish) {
		menuup_clrStatus(info->page_info->sk[0].menuup,info->page_info->sk[0].menuup->index);
		menuup_setStatus(info->page_info->sk[0].menuup,eEnglish);
		info->page_info->sk[0].menuup->index  = eEnglish;
		info->page_info->sk[0].menuup->status = 1;
		mfLanguage_Enter(info,id);
	}

	return NULL;
}
// ѡ������
void* mfLanguage_Enter(PROJECT_INFO *info,I8 id) {
	if(info->page_info->now) {  // ����֮ǰ���ܵĲ˵�ҳ����
		GUI_SetBkColor(DesktopBkColor);
		GUI_ClearRect(SOFTKEY_SX,SOFTKEY_SY-GUI_GetFontDistY()-2, \
			SOFTKEY_SX+GUI_GetStringDistX(info->page_info->now->title),SOFTKEY_SY-2);
	}
	/*��ʼ���˵��ı�*/
	info->page_info->langtype = (LANGUAGE_TYPE) info->page_info->sk[0].menuup->index;
	GUI_SetFont(font_all[info->page_info->langtype]);
	menu_init(info->page_info);
	// 
	mfMeasure_freshSKTitle(info->page_info);
	// ������Ļ��ʾ
	menu_displayPageTitle(*info->page_info);
	menu_setNewSoftKey(info->page_info,info->page_info->now);
	info->page_info->sk[info->page_info->id].option = SOFTKEY_IF_ACTIVATE;
	menu_drawOneSoftKey(info->page_info,0,id);
	/*ˢ��״̬����Ϣ*/
	{
		MENUUP_DATA *menu2=menu_all[eAutoScale]->sk[2].menuup;
		info->statusbar->trigsource	= &menu2->item[menu2->index].kword;
		statusbar_initStatic(info->statusbar);
	}
	/*ˢ����Ϣ����Ϣ*/
	infobar_init(info->infobar);
	/*ˢ�²�����ʾ��Ϣ*/
	param_init(info);

	return NULL;
	// 
}