
#include "menu.h"

/**************************************************************
 * 
 *                     列表程序类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
	{ 4,MENUUP_IF_MENU,},
	{ 5,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk2_menuup= {6,_sk2_menuup,&menuLister,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk5[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,NULL,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk5 = {5,_subsk5,};
/**************************************/
/**************************************/
static SOFTKEY_DATA	sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_NEXT,NULL,&subsk5,},
};
MENUPAGE_DATA menuLister= {5,sk,};
