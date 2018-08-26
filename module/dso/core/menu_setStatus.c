
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
// 计算上拉菜单中某项菜单选项的偏移索引值
int menuup_calcItemIndex(MENUUP_DATA menu, U8 id) {
	I8 i=0,j=0;
// 	do {  //找到第一个菜单选项
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
 *                设置上拉[菜单项]状态位
 *  参数说明: n--表示选中第几项菜单[不包括分隔线和标题项],
 */
void menuup_setStatus(MENUUP_DATA *menu, U8 id) {
	menu->item[menuup_calcItemIndex(*menu,id)].status= 1;
}
/*******************************************************************
*
*                清除上拉[菜单项]状态位
*/
void menuup_clrStatus(MENUUP_DATA *menu, U8 id) {
	menu->item[menuup_calcItemIndex(*menu,id)].status= 0;
}
/*******************************************************************
*
*                清除上拉[所有菜单项]状态位
*/
void menuup_clrAllStatus(MENUUP_DATA *menu) {
	I8 n= menu->menun;
	while(n--) {
		menuup_clrStatus(menu, n);
	}
}
// 获取上拉菜单选项中处于选中状态的id号(若返回值小于0,则表示没有选中的菜单项)
int menuup_getActionId(MENUUP_DATA menu) {
	int i=0;
	while(i < menu.menun) {
		if(menu.item[menuup_calcItemIndex(menu,i)].status == 1) {
			return menuup_calcItemIndex(menu,i);
		}
		i++;
	}
	return -1;  /*没有选中菜单项*/
}

