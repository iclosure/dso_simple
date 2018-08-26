
#include "menu.h"

/**************************************************************
 * 
 *                     屏幕保护设置类::菜单变量的初始化
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_STATIC,},
	{2,SOFTKEY_IF_STATIC,},
};
MENUPAGE_DATA menuScreenSaverSet= {3,sk,};
