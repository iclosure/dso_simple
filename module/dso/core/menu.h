#ifndef MENU_H_
#define MENU_H_


#include "dso_type.h"
#include "picture.h"
#include "menuFunc.h"
#include <stdlib.h>


/************************************************************************
 * 
 *                     菜单变量的声明
 */
const GUI_FONT *font_all[11];
MENUPAGE_DATA *const menu_all[23];

MENUPAGE_DATA menuAnalyze			;  /*分析类*/
MENUPAGE_DATA menuAutoScale			;  /*自动定标类*/
MENUPAGE_DATA menuChannelInfo		;  /*通道X类*/
MENUPAGE_DATA menuCursorSet			;  /*光标设置类*/
MENUPAGE_DATA menuDigitalChannel	;  /*数字通道类*/
MENUPAGE_DATA menuDisplaySet		;  /*显示设置类*/
MENUPAGE_DATA menuFileLoad			;  /*文件加载类*/
MENUPAGE_DATA menuHorizontalSet		;  /*水平设置类*/
MENUPAGE_DATA menuLanguage			;  /*语言设置类*/
MENUPAGE_DATA menuLister			;  /*列表程序设置类*/
MENUPAGE_DATA menuMeasure			;  /*测量类*/
MENUPAGE_DATA menuNewLabel			;  /*新标签类*/
MENUPAGE_DATA menuPattern			;  /*码型类*/
MENUPAGE_DATA menuPrintSet			;  /*打印配置类*/
MENUPAGE_DATA menuReferWaveform		;  /*参考波形类*/
MENUPAGE_DATA menuSamplingSet		;  /*采集设置类*/
MENUPAGE_DATA menuScreenSaverSet	;  /*屏幕保护设置类*/
MENUPAGE_DATA menuService			;  /*服务类*/
MENUPAGE_DATA menuTimeSet			;  /*时间设置类*/
MENUPAGE_DATA menuTrigger			;  /*触发类*/
MENUPAGE_DATA menuTriggerCoupling	;  /*触发模式和耦合类*/
MENUPAGE_DATA menuWaveformGen		;  /*波形发生器类*/
MENUPAGE_DATA menuWaveformMath		;  /*波形数学函数类*/

OTHERTEXT_DATA menuOtherText		;  /*其他显示的字符串数据结构*/

/*******************************************************************
 *
 *                       menu new
 */
void menu_setNewPage		(MENUPAGE_INFO *info, MENUPAGE_DATA *page,I8 dir);
void menu_setNewSoftKey		(MENUPAGE_INFO *info, MENUPAGE_DATA *page);
void menu_displayPageTitle	(MENUPAGE_INFO info);
void menu_selectSoftKey		(MENUPAGE_INFO *info,U8 id);

/*******************************************************************
 *
 *                设置上拉[菜单项]状态位
 *  参数说明: id--表示选中第几项菜单[不包括分隔线和标题项],
 */
void menuup_setStatus		(MENUUP_DATA *menu, U8 id);
void menuup_clrStatus		(MENUUP_DATA *menu, U8 id);
void menuup_clrAllStatus	(MENUUP_DATA *menu);
int  menuup_calcItemIndex	(MENUUP_DATA menu, U8 id);
int  menuup_getActionId		(MENUUP_DATA menu);
void menu_back				(void);

/********************************************************************
 * 
 *                       softkey
 */
void menu_drawSoftKey	(MENUPAGE_INFO *info);
void menu_drawOneSoftKey(MENUPAGE_INFO *info,I8 enTask,U8 id);

/********************************************************************
 * 
 *                       menuup
 */
void menu_drawMenuUp	(MENUPAGE_INFO *info);
void menu_clearMenuUp	(MENUPAGE_INFO *info);
void menu_preDraw1MenuUp(MENUPAGE_INFO *info);
void menu_preDraw1Page	(SOFTKEY_DATA sk);
void menu_drawDialog	(const char *title,GUI_RECT *frame);
void menu_drawFrame		(MENUPAGE_INFO *info);
void menu_displaykword	(MENUPAGE_INFO *info,U8 id);
int  menu_calcItemYSize	(MENUITEM_DATA item);  // 计算上拉菜单选项高度
/*******************************************************************
 *
 *                计算menuup->top / menuup->base
 */
void menuup_calcTop(MENUPAGE_INFO *info);
void menuup_calcBase(MENUPAGE_INFO *info);

/********************************************************************
 *
 *                        状态栏相关函数
 */
void statusbar_initStatic		(STATUSBAR_INFO *info);
void statusbar_dispChannelSens	(STATUSBAR_INFO *info,U8 id);
void statusbar_dispDelayTime	(STATUSBAR_INFO *info);
void statusbar_dispTimeDiv		(STATUSBAR_INFO *info);
void statusbar_dispRunOrStop	(STATUSBAR_INFO *info,const char *runstatus);
void statusbar_dispTriggerType	(STATUSBAR_INFO *info,const GUI_BITMAP *icon);
void statusbar_dispTriggerSource(STATUSBAR_INFO *info,const char *trigsource);
void statusbar_dispTriggerLevel	(STATUSBAR_INFO *info);

/********************************************************************
 *
 *                        信息栏相关函数
 */
void infobar_init		  (INFOBAR_INFO *info);
void infobar_draw		  (INFOBAR_INFO *info);
void infobar_dispAcq	  (INFOBAR_INFO *info);
void infobar_dispChannel  (INFOBAR_INFO *info);
void infobar_initParamArea(INFOBAR_INFO *info);
void infobar_addParam	  (INFOBAR_INFO *info,U8 id,t_param *value);
void infobar_delParam	  (INFOBAR_INFO *info,U8 id,t_param *value);
void infobar_dispParam	  (INFOBAR_INFO *info);

/********************************************************************
 *
 *                        Help相关函数
 */

/**********************************************************
 *
 *                   初始化菜单数据
 */
void menu_init(MENUPAGE_INFO *info);

/**********************************************************
 *
 *                 菜单缓冲区显示函数
 */
void menu_copyToAreaBuff (GUI_RECT *rect);
void menu_displayActivate(GUI_RECT *rect);
void menu_displayMenuHelp(MENUUP_DATA *menu,GUI_RECT *rect);
void menu_displayArea	 (GUI_RECT *rect);

/**********************************************************
 *
 *                   menu task
 */
void menu_task(MENUPAGE_INFO *info);



#endif /*MENU_H_*/
 