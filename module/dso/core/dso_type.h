
#ifndef DSO_TYPE_H
#define DSO_TYPE_H

#include "utypes.h"
#include "target.h"
#include "GUI.h"


#pragma pack(1)  // �ֽڶ��뷽ʽ

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/************************************************************************
 *
 *                             redefine
 *                          [1/5/2012 lkh]
 */
/************************************************************************/
/*                         Global typedef                               */
/************************************************************************/
typedef struct tagPROJECTINFO	PROJECT_INFO	;  /*ϵͳ��Ϣ(������??)*/

/************************************************************************/
/*                         DPO typedef                                  */
/************************************************************************/
typedef enum   tagDPOTYPE		DPO_TYPE	;  /*DPO����*/
typedef struct tagDPOINFO		DPO_INFO	;  /*DPO������Ϣ*/

/************************************************************************/
/*                         StatusBar typedef                            */
/************************************************************************/
typedef struct tagSTATUSBAR_INFO		STATUSBAR_INFO		;  /*״̬����Ϣ*/

/************************************************************************/
/*                         InfoBar typedef                              */
/************************************************************************/
typedef struct tagINFOBAR_PARAMLIST		INFOBAR_PARAMLIST	;  /*��Ϣ��������������б�(����)*/
typedef struct tagInfoBar				INFOBAR_INFO		;  /*��Ϣ��������Ϣ*/

/************************************************************************/
/*                         key typedef                                  */
/************************************************************************/
typedef enum   tagKEYDECODE		 KEY_DECODE		;  /*���������б�*/
typedef struct tagKEY			 KEY_DATA		;  /*�������ݽṹ*/
typedef struct tagKEYINFO		 KEY_INFO		;  /*(��ǰ)����������Ϣ*/ 

/************************************************************************/
/*                       measurement typedef                            */
/************************************************************************/
typedef struct tagVOLT_THRESHOLD_DATA	VOLTTHRESHOLD_DATA	;  /*�����ѹ��ֵ��Ϣ*/
typedef struct tagMEAS_VOLT_DATA		MEASVOLT_DATA		;  /*The Measurement Information of Voltage*/
typedef struct tagMEAS_TIME_DATA		MEASTIME_DATA		;  /*The Measurement Information of Time*/
typedef union tagMEAS_PARAM_LIST		MEASPARAM_LIST		;  /*����������б�*/
typedef struct tagMEASUREINFO			MEASURE_INFO		;  /*����������Ϣ*/

/************************************************************************/
/*                         menu typedef                                 */
/************************************************************************/
typedef enum   tagLanguageType   LANGUAGE_TYPE	;  /*�����л���*/
typedef enum   tagFontType		 FONT_TYPE		;  /*�ֿ��л���*/
typedef enum   tagMenuPageType	 MENUPAGE_TYPE	;  /*�˵�ҳ�л���*/
typedef enum   tagMenuItemOption MENUITEM_OPTION;  /*�����˵���ѡ������*/
typedef	enum   tagSoftKeyOption	 SOFTKEY_OPTION	;  /*�������*/
typedef struct tagMenuMeg   	 MENUMSG_DATA	;  /*�˵���Ϣ�������ݽṹ*/
typedef struct tagMenuItem		 MENUITEM_DATA	;  /*�����˵�ѡ�����ݽṹ*/
typedef struct tagMenuUp		 MENUUP_DATA	;  /*�����˵����ݽṹ*/
typedef struct tagSoftKey		 SOFTKEY_DATA	;  /*������ݽṹ*/
typedef struct tagMenuPage		 MENUPAGE_DATA	;  /*�˵�ҳ���ݽṹ*/
typedef struct tagMENUPAGEINFO	 MENUPAGE_INFO	;  /*(��ǰ)�˵�ҳ��Ϣ*/
typedef struct tagOTHERTEXTDATA  OTHERTEXT_DATA	;  /*������ʾ���ַ������ݽṹ*/
/************************************************************************/
/*                         thread typedef                               */
/************************************************************************/
typedef struct tagThREAD		 THREAD_DATA	;  /*�߳�����*/
typedef struct tagThREADINFO	 THREAD_INFO	;  /*�߳���Ϣ*/

