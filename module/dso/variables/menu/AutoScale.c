
#include "menu.h"

/**************************************************************
 * 
 *                     自动定标类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk3_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
	{ 4,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk3_menuup= {5,_sk3_menuup,&menuAutoScale,mfAutoScale_SelChannels};
/**************************************/
static MENUITEM_DATA _sk4_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk4_menuup= {1,_sk4_menuup,&menuAutoScale,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_RECT,},
	{2,SOFTKEY_IF_STATIC,NULL,NULL,&sk3_menuup},
	{3,SOFTKEY_IF_STATIC,NULL,NULL,&sk4_menuup},
};
MENUPAGE_DATA menuAutoScale= {4,sk};
