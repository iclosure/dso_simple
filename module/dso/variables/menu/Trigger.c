
#include "menu.h"

/**************************************************************
 * 
 *                     触发类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA  _item6_page_sk1[]= {
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA item6_page_sk1= {4,_item6_page_sk1,&menuTrigger,"110000"};
/**************************************/
static SOFTKEY_DATA  _item7_page_sk1[]= {
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA item7_page_sk1= {4,_item7_page_sk1,&menuTrigger,"110000"};
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{0, MENUUP_IF_MENU,},
	{1, MENUUP_IF_MENU,},
	{2, MENUUP_IF_MENU,},
	{3, MENUUP_IF_MENU,},
	{4, MENUUP_IF_MENU,},
	{5, MENUUP_IF_MENU,},
	{6, MENUUP_IF_MENU,NULL,&item6_page_sk1},
	{7, MENUUP_IF_MENU,NULL,&item7_page_sk1},
};
static MENUUP_DATA sk1_menuup= {8,_sk1_menuup,&menuTrigger,};
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{0, MENUUP_IF_MENU,},
	{1, MENUUP_IF_MENU,},
	{2, MENUUP_IF_MENU,},
	{3, MENUUP_IF_MENU,},
	{4, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk2_menuup= {5,_sk2_menuup,&menuTrigger,};
/**************************************/
static MENUITEM_DATA _sk3_menuup[]= {
	{0, MENUUP_IF_MENU,&bmSlopeRisingEdge,},
	{1, MENUUP_IF_MENU,&bmSlopeFallingEdge,},
	{2, MENUUP_IF_MENU,&bmSlopeAlternatingEdge,},
	{3, MENUUP_IF_MENU,&bmSlopeAnyEdge,},
};
static MENUUP_DATA sk3_menuup= {4,_sk3_menuup,&menuTrigger,mfTrigger_slop};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_STATIC,NULL,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,NULL,NULL,&sk3_menuup},
};
MENUPAGE_DATA menuTrigger= {3,sk,};