/************************************************************************/
/*                         channel typedef                              */
/************************************************************************/
typedef struct tagCURSOR_DATA	 CURSOR_DATA	;  /*���δ��ڹ����Ϣ*/
typedef struct tagCHANNELDATA	 CHANNEL_DATA	;  /*ͨ�����ݼ�������Ϣ���ݽṹ*/
typedef struct tagCHANNELINFO	 CHANNEL_INFO	;  /*ͨ����Ϣ���ݽṹ*/
/************************************************************************/
/*                         wave typedef                                 */
/************************************************************************/
typedef enum   tagWAVEDRAWMODE		WAVE_DRAWMODE	;  /*������ʾ(����)ģʽ*/
typedef struct tagWAVEBASE_INFO		WAVEBASE_INFO	;  /*The Base Information of Wave*/
typedef struct tagWAVEFRAME			WAVEFRAME_DATA	;  /*���δ��ڿ����Ϣ�ṹ*/
typedef struct tagWAVEINFO			WAVE_INFO		;  /*������Ϣ�ṹ*/
typedef I16	   t_ad		;  /*�����ĵ������ݵĳ�ʼ����*/
typedef double t_real	;  /*��Ų�������ת��Ϊ��ʵ��ѹֵ����������*/
typedef double t_param	;  /*������������*/

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/************************************************************************
 *
 *                             first define
 *                            [1/5/2012 lkh]
 */

/************************************************************************/
/*                        Global typedef                                */
/************************************************************************/
typedef struct tagPROJECTINFO {
	STATUSBAR_INFO	*statusbar		;  /*״̬����Ϣ*/
	INFOBAR_INFO	*infobar		;  /*��Ϣ������*/
	KEY_INFO		*key_info		;  /*(��ǰ)������Ϣ*/
	MENUPAGE_INFO	*page_info		;  /*(��ǰ)�˵�ҳ��Ϣ*/
	WAVE_INFO		*wave_info		;  /*(��ǰ)������Ϣ*/
	THREAD_INFO		*thread_info	;  /*(��ǰ)��ǰ�����̶߳�����Ϣ*/

} tPROJECT_INFO;

/************************************************************************/
/*                         DPO typedef                                  */
/************************************************************************/
/*DPO����*/
typedef enum tagDPOTYPE {
	DPO_GRAY	,  /*�Ҷȼ�*/
	DPO_TEMP	,  /*ɫ��*/
} tDPO_TYPE;
/*DPO���ݽṹ*/
typedef struct tagDPOINFO {
	CHANNEL_DATA	*parent	;  /*������*/
	U8				 status	;  /*״̬*/
	DPO_TYPE		 type	;  /*DPO����*/
	int				 size	;  /*DPO�������С*/
	U8				*buff	;  /*DPO������*/

} tDPO_INFO;

/************************************************************************/
/*                        StatusBar typedef                             */
/************************************************************************/
/*״̬����Ϣ*/
typedef struct tagSTATUSBAR_INFO {
	PROJECT_INFO		*parent		;  /*������*/
	GUI_RECT			 rect		;  /*״̬����Ϣ����*/

	t_param				*delayTime	;  /*ʱ��*/
	const char		   **runstatus	;  /*����/ֹͣ״̬*/
	const GUI_BITMAP	*trigtype	;  /*��������*/
	const char		   **trigsource	;  /*����Դ*/
	t_param				*triglevel	;  /*������ƽ��������ֵ*/
	
} tSTATUSBAR_INFO;

/************************************************************************/
/*                         InfoBar typedef                              */
/************************************************************************/
/*��Ϣ��������������б�(����)*/
typedef struct tagINFOBAR_PARAMLIST {
	U8			 id				;  /*ͨ����(1/2/3/4/...)*/
	const char **name			;  /*��������*/
	t_param		*value			;  /*����ֵ*/
	const char **unit			;  /*��λ��Ϣ*/

} tINFOBAR_PARAMLIST;
/*��Ϣ��������Ϣ*/
typedef struct tagInfoBar {
	PROJECT_INFO		*parent			;  /*������*/
	/******** Logo ********/
	GUI_RECT			 logo_rect		;  /*LOGO��Ϣ����*/
	LONG				 cnt			;  /*ͼ����ת��������*/
	/******** Acq *********/
	GUI_RECT			 acq_rect		;  /*�ɼ���Ϣ����*/
	I8					 acq_fresh		;  /*ʹ�ܸ���������ʾ*/
	const char			**acq_mode		;  /*�ɼ�ģʽ�ַ���*/
	t_param				*acq_param		;  /*����*/
	/******** ch  *********/
	GUI_RECT			 ch_rect		;  /*ͨ����Ϣ����*/
	I8					 ch_fresh		;  /*ʹ�ܸ���������ʾ*/
	CHANNEL_DATA		*ch_data		;  /*ͨ������*/
	/******** param *******/
	GUI_RECT			 param_rect		;  /*������ʾ���ڿ��*/
	GUI_RECT			 param_client	;  /*������ʾ���ڿͻ���*/
	U8					 param_n		;  /*��������*/
	INFOBAR_PARAMLIST	 param_list[5]	;  /*�����б�(����)*/
	
} tINFOBAR_INFO;

