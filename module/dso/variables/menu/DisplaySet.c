
#include "menu.h"
/**************************************************************
 * 
 *                     ��ʾ������::�˵������ĳ�ʼ��
 */
/**************************************/
/**************************************/
static SOFTKEY_DATA  sk[]= {
	{0,SOFTKEY_IF_STATIC,},
	{1,SOFTKEY_IF_NOBK,},
	{2,SOFTKEY_IF_NOBK,},
	{3,SOFTKEY_IF_NOBK,},
	{4,SOFTKEY_IF_STATIC,mf_SetGrid,},
};
MENUPAGE_DATA menuDisplaySet= {5,sk,};
