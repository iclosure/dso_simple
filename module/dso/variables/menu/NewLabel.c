
#include "menu.h"

/**************************************************************
 * 
 *                     新标签类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
	{ 0, MENUUP_IF_SEPARATOR,},
	{ 4, MENUUP_IF_MENU,},
	{ 5, MENUUP_IF_MENU,},
	{ 6, MENUUP_IF_MENU,},
	{ 0, MENUUP_IF_SEPARATOR,},
	{ 7, MENUUP_IF_MENU,},
	{ 8, MENUUP_IF_MENU,},
	{ 9, MENUUP_IF_MENU,},
	{10, MENUUP_IF_MENU,},
	{11, MENUUP_IF_MENU,},
	{12, MENUUP_IF_MENU,},
	{13, MENUUP_IF_MENU,},
	{14, MENUUP_IF_MENU,},
	{ 0, MENUUP_IF_SEPARATOR,},
	{15, MENUUP_IF_MENU,},
	{16, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {20,_sk1_menuup,&menuNewLabel,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
MENUPAGE_DATA menuNewLabel= {6,sk,};