/************************************************************************/
/*                         key typedef                                  */
/************************************************************************/

/*************************************************************************/
#define KEY_NUM		(46) // Ӳ����������

/********************************************************
 *
 *                   ���̱���
 */
typedef enum tagKEYDECODE {
	KEY_INVALID			= 0xFFFF,
	/************* �˵��� ���� ********************/
	KEY_MENU_PAGE1      = 0,  /*������*/
	KEY_MENU_PAGE2      = 1,  /*�Զ�������*/
	KEY_MENU_PAGE3      = 2,  /*ͨ��X��*/
	KEY_MENU_PAGE4      = 3,  /*���������*/
	KEY_MENU_PAGE5      = 4,  /*����ͨ����*/
	KEY_MENU_PAGE6      = 5,  /*��ʾ������*/
	KEY_MENU_PAGE7      = 6,  /*�ļ�������*/
	KEY_MENU_PAGE8      = 7,  /*ˮƽ������*/
	KEY_MENU_PAGE9      = 8,  /*����������*/
	KEY_MENU_PAGE10     = 9,  /*�б����������*/
	KEY_MENU_PAGE11     = 10,  /*������*/
	KEY_MENU_PAGE12     = 11,  /*�±�ǩ��*/
	KEY_MENU_PAGE13     = 12,  /*������*/
	KEY_MENU_PAGE14     = 13,  /*��ӡ������*/
	KEY_MENU_PAGE15     = 14,  /*�ο�������*/
	KEY_MENU_PAGE16     = 15,  /*�ɼ�������*/
	KEY_MENU_PAGE17     = 16,  /*��Ļ����������*/
	KEY_MENU_PAGE18     = 17,  /*������*/
	KEY_MENU_PAGE19     = 18,  /*ʱ��������*/
	KEY_MENU_PAGE20     = 19,  /*������*/
	KEY_MENU_PAGE21     = 20,  /*����ģʽ�������*/
	KEY_MENU_PAGE22     = 21,  /*���η�������*/
	KEY_MENU_PAGE23	    = 22,  /*������ѧ������*/
	KEY_MENU_RES1	    = 23,  /*Reserved*/
	KEY_MENU_HELP       = 24,  /*help*/
	KEY_MENU_BM_24      = 25,  /*Generate bmp*/
	KEY_MENU_RES3	    = 27,  /*Reserved*/
	KEY_MENU_RES5	    = 29,  /*Reserved*/
	KEY_MENU_CH1	    = 30,  /*Reserved*/
	KEY_MENU_RES6	    = 31,  /*Reserved*/
	KEY_MENU_CH2	    = 32,  /*Reserved*/
	KEY_MENU_RES7	    = 33,  /*Reserved*/
	KEY_MENU_CH3	    = 34,  /*Reserved*/
	KEY_MENU_RES8	    = 35,  /*Reserved*/
	KEY_MENU_CH4	    = 36,  /*Reserved*/
	KEY_MENU_RES9	    = 37,  /*Reserved*/
	KEY_MENU_RES10	    = 38,  /*Reserved*/
	/************* �����Ӧ��Ӳ�� ���� ********************/
	KEY_MENU_BACK       = 38,  /**/
	/************* ʾ������Դ���� *****************/
	KEY_MENU_POWER      = 39,  /**/
	/*************  ��� *****************/
	KEY_MENU_SK1        = 40,  /**/
	KEY_MENU_SK2        = 41,  /**/
	KEY_MENU_SK3        = 42,  /**/
	KEY_MENU_SK4        = 43,  /**/
	KEY_MENU_SK5        = 44,  /**/
	KEY_MENU_SK6        = 45,  /**/
	/************* ��ť ���� ********************/
	KEY_MENU_UP		    = 26,  /*up*/
	KEY_MENU_DOWN	    = 28,  /*down*/
	KEY_MENU_OK         = 255, /**/

} tKEY_DECODE;


