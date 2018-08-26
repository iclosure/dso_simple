
#include "menu.h"

/**************************************************************
 * 
 *                     水平设置类::水平设置变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {3,_sk1_menuup,&menuHorizontalSet,};
/**************************************/
static MENUITEM_DATA _sk6_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk6_menuup= {3,_sk6_menuup,&menuHorizontalSet,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_RECT,},
	{4,SOFTKEY_IF_RECT,},
	{5,SOFTKEY_IF_STATIC,NULL,NULL,&sk6_menuup},
};
MENUPAGE_DATA menuHorizontalSet= {4,sk,};
