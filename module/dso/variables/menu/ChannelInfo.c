
#include "menu.h"

/**************************************************************
 * 
 *                     通道X类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {2,_sk1_menuup,};
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
	{ 4,MENUUP_IF_MENU,},
	{ 5,MENUUP_IF_MENU,},
	{ 6,MENUUP_IF_MENU,},
	{ 7,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk2_menuup= {8,_sk2_menuup,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk6[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup,},
	{1,SOFTKEY_IF_STATIC,NULL,NULL,&sk2_menuup,},
	{3,SOFTKEY_IF_STATIC,NULL,},
	{4,SOFTKEY_IF_NOBK,NULL,},
};
static MENUPAGE_DATA subsk6 = {4,_subsk6,};
/**************************************/
/**************************************/
static SOFTKEY_DATA	sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_RECT,},
	{3,SOFTKEY_IF_RECT,},
	{4,SOFTKEY_IF_RECT,},
	{5,SOFTKEY_IF_NEXT,NULL,&subsk6,},
};
MENUPAGE_DATA menuChannelInfo= {6,sk,};
