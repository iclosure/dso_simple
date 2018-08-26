
#include "menu.h"

/**************************************************************
 * 
 *                     波形发生器类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
	{ 4,MENUUP_IF_MENU,},
	{ 5,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {6,_sk1_menuup,&menuWaveformGen,};
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk2_menuup= {4,_sk2_menuup,&menuWaveformGen,};
/**************************************/
static MENUITEM_DATA _sk3_menuup[]= {
	{ 0,MENUUP_IF_MENU,},
	{ 1,MENUUP_IF_MENU,},
	{ 2,MENUUP_IF_MENU,},
	{ 3,MENUUP_IF_MENU,},
	{ 4,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk3_menuup= {5,_sk3_menuup,&menuWaveformGen,};
/**************************************/
static MENUITEM_DATA _sk4_menuup[]= {
	{0,MENUUP_IF_MENU,},
	{1,MENUUP_IF_MENU,},
};
static MENUUP_DATA sk4_menuup= {2,_sk4_menuup,&menuWaveformGen,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk6[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk6 = {4,_subsk6,&menuWaveformGen,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_STATIC,NULL,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,NULL,NULL,&sk3_menuup},
	{3,SOFTKEY_IF_STATIC,NULL,NULL,&sk4_menuup},
	{5,SOFTKEY_IF_NEXT,NULL,&subsk6},
};
MENUPAGE_DATA menuWaveformGen= {5,sk,};