/*�������ݽṹ*/
typedef struct tagKEY {
	KEY_DECODE	index	;  /*��������ֵ*/
	I8			status	;  /*����״̬*/
} tKEY_DATA;
/*(��ǰ)����������Ϣ*/
typedef struct tagKEYINFO {
	PROJECT_INFO	*parent		;  /**/
	I8				 ischange	;  /*��ֵ�ı��־*/
	KEY_DATA		 oldkey		;  /*�ɼ�ֵ*/
	KEY_DATA		 newkey		;  /*�¼�ֵ*/
} tKEY_INFO;

/************************************************************************/
/*                       measurement typedef                            */
/************************************************************************/
/* ���������ڡ�Ƶ�ʡ������������������塢�����塢��ֵ����ֵ������� Сֵ����-�塢��ֵ��
   ƽ��ֵ������ƽ��ֵ�������������ھ�����������ʱ�䡢�½�ʱ�䡢��ռ�ձȡ���ռ�ձȡ�⧷���� */

/*�����ѹ��ֵ��Ϣ*/
typedef struct tagVOLT_THRESHOLD_DATA {
    t_param per_10	;  /*10%��ѹ*/
    t_param per_50	;  /*50%��ѹ*/
    t_param per_90	;  /*90%��ѹ*/

} tVOLTTHRESHOLD_DATA;
/*The Measurement Information of Voltage*/
typedef struct tagMEAS_VOLT_DATA {
	t_param		pk_pk		;  /*^��ѹ��-��ֵ (���ֵ����Сֵ֮��Ĳ)(��λ : V) */
	t_param		max			;  /*^����ƽ (������ʾ�����ֵ��)(��λ : V) */
	t_param		min			;  /*^��С��ƽ (������ʾ�����ֵ��)(��λ : V) */
    t_param		amplitude	;  /*^���� (��ֵ�͵�ֵ֮��Ĳ)(��λ : V) */
	t_param		top			;  /*^��ѹ��ֵ (���νϸ߲��ֵ����� (���ֵ)�����δ��������׼ȷ���壬��
								  ����ֵ��Ϊ�����ֵ��ͬ��)(��λ : V) */
	t_param		base		;  /*^��ѹ��ֵ (���νϵͲ��ֵ�ģʽ (���ֵ)�����δ��ģʽ��׼ȷ���壬��
								  ����ֵ��Ϊ����Сֵ��ͬ��)(��λ : V) */
	t_param		overShoot	;  /*^��ѹ�����ع���. ����仯 (��������ת�����ʧ�棬�Է��ȵİٷֱȱ�ʾ��)(��λ : �ٷֱ�) */
    t_param		preShoot	;  /*^��ѹ�½��ع���. ����仯 (���½���ת�����ʧ�棬�Է��ȵİٷֱȱ�ʾ��)(��λ : �ٷֱ�) */
    t_param		average_Nth	;  /*^����ƽ��ֵ (��λ : V)��һ�����������ϲ��εĵ�ѹƽ��ֵ*/
	t_param		average_FS	;  /*^ȫ��ƽ��ֵ (��λ : V)��������������ϲ��εĵ�ѹƽ��ֵ*/ 
	t_param		DCrms_Nth	;  /*^����DC-RMS (��λ : V)��һ�����������ϲ��εľ�����*/
	t_param		DCrms_FS	;  /*^ȫ��DC-RMS (��λ : V)��������������ϲ��εľ�����*/ 
	t_param		ACrms_Nth	;  /*^����AC-RMS (��λ : V)��һ�������������Ƴ��� DC �����Ĳ��εľ�����*/
	t_param		ACrms_FS	;  /*^ȫ��AC-RMS (��λ : V)����������������Ƴ��� DC �����Ĳ��εľ�����*/
	t_param		ratio		;  /*^��������ֵ*/

} tMEAS_VOLT_DATA;
/*The Measurement Information of Time*/
typedef struct tagMEAS_TIME_DATA {
	t_param		period		;  /*^���� (��λ : s)*/
	t_param		freq		;  /*^���� (��λ : Hz)*/
	t_param		phase		;  /*^����ͨ�����ε���λ�� (��λ�Ǵ�Դ 1 ��Դ 2 �����������. )(��λ : ��). */
    t_param		posWidth	;  /* ������. ����仯 (�������ص��м���ֵ����һ���½��ص��м���ֵ��ʱ��)(��λ : s) */
    t_param		negWidth	;  /* ������. ����仯 (���½��ص��м���ֵ����һ�������ص��м���ֵ��ʱ��)(��λ : s) */
    t_param		burstWidth	;  /* ⧷����. ����仯 (��Ļ�ϴӵ�һ���ص����һ���ص�ʱ��)(��λ : s) */
    t_param		posDutyCycle;  /* ��ռ�ձ� (�ظ������е�ռ�ձ����������Ⱥ����ڵı��ʣ��԰ٷֱȱ�ʾ��)(��λ : �ٷֱ�) */
    t_param		negDutyCycle;  /* ��ռ�ձ� (�ظ������е�ռ�ձ����������Ⱥ����ڵı��ʣ��԰ٷֱȱ�ʾ��)(��λ : �ٷֱ�) */
    t_param		riseTime	;  /* ����ʱ��. ����仯 (�źŵ�����ʱ���������صĽϵ���ֵ�����ͽϸ���ֵ�����֮���ʱ�)(��λ : s) */
    t_param		fallTime	;  /* �½�ʱ��. ����仯 (�źŵ��½�ʱ���Ǹ����صĽϸ���ֵ�����ͽϵ���ֵ�����֮���ʱ�)(��λ : s) */
    t_param		x_min		;  /**/
	t_param		x_max		;  /**/
	t_param		posPulseCnt	;  /*������ֵ*/
	t_param		negPulseCnt	;  /*������ֵ*/
	t_param		riseEdge	;  /* �������ͨ�����ε������ӳ�. ����仯 (�ӳٲ�����ӽ��ڴ����ο����Դ 1 ��ѡ������Դ 2 ��ѡ�����ڲ�������ֵ��
                                  ����ʱ�����ӳ�ֵ��ʾԴ 1 ����ѡ���س�����Դ 2 ����ѡ����֮��)(��λ : s) */
    t_param		fallEdge	;  /* �������ͨ�����ε��½��ӳ�. ����仯 (�ӳٲ�����ӽ��ڴ����ο����Դ 1 ��ѡ������Դ 2 ��ѡ�����ڲ�������ֵ��
                                  ����ʱ�����ӳ�ֵ��ʾԴ 1 ����ѡ���س�����Դ 2 ����ѡ����֮��)(��λ : s) */
    t_param		area_Nth	;  /**/
	t_param		area_FS		;  /**/
    
} tMEASTIME_DATA;
/*����������б�*/
typedef union tagMEAS_PARAM_LIST {
	t_param			list[33]	;  /**/
	struct {
		MEASVOLT_DATA	v			;  /**/
		MEASTIME_DATA	t			;  /**/
	} i;
} tMEASPARAM_LIST;
/*����������Ϣ*/
typedef struct tagMEASUREINFO {
	CHANNEL_DATA		*parent		;  /*������*/
	VOLTTHRESHOLD_DATA   vt			;  /*�����ѹ��ֵ��Ϣ*/
	MEASPARAM_LIST		 param		;  /*����������б�*/

} tMEASURE_INFO;

