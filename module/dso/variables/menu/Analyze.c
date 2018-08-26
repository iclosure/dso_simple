
#include "menu.h"

/**************************************************************
 * 
 *                     分析类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA  _item2_page_sk1[]= {
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA item2_page_sk1= {5,_item2_page_sk1,&menuAnalyze,"100000"};
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{0, MENUUP_IF_MENU,},
	{1, MENUUP_IF_MENU,},
	{2, MENUUP_IF_MENU,NULL,&item2_page_sk1},
};
static MENUUP_DATA sk1_menuup= {3,_sk1_menuup,&menuAnalyze,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk2[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk2 = {4,_subsk2,&menuAnalyze,};
/**************************************/
static SOFTKEY_DATA _subsk3[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk3 = {2,_subsk3,&menuAnalyze,};
/**************************************/
static SOFTKEY_DATA _subsk4[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk4 = {2,_subsk4,&menuAnalyze,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{ 0,SOFTKEY_IF_STATIC, NULL,NULL,&sk1_menuup},
	{ 1,SOFTKEY_IF_NEXT, NULL,&subsk2},
	{ 2,SOFTKEY_IF_NEXT, NULL,&subsk3},
	{ 3,SOFTKEY_IF_NEXT, NULL,&subsk4},
	{ 4,SOFTKEY_IF_STATIC,},
};
MENUPAGE_DATA menuAnalyze= {5,sk};
