

#include "dso_type.h"
#include "dso_confDefaults.h"
#include "menu.h"
#include "meas.h"
#include "wave.h"
#include "thread.h"
#include "key.h"
#include <math.h>

/**********************************************************
 *
 *                 系统信息(变量、??)
 */

extern KEY_INFO			keyinfo		;  /*(当前)按键信息*/
extern MENUPAGE_INFO	pageinfo	;  /*(当前)菜单页信息*/
extern STATUSBAR_INFO	statusbar	;  /*状态栏数据信息*/
extern INFOBAR_INFO		infobar		;  /*信息栏数据信息*/
extern CHANNEL_INFO		chinfo		;  /*通道信息*/
extern WAVE_INFO		waveinfo	;  /*(当前)波形信息*/
extern THREAD_INFO		threadinfo	;  /*(当前)工程线程队列信息*/

PROJECT_INFO	prj_info= {    /*系统信息(变量、??)*/
	&statusbar,
	&infobar,
	&keyinfo,
	&pageinfo,
	&waveinfo,
	&threadinfo,

};

/**********************************************************
 *
 *
 */
/*菜单字体库*/
const GUI_FONT *font_all[11]= {
	&GUI_Font13B_ASCII	, /*英文字库类*/
	&GUI_Font13B_ASCII	, /*法文字库类*/
	&GUI_Font13B_ASCII	, /*德文字库类*/
	&GUI_Font13B_ASCII	, /*意大利文字库类*/
	&GUI_Font13B_ASCII	, /*日文字库类*/
	&GUI_Font13B_ASCII	, /*韩文字库类*/
	&GUI_Font13B_ASCII	, /*??字库类*/
	&GUI_Font13B_ASCII	, /*俄文字库类*/
	&GUI_FontHZ13		, /*简体中文字库类*/
	&GUI_Font13B_ASCII	, /*西班牙文字库类*/
	&GUI_FontHZ13		, /*繁体中文字库类*/
};
// 
MENUPAGE_DATA *const menu_all[23]= {
	&menuAnalyze,
	&menuAutoScale,
	&menuChannelInfo,
	&menuCursorSet,
	&menuDigitalChannel,
	&menuDisplaySet,
	&menuFileLoad,
	&menuHorizontalSet,
	&menuLanguage,
	&menuLister,
	&menuMeasure,
	&menuNewLabel,
	&menuPattern,
	&menuPrintSet,
	&menuReferWaveform,
	&menuSamplingSet,
	&menuScreenSaverSet,
	&menuService,
	&menuTimeSet,
	&menuTrigger,
	&menuTriggerCoupling,
	&menuWaveformGen,
	&menuWaveformMath,
};

/********************************************************************
 *
 *                      Functions
 */
// isdel=1表示释放指针变量占用的空间，否则申请空间
void dso_initVariable(PROJECT_INFO *info,int isdel) {
	int i=0;
	COLOR ch_color[4]={CH1_COLOR,CH2_COLOR,CH3_COLOR,CH4_COLOR};
	if(isdel) {
		// 释放指针-> 波形通道指针变量
		if(info->wave_info->ch->validn > 0) {
			info->wave_info->ch->validn	= 0;
			info->wave_info->ch->action	= NULL;
			for(i=0; i<info->wave_info->ch->n; i++) {
				if(info->wave_info->ch->ch[i].status == 1) {
					free(info->wave_info->ch->ch[i].sort);
					free(info->wave_info->ch->ch[i].sample);
					free(info->wave_info->ch->ch[i].real);
					if(info->wave_info->ch->ch[i].dpo.status == 1) {
						free(info->wave_info->ch->ch[i].dpo.buff);
						info->wave_info->ch->ch[i].dpo.parent = NULL;
						info->wave_info->ch->ch[i].dpo.buff	  = NULL;
						info->wave_info->ch->ch[i].dpo.status = 0;
					}
					info->wave_info->ch->ch[i].sampleN			= WAVEWIN_XSIZE;//65;
					info->wave_info->ch->ch[i].measure.parent	= NULL;
					info->wave_info->ch->ch[i].sort				= NULL;
					info->wave_info->ch->ch[i].sample			= NULL;
					info->wave_info->ch->ch[i].real				= NULL;
					info->wave_info->ch->ch[i].status			= 0;
				}
			}
		}
		// 释放指针-> XXX

	}
		/*参数*/
		/*初始化按键数据信息*/
		info->key_info->parent		= info;
		/*初始化菜单数据信息*/
		info->page_info->parent		= info;
		info->page_info->langtype	= eEnglish;
		info->page_info->hide		= 1;
		info->page_info->number		= eAutoScale;
		info->page_info->now		= menu_all[info->page_info->number];
		GUI_SetFont(font_all[info->page_info->langtype]);
		menu_init(info->page_info);
		/*初始化线程数据信息*/ 
		info->thread_info->parent	= info;
		info->thread_info->offset	= TASK_OFFSET_ID;
		/*初始化波形通道指针变量*/
		info->wave_info->parent		= info;
		info->wave_info->ch			= &chinfo;
		info->wave_info->ch->parent	= info->wave_info;
		info->wave_info->ch->action	= NULL;
		info->wave_info->ch->n		= 4;
		info->wave_info->ch->validn	= 0;
		for(i=0; i<info->wave_info->ch->n; i++) {
			info->wave_info->ch->ch[i].parent	= info->wave_info->ch;
			info->wave_info->ch->ch[i].color	= ch_color[i];
			info->wave_info->ch->ch[i].zoom		= 10.0;
			info->wave_info->ch->ch[i].id		= i;
			info->wave_info->ch->ch[i].status	= 0;
			info->wave_info->ch->ch[i].sampleN	= WAVEWIN_XSIZE;//65;
			info->wave_info->ch->ch[i].hcursor.sens = 1.00;
			info->wave_info->ch->ch[i].vcursor.sens = 0.50;
			// 
			info->wave_info->ch->ch[i].measure.parent = &info->wave_info->ch->ch[i];
			info->wave_info->ch->ch[i].dpo.parent	  = &info->wave_info->ch->ch[i];
			info->wave_info->ch->ch[i].dpo.status	  = 1;
			info->wave_info->ch->ch[i].dpo.size		  = WAVEWIN_XSIZE*WAVEWIN_YSIZE;
		}
		/*初始化状态栏数据信息*/
		info->statusbar->parent		= info;
		info->statusbar->runstatus	= &menuOtherText.runstatus[0];  /*自动模式*/
		info->statusbar->trigtype	= menu_all[eTrigger]->sk[2].menuup->item[0].icon;
		info->statusbar->trigsource	= &menu_all[eAutoScale]->sk[2].menuup->item[0].kword;
		/*初始化信息栏数据信息*/
		info->infobar->parent		= info;
		info->infobar->cnt			= 1000;
		info->infobar->acq_mode		= &menuAutoScale.sk[3].menuup->item[0].kword;
		info->infobar->acq_fresh	= 0;
		info->infobar->ch_fresh		= 0;
		info->infobar->ch_data		= info->wave_info->ch->ch;
		info->infobar->param_n		= 0;
		// 初始化 XXX
}