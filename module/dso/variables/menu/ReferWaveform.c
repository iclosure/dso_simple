
#include "menu.h"

/**************************************************************
 * 
 *                     参考波形类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA _subsk6[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
};
static MENUPAGE_DATA subsk6 = {3,_subsk6,};
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
	{3,SOFTKEY_IF_STATIC,},
	{4,SOFTKEY_IF_STATIC,},
	{5,SOFTKEY_IF_NEXT,NULL,&subsk6,},
};
MENUPAGE_DATA menuReferWaveform= {6,sk,};