/************************************************************************/
/*                         menu typedef                                 */
/************************************************************************/
/*�����л���*/
typedef enum tagLanguageType {
	eEnglish			,  /*Ӣ��*/
	eFrench				,  /*����*/
	eGerman				,  /*����*/
	eItalian			,  /*�������*/
	eJapanese			,  /*����*/
	eKorean				,  /*����*/
	ePortuguese			,  /*??*/
	eRussian			,  /*����*/
	eSimplifiedChinese	,  /*��������*/
	eSpanish			,  /*��������*/
	eTraditionalChinese	,  /*��������*/

} tLANGUAGE_TYPE;
/*�ֿ��л���[������LANGUAGE_TYPEһһ��Ӧ]*/
typedef enum tagFontType {
	efontEnglish			,  /*Ӣ���ֿ���*/
	efontFrench				,  /*�����ֿ���*/
	efontGerman				,  /*�����ֿ���*/
	efontItalian			,  /*��������ֿ���*/
	efontJapanese			,  /*�����ֿ���*/
	efontKorean				,  /*�����ֿ���*/
	efontPortuguese			,  /*??�ֿ���*/
	efontRussian			,  /*�����ֿ���*/
	efontSimplifiedChinese	,  /*���������ֿ���*/
	efontSpanish			,  /*���������ֿ���*/
	efontTraditionalChinese	,  /*���������ֿ���*/

} tFONT_TYPE;
/*�˵�ҳ�л���*/
typedef enum tagMenuPageType {
	eAnalyze		,  /*������*/
	eAutoScale		,  /*�Զ�������*/
	eChannelInfo	,  /*ͨ��X��*/
	eCursorSet		,  /*���������*/
	eDigitalChannel	,  /*����ͨ����*/
	eDisplaySet		,  /*��ʾ������*/
	eFileLoad		,  /*�ļ�������*/
	eHorizontalSet	,  /*ˮƽ������*/
	eLanguage		,  /*����������*/
	eLister			,  /*�б����������*/
	eMeasure		,  /*������*/
	eNewLabel		,  /*�±�ǩ��*/
	ePattern		,  /*������*/
	ePrintSet		,  /*��ӡ������*/
	eReferWaveform	,  /*�ο�������*/
	eSamplingSet	,  /*�ɼ�������*/
	eScreenSaverSet	,  /*��Ļ����������*/
	eService		,  /*������*/
	eTimeSet		,  /*ʱ��������*/
	eTrigger		,  /*������*/
	eTriggerCoupling,  /*����ģʽ�������*/
	eWaveformGen	,  /*���η�������*/
	eWaveformMath	,  /*������ѧ������*/

} tMENUPAGE_TYPE;
/*�����˵���ѡ������*/
typedef enum tagMenuItemOption {
	MENUUP_IF_TITLE		,  /*������*/
	MENUUP_IF_MENU		,  /*�˵���*/
	MENUUP_IF_SEPARATOR	,  /*�ָ���*/
	MENUUP_IF_DISABLED	,  /*δ����״̬*/
	MENUUP_IF_ENABLED 	,  /*����״̬*/

} tMENUITEN_OPTION;
/*�������*/
typedef enum tagSoftKeyOption {
	SOFTKEY_IF_EMPTY		,  /*���������*/
	SOFTKEY_IF_NOBK			,  /*û�б��������*/
	SOFTKEY_IF_RECT			,  /*�·�����������*/
	SOFTKEY_IF_DISABLED		,  /*�����������Ч�����[��Ҫ�ڸ���ʱ���][Ҳ��Ĭ��״̬]*/
	SOFTKEY_IF_NEXT			,  /*�����������Ч�����[��Ҫ�ڸ���ʱ���][Ҳ��Ĭ��״̬]*/
	SOFTKEY_IF_STATIC		,  /*�̶������[�ڵ�ǰҳ���ı�״̬]*/
	SOFTKEY_IF_SELRECT		,  /*����״̬[�����Ӧ��Ӳ����ѡ��]*/
	SOFTKEY_IF_ACTIVATE		,  /*����״̬[�����Ӧ��Ӳ����ѡ��]*/
	SOFTKEY_IF_MENU			,  /*���������˵�[]*/

} tSOFTKEY_OPTION;
/*�˵���Ϣ�������ݽṹ*/
typedef struct tagMenuMeg{
	U16		msgtype	;  /**/
	U16		itemid	;  /**/
} tMENUMSG_DATA;
/*�����˵�ѡ�����ݽṹ*/
typedef struct tagMenuItem {
	U8                id		;  /*����*/
	MENUITEM_OPTION   option	;  /*����: MENUUP_OPTION_TITLE or MENUUP_OPTION_MENU or MENUUP_OPTION_SEPARALINE*/
	const GUI_BITMAP *icon		;  /*�˵���icon*/
	MENUPAGE_DATA	 *next		;  /*��һҳ(˫������)*/
	U8                status	;  /*״̬: 1--ѡ��;0--ûѡ��*/
	const char       *title		;  /*��������ΪMENUUP_OPTION_TITLEʱ��ȡtitle, ΪMENUUP_OPTION_MENUʱ��ȡ�ı��ַ���*/
	const char		 *kword		;  /*����(�ؼ���)*/
	const char       *help		;  /*�����ĵ�*/

} tMENUITEM_DATA;
/*�����˵����ݽṹ*/
typedef struct tagMenuUp {
	U8               itemn		;  /*�˵�ѡ�����[�����ָ��ߺͱ���]*/
	MENUITEM_DATA   *item		;  /*ѡ���б�*/
	MENUPAGE_DATA	*back		;  /*��һҳ(˫������)*/
	void          *(*task)(PROJECT_INFO *info,I8 id);  /*����*/
	U8               menun		;  /*�˵������*/
	GUI_RECT         frame		;  /*�����˵�����*/
	GUI_RECT		 client		;  /*�ͻ���*/
	I16				 width,height;  /*�����˵��ߴ�*/
	I16				 MaxXSize	;  /*�����˵��Ĳ˵�ѡ���е�����*/
	U8               status		;  /*״̬: 1--ѡ��;0--ûѡ��*/
	const char      *title		;  /*menu title*/
	/*++++++++++++++++++++++++++++*/
	I8				 index		;  /*�����˵����������*/
	I8				 top,base	;  /*��ǰ�����˵��Ĳ˵���[��ʼ]��[��ֹ]����[�������ָ��ߺͱ�����]*/
	I8				 dispdir	;  /*�����˵���ʾ����[=1��ʾ����;=0��ʾ����][Ĭ��Ϊ����]*/
	/*++++++++++++++++++++++++++++*/
} tMENUUP_DATA;
/*������ݽṹ*/
typedef struct tagSoftKey {
	U8                    id		;  /*����*/
	SOFTKEY_OPTION        option	;  /*״̬: 1--ѡ��;0--ûѡ��*/
	void              *(*task)(PROJECT_INFO *info,I8 id)	;  /*����*/
	MENUPAGE_DATA		 *next		;  /*��һҳ(˫������)*/
	MENUUP_DATA          *menuup	;  /*���������˵�*/
	const GUI_BITMAP	 *icon		;  /*ͼ����ؼ���*/
	const char			 *title		;  /*����*/
	const char			 *ktype		;  /*�ؼ��������ַ���*/

} tSOFTKEY_DATA;
/*�˵�ҳ���ݽṹ*/
typedef struct tagMenuPage {
	U8                   n		;  /*���ڱ����˵����������*/
	SOFTKEY_DATA        *sk		;  /*��������б�*/
	MENUPAGE_DATA		*back	;  /*��һҳ(˫������)*/
	const char 			*others	;  /*���˵�ҳ�е������̶�������(���ַ�����ʽ��Ҫʱ��ÿ������и���)*/
	const char          *title	;  /*�˵�ҳ����*/
	const char			*kword	;  /*����(�ؼ���)*/

} tMENUPAGE_DATA;
/*�˵�ҳ������Ϣ*/
typedef struct tagMENUPAGEINFO {
	PROJECT_INFO		*parent		;  /*������*/
	LANGUAGE_TYPE		 langtype 	;  /*��ǰ��ʼ����������*/
	I8					 hide		;  /*�����˵��Զ����ر�־(���а�����Ӧʱ��λ������ʱ��ʱ���ز˵���=1��Ч)*/
	I8					 enhide		;  /*ʹ�����������˵�*/
	I8					 enExt		;  /*ʹ�ܸ��Ӳ˵�*/
	GUI_RECT			 extFrame,extClient	;  /*���Ӳ˵�����Ϳͻ�����*/
	void              *(*task)(PROJECT_INFO *info,I8 id)	;  /*����[�����������Ҫռ�ò��ֲ���������ʾʱʹ��]*/

	MENUPAGE_TYPE		 number		;  /*��ǰҳ�����*/
	MENUPAGE_DATA		*back		;  /*˫������ָ�����*/
	MENUPAGE_DATA		*now    	;  /*��ǰ���ڼ���״��Ĳ˵�ҳ*/
	MENUPAGE_DATA		*next		;  /*˫������ָ�����*/
	I8					 id			;  /*��ǰҳ�д��ڼ���״̬�����ID��*/
	SOFTKEY_DATA		 sk[6]		;  /*��ǰ���ڼ���״̬�����*/

} tMENUPAGE_INFO;
/*������ʾ���ַ������ݽṹ*/
typedef struct tagOTHERTEXTDATA {
	const char		*runstatus[2];	/*����/ֹͣ״̬*/
} tOTHERTEXT_DATA;

