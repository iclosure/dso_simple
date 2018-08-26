
#include "menu.h"
#include "dso.h"
#include "thread.h"
#include <stdlib.h>
#include <string.h>


/*******************************************************************
 *
 *                     public code
 */

/*******************************************************************
 *
 *                       menu new
 */
/*dirΪ���÷������(back: -1);���ߵ�ǰ(next: 0); ������ǰ(next: 1)*/
void menu_setNewPage(MENUPAGE_INFO *info, MENUPAGE_DATA *page,I8 dir) {
	if(info->id>=0 && info->sk[info->id].menuup) {  // ���֮ǰ���ܵ������˵�
		menu_clearMenuUp(info);
		info->hide = 1;

	} 
	if(info->now) {  // ����֮ǰ���ܵĲ˵�ҳ����
		GUI_SetBkColor(DesktopBkColor);
		GUI_ClearRect(SOFTKEY_SX,SOFTKEY_SY-GUI_GetFontSizeY()-2, \
			SOFTKEY_SX+GUI_GetStringDistX(info->now->title),SOFTKEY_SY-2);
	}
	info->enhide	= 1;
	info->task		= NULL;
	if(dir > 0) {
		info->back	= info->now;
		info->next	= NULL;
	} else if(dir < 0) {
		if(page->back)
			info->back	= page->back;
		else 
			info->back	= NULL;
		info->next	= info->now;
	} else {
		info->hide	=-1;
		info->back	= page->back;
		info->next	= NULL;
	}
	info->now		= page;
	menu_setNewSoftKey(info,page);
	menu_displayPageTitle(*info);
	infobar_init(info->parent->infobar);
}
/**/
void menu_setNewSoftKey(MENUPAGE_INFO *info, MENUPAGE_DATA *page) {
	I8 i=0,j=0;
	I8 skId=-1;
	I8 index=-1;
	do {
		if(page->others && page->others[i]=='1')
			continue;
		if(j < page->n && i == page->sk[j].id) {
			if(info->sk[i].option == SOFTKEY_IF_MENU && !info->parent->key_info->ischange) { 
				j++; continue;  // ������ǰ���ڼ���״̬�������˵�ѡ�������
			}
			info->sk[i]= page->sk[j++];
		} else if(page->others && page->others[i]=='0') {
			info->sk[i].option = SOFTKEY_IF_EMPTY;
		} else {
			if(page->others && info->sk[i].option==SOFTKEY_IF_MENU)
				continue;  // ������ǰ���ڼ���״̬�������˵�ѡ�������
			info->sk[i].option = SOFTKEY_IF_EMPTY;
		}
		// 
		menu_drawOneSoftKey(info,0,i);
		if(info->sk[i].menuup && info->sk[i].menuup->status==1) {
			U8 temp= menuup_calcItemIndex(*info->sk[i].menuup,info->sk[i].menuup->index);
			if(info->sk[i].menuup->item[temp].next) {  // �����˵���ѡ������������
				skId = i; index = temp;
			}
		}
	} while(++i < 6);

	if(index >= 0) {  // ���������˵���ѡ������ڵ������
		I8 id=info->id;
		info->sk[skId].menuup->item[index].status = 1;
		info->id = skId;
		menu_preDraw1MenuUp(info);
		menu_clearMenuUp(info);
		info->id = id;
		menu_drawOneSoftKey(info,0,skId);
	}
}

