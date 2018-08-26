

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
 *                 ϵͳ��Ϣ(������??)
 */

extern KEY_INFO			keyinfo		;  /*(��ǰ)������Ϣ*/
extern MENUPAGE_INFO	pageinfo	;  /*(��ǰ)�˵�ҳ��Ϣ*/
extern STATUSBAR_INFO	statusbar	;  /*״̬��������Ϣ*/
extern INFOBAR_INFO		infobar		;  /*��Ϣ��������Ϣ*/
extern CHANNEL_INFO		chinfo		;  /*ͨ����Ϣ*/
extern WAVE_INFO		waveinfo	;  /*(��ǰ)������Ϣ*/
extern THREAD_INFO		threadinfo	;  /*(��ǰ)�����̶߳�����Ϣ*/

PROJECT_INFO	prj_info= {    /*ϵͳ��Ϣ(������??)*/
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
/*�˵������*/
const GUI_FONT *font_all[11]= {
	&GUI_Font13B_ASCII	, /*Ӣ���ֿ���*/
	&GUI_Font13B_ASCII	, /*�����ֿ���*/
	&GUI_Font13B_ASCII	, /*�����ֿ���*/
	&GUI_Font13B_ASCII	, /*��������ֿ���*/
	&GUI_Font13B_ASCII	, /*�����ֿ���*/
	&GUI_Font13B_ASCII	, /*�����ֿ���*/
	&GUI_Font13B_ASCII	, /*??�ֿ���*/
	&GUI_Font13B_ASCII	, /*�����ֿ���*/
	&GUI_FontHZ13		, /*���������ֿ���*/
	&GUI_Font13B_ASCII	, /*���������ֿ���*/
	&GUI_FontHZ13		, /*���������ֿ���*/
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
// isdel=1��ʾ�ͷ�ָ�����ռ�õĿռ䣬��������ռ�
void dso_initVariable(PROJECT_INFO *info,int isdel) {
	int i=0;
	COLOR ch_color[4]={CH1_COLOR,CH2_COLOR,CH3_COLOR,CH4_COLOR};
	if(isdel) {
		// �ͷ�ָ��-> ����ͨ��ָ�����
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
		// �ͷ�ָ��-> XXX

	}
		/*����*/
		/*��ʼ������������Ϣ*/
		info->key_info->parent		= info;
		/*��ʼ���˵�������Ϣ*/
		info->page_info->parent		= info;
		info->page_info->langtype	= eEnglish;
		info->page_info->hide		= 1;
		info->page_info->number		= eAutoScale;
		info->page_info->now		= menu_all[info->page_info->number];
		GUI_SetFont(font_all[info->page_info->langtype]);
		menu_init(info->page_info);
		/*��ʼ���߳�������Ϣ*/ 
		info->thread_info->parent	= info;
		info->thread_info->offset	= TASK_OFFSET_ID;
		/*��ʼ������ͨ��ָ�����*/
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
		/*��ʼ��״̬��������Ϣ*/
		info->statusbar->parent		= info;
		info->statusbar->runstatus	= &menuOtherText.runstatus[0];  /*�Զ�ģʽ*/
		info->statusbar->trigtype	= menu_all[eTrigger]->sk[2].menuup->item[0].icon;
		info->statusbar->trigsource	= &menu_all[eAutoScale]->sk[2].menuup->item[0].kword;
		/*��ʼ����Ϣ��������Ϣ*/
		info->infobar->parent		= info;
		info->infobar->cnt			= 1000;
		info->infobar->acq_mode		= &menuAutoScale.sk[3].menuup->item[0].kword;
		info->infobar->acq_fresh	= 0;
		info->infobar->ch_fresh		= 0;
		info->infobar->ch_data		= info->wave_info->ch->ch;
		info->infobar->param_n		= 0;
		// ��ʼ�� XXX
}