/************************************************************************/
/*                         thread typedef                               */
/************************************************************************/
// �̶߳�ջ�������Ͷ���
#if defined(OS_UCOS)  /*uCOS System*/
#define UCOS_STKMAX	(256)
//typedef OS_STK			thread_stack[UCOS_STKMAX]	;

#else /*Linux system*/
//typedef pthread_t		thread_stack

#endif

/*�߳���Ϣ�ṹ*/
typedef struct tagThREAD {
	U8				 id					;  /*�߳�id*/
	void		   (*task)(void *p_arg)	;  /*������*/
	void			*p_arg				;  /*�����������*/
#if defined(OS_UCOS)  /*uCOS System*/
	OS_STK			 stack[UCOS_STKMAX]	;  /*�̶߳�ջ*/
#else   /*Linux system*/
	pthread_t		 stack	 			;  /*�̶߳�ջ*/	
#endif
	U8				 status				;  /*����״̬*/
} tTHREAD_DATA;

/*�߳���Ϣ�ṹ*/
typedef struct tagThREADINFO {
	PROJECT_INFO	*parent	;  /*������*/
	U8				 offset	;  /*idƫ����*/
	U8				 n		;  /*�̸߳���*/
	THREAD_DATA	    *task	;  /*�����б�*/
} tTHREAD_INFO;

