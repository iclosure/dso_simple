
#include "menu.h"

/**************************************************************
 * 
 *                     打印配置类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk2_menuup= {4,_sk2_menuup,&menuPrintSet,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk4[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk4 = {2,_subsk4,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC, NULL,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_NEXT,NULL,&subsk4,},
};
MENUPAGE_DATA menuPrintSet= {4,sk};
