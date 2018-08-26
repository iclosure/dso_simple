
#include "menu.h"

/**************************************************************
 * 
 *                     文件加载类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_NOBK,},
	{2,SOFTKEY_IF_NOBK,},
};
MENUPAGE_DATA menuFileLoad= {3,sk,};