/************************************************************************/
/*                         channel typedef                              */
/************************************************************************/
/*���δ��ڹ����Ϣ*/
typedef struct tagCURSOR_DATA {
	const GUI_BITMAP *icon		;  /*�˵���icon*/
	int				  x			;  /**/
	int				  y			;  /**/
	t_param			  sens		;  /*ˮƽ(��ֱ)������*/

} tCURSOR_DATA;
/*ͨ�����ݼ�������Ϣ���ݽṹ*/
typedef struct tagCHANNELDATA {
	CHANNEL_INFO   *parent	;  /*������*/
	/*base data info*/
	U8				id		;  /*��ǰͨ����[1,2,...]*/
	U8				status	;  /**/
	COLOR			color	;  /*ͨ����ɫ*/
	t_param			zoom	;  /*˥������*/
	I16				start	;  /**/
	I16				end		;  /**/
	U16				sampleN	;  /*ͨ��ԭʼ���ݵ���(Ĭ��Ϊ )*/
	t_ad		   *sort	;  /*�����ݴ�ֵ*/
	t_ad		   *sample	;  /*ͨ������*/
	t_real		   *real	;  /*��Ų�������ת��Ϊ��ʵ��ѹֵ*/
	CURSOR_DATA		hcursor	;  /*ˮƽ���*/
	CURSOR_DATA		vcursor	;  /*��ֱ���*/

	/*more ...*/
	MEASURE_INFO	measure	;  /*��������Ϣ*/
	DPO_INFO	    dpo		;  /*DPO������Ϣ*/

} tCHANNEL_DATA;
/*ͨ����Ϣ���ݽṹ*/
typedef struct tagCHANNELINFO {
	WAVE_INFO		*parent		;  /*������*/
	U8				 n			;  /*��ͨ������*/
	I8				 validn		;  /*��ǰ���ڹ���״̬��ͨ������*/
	CHANNEL_DATA	*action		;  /*��ǰͨ��(1/2/3/4/...)*/
	CHANNEL_DATA	 ch[4]		;  /*����ͨ�����ݽṹ*/
	LONG			 dpocnt		;  /*DPO������*/

} tCHANNEL_INFO;

