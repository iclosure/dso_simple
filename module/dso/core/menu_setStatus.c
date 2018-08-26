
#include "dso_confDefaults.h"
#include "dso.h"
#include "menu.h"

/*******************************************************************
 *
 *                   static code
 */

/*******************************************************************
 *
 *                   public code
 */
// ���������˵���ĳ��˵�ѡ���ƫ������ֵ
int menuup_calcItemIndex(MENUUP_DATA menu, U8 id) {
	I8 i=0,j=0;
// 	do {  //�ҵ���һ���˵�ѡ��
// 		if(menu.item[i].option == MENUUP_IF_MENU) break;
// 	} while(++i < menu.itemn);
	do {
		if(menu.item[i].option == MENUUP_IF_MENU) {
			if(j == id)
				return i;
			j++;
		}
	} while(++i < menu.itemn);

	return 0;
}
/*******************************************************************
 *
 *                ��������[�˵���]״̬λ
 *  ����˵��: n--��ʾѡ�еڼ���˵�[�������ָ��ߺͱ�����],
 */
void menuup_setStatus(MENUUP_DATA *menu, U8 id) {
	menu->item[menuup_calcItemIndex(*menu,id)].status= 1;
}
/*******************************************************************
*
*                �������[�˵���]״̬λ
*/
void menuup_clrStatus(MENUUP_DATA *menu, U8 id) {
	menu->item[menuup_calcItemIndex(*menu,id)].status= 0;
}
/*******************************************************************
*
*                �������[���в˵���]״̬λ
*/
void menuup_clrAllStatus(MENUUP_DATA *menu) {
	I8 n= menu->menun;
	while(n--) {
		menuup_clrStatus(menu, n);
	}
}
// ��ȡ�����˵�ѡ���д���ѡ��״̬��id��(������ֵС��0,���ʾû��ѡ�еĲ˵���)
int menuup_getActionId(MENUUP_DATA menu) {
	int i=0;
	while(i < menu.menun) {
		if(menu.item[menuup_calcItemIndex(menu,i)].status == 1) {
			return menuup_calcItemIndex(menu,i);
		}
		i++;
	}
	return -1;  /*û��ѡ�в˵���*/
}

