#ifndef MENU_H_
#define MENU_H_


#include "dso_type.h"
#include "picture.h"
#include "menuFunc.h"
#include <stdlib.h>


/************************************************************************
 * 
 *                     �˵�����������
 */
const GUI_FONT *font_all[11];
MENUPAGE_DATA *const menu_all[23];

MENUPAGE_DATA menuAnalyze			;  /*������*/
MENUPAGE_DATA menuAutoScale			;  /*�Զ�������*/
MENUPAGE_DATA menuChannelInfo		;  /*ͨ��X��*/
MENUPAGE_DATA menuCursorSet			;  /*���������*/
MENUPAGE_DATA menuDigitalChannel	;  /*����ͨ����*/
MENUPAGE_DATA menuDisplaySet		;  /*��ʾ������*/
MENUPAGE_DATA menuFileLoad			;  /*�ļ�������*/
MENUPAGE_DATA menuHorizontalSet		;  /*ˮƽ������*/
MENUPAGE_DATA menuLanguage			;  /*����������*/
MENUPAGE_DATA menuLister			;  /*�б����������*/
MENUPAGE_DATA menuMeasure			;  /*������*/
MENUPAGE_DATA menuNewLabel			;  /*�±�ǩ��*/
MENUPAGE_DATA menuPattern			;  /*������*/
MENUPAGE_DATA menuPrintSet			;  /*��ӡ������*/
MENUPAGE_DATA menuReferWaveform		;  /*�ο�������*/
MENUPAGE_DATA menuSamplingSet		;  /*�ɼ�������*/
MENUPAGE_DATA menuScreenSaverSet	;  /*��Ļ����������*/
MENUPAGE_DATA menuService			;  /*������*/
MENUPAGE_DATA menuTimeSet			;  /*ʱ��������*/
MENUPAGE_DATA menuTrigger			;  /*������*/
MENUPAGE_DATA menuTriggerCoupling	;  /*����ģʽ�������*/
MENUPAGE_DATA menuWaveformGen		;  /*���η�������*/
MENUPAGE_DATA menuWaveformMath		;  /*������ѧ������*/

OTHERTEXT_DATA menuOtherText		;  /*������ʾ���ַ������ݽṹ*/

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
 *                ��������[�˵���]״̬λ
 *  ����˵��: id--��ʾѡ�еڼ���˵�[�������ָ��ߺͱ�����],
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
int  menu_calcItemYSize	(MENUITEM_DATA item);  // ���������˵�ѡ��߶�
/*******************************************************************
 *
 *                ����menuup->top / menuup->base
 */
void menuup_calcTop(MENUPAGE_INFO *info);
void menuup_calcBase(MENUPAGE_INFO *info);

/********************************************************************
 *
 *                        ״̬����غ���
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
 *                        ��Ϣ����غ���
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
 *                        Help��غ���
 */

/**********************************************************
 *
 *                   ��ʼ���˵�����
 */
void menu_init(MENUPAGE_INFO *info);

/**********************************************************
 *
 *                 �˵���������ʾ����
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
 