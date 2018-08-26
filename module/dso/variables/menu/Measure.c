
#include "menu.h"

/**************************************************************
 * 
 *                     测量类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static MENUITEM_DATA _sk1_menuup[]= {
	{ 0, MENUUP_IF_MENU,},
	{ 1, MENUUP_IF_MENU,},
	{ 2, MENUUP_IF_MENU,},
	{ 3, MENUUP_IF_MENU,},
};
static MENUUP_DATA sk1_menuup= {4,_sk1_menuup,&menuMeasure,};
/**************************************/
static MENUITEM_DATA _sk2_menuup[]= {
	{ 0, MENUUP_IF_TITLE,},
	{ 1, MENUUP_IF_MENU, &bmicon_unknown},
	{ 2, MENUUP_IF_MENU, &bmicon_unknown},
	{ 3, MENUUP_IF_MENU, &bmicon_unknown},
	{ 4, MENUUP_IF_MENU, &bmicon_unknown},
	{ 5, MENUUP_IF_MENU, &bmicon_unknown},
	{ 6, MENUUP_IF_MENU, &bmicon_unknown},
	{ 7, MENUUP_IF_MENU, &bmicon_unknown},
	{ 8, MENUUP_IF_MENU, &bmicon_unknown},
	{ 9, MENUUP_IF_SEPARATOR,},
	{10, MENUUP_IF_MENU, &bmicon_mean_cycle},
	{11, MENUUP_IF_MENU, &bmicon_mean_fs},
	{12, MENUUP_IF_MENU, &bmicon_dc_rms_cycle},
	{13, MENUUP_IF_MENU, &bmicon_dc_rms_fs},
	{14, MENUUP_IF_MENU, &bmicon_ac_rms_cycle},
	{15, MENUUP_IF_MENU, &bmicon_ac_rms_fs},
	{16, MENUUP_IF_MENU, &bmicon_rate},
	{17, MENUUP_IF_TITLE,},
	{18, MENUUP_IF_MENU, &bmicon_period},
	{19, MENUUP_IF_MENU, &bmicon_freq},
	{20, MENUUP_IF_MENU, &bmicon_unknown},
	{21, MENUUP_IF_MENU, &bmicon_unknown},
	{22, MENUUP_IF_MENU, &bmicon_unknown},
	{23, MENUUP_IF_MENU, &bmicon_unknown},
	{24, MENUUP_IF_MENU, &bmicon_unknown},
	{25, MENUUP_IF_MENU, &bmicon_unknown},
	{26, MENUUP_IF_MENU, &bmicon_unknown},
	{27, MENUUP_IF_MENU, &bmicon_unknown},
	{28, MENUUP_IF_MENU, &bmicon_unknown},
	{29, MENUUP_IF_MENU, &bmicon_unknown},
	{30, MENUUP_IF_MENU, &bmicon_unknown},
	{31, MENUUP_IF_MENU, &bmicon_unknown},
	{32, MENUUP_IF_MENU, &bmicon_unknown},
	{33, MENUUP_IF_MENU, &bmicon_unknown},
	{34, MENUUP_IF_MENU, &bmicon_unknown},
	{35, MENUUP_IF_MENU, &bmWaveCursorToDown},
};
static MENUUP_DATA sk2_menuup= {36,_sk2_menuup,&menuMeasure,};
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk4[]= {
	{4,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk4 = {1,_subsk4,&menuMeasure,"110000"};
/**************************************/
static SOFTKEY_DATA _subsk5[]= {
	{0,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
	{1,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
	{2,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
	{3,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
	{4,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
	{5,SOFTKEY_IF_NOBK,mfMeasure_delMeas,},
};
static MENUPAGE_DATA subsk5 = {6,_subsk5,&menuMeasure,};
/**************************************/
static SOFTKEY_DATA _subsk6[]= {
	{0,SOFTKEY_IF_RECT,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_RECT,},
};
static MENUPAGE_DATA subsk6 = {3,_subsk6,&menuMeasure,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC, NULL,NULL,&sk1_menuup},
	{1,SOFTKEY_IF_STATIC,mfMeasure_dispFastView,NULL,&sk2_menuup},
	{2,SOFTKEY_IF_STATIC,mfMeasure_addMeas,},
	{3,SOFTKEY_IF_NEXT, NULL, &subsk4},
	{4,SOFTKEY_IF_NEXT, NULL, &subsk5},
	{5,SOFTKEY_IF_NEXT, NULL, &subsk6},
};
MENUPAGE_DATA menuMeasure= {6,sk,};
