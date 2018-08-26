
#include "menu.h"

/**************************************************************
 * 
 *                     语言设置类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
	{ 4, MENUUP_IF_MENU,},
	{ 5, MENUUP_IF_MENU,},
	{ 6, MENUUP_IF_MENU,},
	{ 7, MENUUP_IF_MENU,},
	{ 8, MENUUP_IF_MENU,},
	{ 9, MENUUP_IF_MENU,},
	{10, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {11,_sk1_menuup,&menuLanguage,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_STATIC,mfLanguage_AutoSet,},
	{2,SOFTKEY_IF_STATIC,mfLanguage_Enter,},
};
MENUPAGE_DATA menuLanguage= {3,sk,};