/************************************************************************/
/*                         wave typedef                                 */
/************************************************************************/
/*������ʾ(����)ģʽ*/
typedef enum tagWAVEDRAWMODE {
	WAVE_DRAWMODE_DOT	,  /*��*/
	WAVE_DRAWMODE_LINE	,  /*��(ʸ��)*/
	WAVE_DRAWMODE_GRAY	,  /*�Ҷȼ�*/
	WAVE_DRAWMODE_TEMP	,  /*ɫ��*/
} tWAVE_DRAWMODE;
//I16* pay, int NumPoints, int xoff, int yoff, int ExPoints
/*The Base Information of Wave*/
typedef struct tagWAVEBASE_INFO {
	t_param  hSens	;  /*������ʾ����ˮƽ������*/
	t_param  vSens	;  /*������ʾ���ڴ�ֱ������*/
	t_param  Period	;  /*����(��λ : s)*/
	t_param  Vmax	;  /*����ƽ (������ʾ�����ֵ��)(��λ : V)*/
	t_param  Vmin	;  /*��С��ƽ (������ʾ�����ֵ��)(��λ : V)*/

} tWAVEBASE_INFO;
/*���δ��ڿ����Ϣ�ṹ*/
typedef struct tagWAVEFRAME {
	GUI_RECT	frame	;
	GUI_RECT	client	;

} tWAVEFRAME_DATA;
/*������Ϣ�ṹ*/
typedef struct tagWAVEINFO {
	PROJECT_INFO	*parent		;  /*������*/
	WAVEFRAME_DATA	 frame		;  /**/
	I8				 gridrate	;  /*����������������*/
	U16				 gridcolor	;  /*��������������ɫ*/
	I8				 wavecnt	;  /*���λ��Ƽ�����(��¼һ���Ի��ƴ���)*/
	WAVE_DRAWMODE	 mode		;  /**/	
	CHANNEL_INFO	*ch			;  /*ͨ��*/

} tWAVE_INFO;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#pragma pack()


#endif /**/
