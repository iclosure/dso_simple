
#include "menu.h"

/**************************************************************
 * 
 *                 波形数学函数类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _item_page_sk2_sk_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
	{ 4, MENUUP_IF_MENU,},
	{ 5, MENUUP_IF_MENU,},
	{ 6, MENUUP_IF_MENU,},
};
static MENUPAGE_DATA item_page_sk2;
static MENUUP_DATA item_page_sk2_sk_menuup= {
	7,_item_page_sk2_sk_menuup,&item_page_sk2,
};
/**************************************/
/**************************************/
static SOFTKEY_DATA  _item_page_sk2_sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&item_page_sk2_sk_menuup},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA item_page_sk2_sk= {5,_item_page_sk2_sk,&menuWaveformMath,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  _item_page_sk2[]= {
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_NEXT,NULL,&item_page_sk2_sk},
};
static MENUPAGE_DATA item_page_sk2= {2, _item_page_sk2,&menuWaveformMath,"111100"};
/**************************************/
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
	{ 4, MENUUP_IF_MENU,},
	{ 5, MENUUP_IF_MENU,},
	{ 6, MENUUP_IF_MENU,},
	{ 7, MENUUP_IF_MENU,NULL,&item_page_sk2},
};
/**************************************/
static MENUUP_DATA sk2_menuup= {8,_sk2_menuup,&menuWaveformMath,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,NULL,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_RECT,},
	{5,SOFTKEY_IF_RECT,},
};
MENUPAGE_DATA menuWaveformMath= {6,sk,};
