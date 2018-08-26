
#include "menu.h"

/**************************************************************
 * 
 *                     光标设置类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk4_sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk4_sk1_menuup= {4,_sk4_sk1_menuup,};
/**************************************/
static MENUITEM_DATA _sk4_sk3_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk4_sk3_menuup= {2,_sk4_sk3_menuup,};
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {4,_sk1_menuup,};
/**************************************/
static SOFTKEY_DATA _subsk4[]= {
	{0,SOFTKEY_IF_STATIC, NULL,NULL,&sk4_sk1_menuup,},
	{1,SOFTKEY_IF_STATIC, NULL,},
	{2,SOFTKEY_IF_STATIC, NULL,NULL,&sk4_sk3_menuup,},
	{3,SOFTKEY_IF_STATIC, NULL,},
};
static MENUPAGE_DATA subsk4 = {4,_subsk4,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC, NULL,NULL,&sk1_menuup,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_NEXT, NULL,&subsk4},
};
MENUPAGE_DATA menuCursorSet= {4,sk,};
