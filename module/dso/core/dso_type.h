
#ifndef DSO_TYPE_H
#define DSO_TYPE_H

#include "utypes.h"
#include "target.h"
#include "GUI.h"


#pragma pack(1)  // 字节对齐方式

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
typedef struct tagPROJECTINFO	PROJECT_INFO	;  /*系统信息(变量、??)*/

/************************************************************************/
/*                         DPO typedef                                  */
/************************************************************************/
typedef enum   tagDPOTYPE		DPO_TYPE	;  /*DPO类型*/
typedef struct tagDPOINFO		DPO_INFO	;  /*DPO数据信息*/

/************************************************************************/
/*                         StatusBar typedef                            */
/************************************************************************/
typedef struct tagSTATUSBAR_INFO		STATUSBAR_INFO		;  /*状态栏信息*/

/************************************************************************/
/*                         InfoBar typedef                              */
/************************************************************************/
typedef struct tagINFOBAR_PARAMLIST		INFOBAR_PARAMLIST	;  /*信息栏参数区域参数列表(队列)*/
typedef struct tagInfoBar				INFOBAR_INFO		;  /*信息栏数据信息*/

/************************************************************************/
/*                         key typedef                                  */
/************************************************************************/
typedef enum   tagKEYDECODE		 KEY_DECODE		;  /*按键编码列表*/
typedef struct tagKEY			 KEY_DATA		;  /*按键数据结构*/
typedef struct tagKEYINFO		 KEY_INFO		;  /*(当前)按键数据信息*/ 

/************************************************************************/
/*                       measurement typedef                            */
/************************************************************************/
typedef struct tagVOLT_THRESHOLD_DATA	VOLTTHRESHOLD_DATA	;  /*特殊电压阈值信息*/
typedef struct tagMEAS_VOLT_DATA		MEASVOLT_DATA		;  /*The Measurement Information of Voltage*/
typedef struct tagMEAS_TIME_DATA		MEASTIME_DATA		;  /*The Measurement Information of Time*/
typedef union tagMEAS_PARAM_LIST		MEASPARAM_LIST		;  /*测量类参数列表*/
typedef struct tagMEASUREINFO			MEASURE_INFO		;  /*测量数据信息*/

/************************************************************************/
/*                         menu typedef                                 */
/************************************************************************/
typedef enum   tagLanguageType   LANGUAGE_TYPE	;  /*语言切换类*/
typedef enum   tagFontType		 FONT_TYPE		;  /*字库切换类*/
typedef enum   tagMenuPageType	 MENUPAGE_TYPE	;  /*菜单页切换类*/
typedef enum   tagMenuItemOption MENUITEM_OPTION;  /*上拉菜单栏选项属性*/
typedef	enum   tagSoftKeyOption	 SOFTKEY_OPTION	;  /*软键属性*/
typedef struct tagMenuMeg   	 MENUMSG_DATA	;  /*菜单信息处理数据结构*/
typedef struct tagMenuItem		 MENUITEM_DATA	;  /*上拉菜单选项数据结构*/
typedef struct tagMenuUp		 MENUUP_DATA	;  /*上拉菜单数据结构*/
typedef struct tagSoftKey		 SOFTKEY_DATA	;  /*软键数据结构*/
typedef struct tagMenuPage		 MENUPAGE_DATA	;  /*菜单页数据结构*/
typedef struct tagMENUPAGEINFO	 MENUPAGE_INFO	;  /*(当前)菜单页信息*/
typedef struct tagOTHERTEXTDATA  OTHERTEXT_DATA	;  /*其他显示的字符串数据结构*/
/************************************************************************/
/*                         thread typedef                               */
/************************************************************************/
typedef struct tagThREAD		 THREAD_DATA	;  /*线程数据*/
typedef struct tagThREADINFO	 THREAD_INFO	;  /*线程信息*/

/************************************************************************/
/*                         channel typedef                              */
/************************************************************************/
typedef struct tagCURSOR_DATA	 CURSOR_DATA	;  /*波形窗口光标信息*/
typedef struct tagCHANNELDATA	 CHANNEL_DATA	;  /*通道数据及其他信息数据结构*/
typedef struct tagCHANNELINFO	 CHANNEL_INFO	;  /*通道信息数据结构*/
/************************************************************************/
/*                         wave typedef                                 */
/************************************************************************/
typedef enum   tagWAVEDRAWMODE		WAVE_DRAWMODE	;  /*波形显示(绘制)模式*/
typedef struct tagWAVEBASE_INFO		WAVEBASE_INFO	;  /*The Base Information of Wave*/
typedef struct tagWAVEFRAME			WAVEFRAME_DATA	;  /*波形窗口框架信息结构*/
typedef struct tagWAVEINFO			WAVE_INFO		;  /*波形信息结构*/
typedef I16	   t_ad		;  /*采样的到的数据的初始类型*/
typedef double t_real	;  /*存放采样数据转换为真实电压值的数据类型*/
typedef double t_param	;  /*测量参数类型*/

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
	STATUSBAR_INFO	*statusbar		;  /*状态栏信息*/
	INFOBAR_INFO	*infobar		;  /*信息栏数据*/
	KEY_INFO		*key_info		;  /*(当前)按键信息*/
	MENUPAGE_INFO	*page_info		;  /*(当前)菜单页信息*/
	WAVE_INFO		*wave_info		;  /*(当前)波形信息*/
	THREAD_INFO		*thread_info	;  /*(当前)当前工程线程队列信息*/

} tPROJECT_INFO;

/************************************************************************/
/*                         DPO typedef                                  */
/************************************************************************/
/*DPO类型*/
typedef enum tagDPOTYPE {
	DPO_GRAY	,  /*灰度级*/
	DPO_TEMP	,  /*色温*/
} tDPO_TYPE;
/*DPO数据结构*/
typedef struct tagDPOINFO {
	CHANNEL_DATA	*parent	;  /*父对象*/
	U8				 status	;  /*状态*/
	DPO_TYPE		 type	;  /*DPO类型*/
	int				 size	;  /*DPO处理缓存大小*/
	U8				*buff	;  /*DPO处理缓存*/

} tDPO_INFO;

/************************************************************************/
/*                        StatusBar typedef                             */
/************************************************************************/
/*状态栏信息*/
typedef struct tagSTATUSBAR_INFO {
	PROJECT_INFO		*parent		;  /*父对象*/
	GUI_RECT			 rect		;  /*状态栏信息窗口*/

	t_param				*delayTime	;  /*时延*/
	const char		   **runstatus	;  /*运行/停止状态*/
	const GUI_BITMAP	*trigtype	;  /*触发类型*/
	const char		   **trigsource	;  /*触发源*/
	t_param				*triglevel	;  /*触发电平或数字阈值*/
	
} tSTATUSBAR_INFO;

/************************************************************************/
/*                         InfoBar typedef                              */
/************************************************************************/
/*信息栏参数区域参数列表(队列)*/
typedef struct tagINFOBAR_PARAMLIST {
	U8			 id				;  /*通道号(1/2/3/4/...)*/
	const char **name			;  /*参数名字*/
	t_param		*value			;  /*参数值*/
	const char **unit			;  /*单位信息*/

} tINFOBAR_PARAMLIST;
/*信息栏数据信息*/
typedef struct tagInfoBar {
	PROJECT_INFO		*parent			;  /*父对象*/
	/******** Logo ********/
	GUI_RECT			 logo_rect		;  /*LOGO信息窗口*/
	LONG				 cnt			;  /*图标旋转计数变量*/
	/******** Acq *********/
	GUI_RECT			 acq_rect		;  /*采集信息窗口*/
	I8					 acq_fresh		;  /*使能更新数据显示*/
	const char			**acq_mode		;  /*采集模式字符串*/
	t_param				*acq_param		;  /*参数*/
	/******** ch  *********/
	GUI_RECT			 ch_rect		;  /*通道信息窗口*/
	I8					 ch_fresh		;  /*使能更新数据显示*/
	CHANNEL_DATA		*ch_data		;  /*通道数据*/
	/******** param *******/
	GUI_RECT			 param_rect		;  /*参数显示窗口框架*/
	GUI_RECT			 param_client	;  /*参数显示窗口客户区*/
	U8					 param_n		;  /*参数个数*/
	INFOBAR_PARAMLIST	 param_list[5]	;  /*参数列表(队列)*/
	
} tINFOBAR_INFO;

/************************************************************************/
/*                         key typedef                                  */
/************************************************************************/

/*************************************************************************/
#define KEY_NUM		(46) // 硬件按键个数

/********************************************************
 *
 *                   键盘编码
 */
typedef enum tagKEYDECODE {
	KEY_INVALID			= 0xFFFF,
	/************* 菜单类 编码 ********************/
	KEY_MENU_PAGE1      = 0,  /*分析类*/
	KEY_MENU_PAGE2      = 1,  /*自动定标类*/
	KEY_MENU_PAGE3      = 2,  /*通道X类*/
	KEY_MENU_PAGE4      = 3,  /*光标设置类*/
	KEY_MENU_PAGE5      = 4,  /*数字通道类*/
	KEY_MENU_PAGE6      = 5,  /*显示设置类*/
	KEY_MENU_PAGE7      = 6,  /*文件加载类*/
	KEY_MENU_PAGE8      = 7,  /*水平设置类*/
	KEY_MENU_PAGE9      = 8,  /*语言设置类*/
	KEY_MENU_PAGE10     = 9,  /*列表程序设置类*/
	KEY_MENU_PAGE11     = 10,  /*测量类*/
	KEY_MENU_PAGE12     = 11,  /*新标签类*/
	KEY_MENU_PAGE13     = 12,  /*码型类*/
	KEY_MENU_PAGE14     = 13,  /*打印配置类*/
	KEY_MENU_PAGE15     = 14,  /*参考波形类*/
	KEY_MENU_PAGE16     = 15,  /*采集设置类*/
	KEY_MENU_PAGE17     = 16,  /*屏幕保护设置类*/
	KEY_MENU_PAGE18     = 17,  /*服务类*/
	KEY_MENU_PAGE19     = 18,  /*时间设置类*/
	KEY_MENU_PAGE20     = 19,  /*触发类*/
	KEY_MENU_PAGE21     = 20,  /*触发模式和耦合类*/
	KEY_MENU_PAGE22     = 21,  /*波形发生器类*/
	KEY_MENU_PAGE23	    = 22,  /*波形数学函数类*/
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
	/************* 软键对应的硬键 编码 ********************/
	KEY_MENU_BACK       = 38,  /**/
	/************* 示波器电源开关 *****************/
	KEY_MENU_POWER      = 39,  /**/
	/*************  软键 *****************/
	KEY_MENU_SK1        = 40,  /**/
	KEY_MENU_SK2        = 41,  /**/
	KEY_MENU_SK3        = 42,  /**/
	KEY_MENU_SK4        = 43,  /**/
	KEY_MENU_SK5        = 44,  /**/
	KEY_MENU_SK6        = 45,  /**/
	/************* 旋钮 编码 ********************/
	KEY_MENU_UP		    = 26,  /*up*/
	KEY_MENU_DOWN	    = 28,  /*down*/
	KEY_MENU_OK         = 255, /**/

} tKEY_DECODE;


/*按键数据结构*/
typedef struct tagKEY {
	KEY_DECODE	index	;  /*按键索引值*/
	I8			status	;  /*按键状态*/
} tKEY_DATA;
/*(当前)按键数据信息*/
typedef struct tagKEYINFO {
	PROJECT_INFO	*parent		;  /**/
	I8				 ischange	;  /*键值改变标志*/
	KEY_DATA		 oldkey		;  /*旧键值*/
	KEY_DATA		 newkey		;  /*新键值*/
} tKEY_INFO;

/************************************************************************/
/*                       measurement typedef                            */
/************************************************************************/
/* 参数：周期、频率、正脉宽、负脉宽、正过冲、负过冲、高值、低值、最大、最 小值、峰-峰、幅值、
   平均值、周期平均值、均方根、周期均方根、上升时间、下降时间、正占空比、负占空比、猝发宽度 */

/*特殊电压阈值信息*/
typedef struct tagVOLT_THRESHOLD_DATA {
    t_param per_10	;  /*10%电压*/
    t_param per_50	;  /*50%电压*/
    t_param per_90	;  /*90%电压*/

} tVOLTTHRESHOLD_DATA;
/*The Measurement Information of Voltage*/
typedef struct tagMEAS_VOLT_DATA {
	t_param		pk_pk		;  /*^电压峰-峰值 (最大值和最小值之间的差。)(单位 : V) */
	t_param		max			;  /*^最大电平 (波形显示的最高值。)(单位 : V) */
	t_param		min			;  /*^最小电平 (波形显示的最低值。)(单位 : V) */
    t_param		amplitude	;  /*^幅度 (高值和低值之间的差。)(单位 : V) */
	t_param		top			;  /*^电压高值 (波形较高部分的众数 (最常用值)，如果未对众数做准确定义，则
								  将高值视为与最大值相同。)(单位 : V) */
	t_param		base		;  /*^电压低值 (波形较低部分的模式 (最常用值)，如果未对模式做准确定义，则
								  将低值视为与最小值相同。)(单位 : V) */
	t_param		overShoot	;  /*^电压上升沿过冲. 随光标变化 (大上升沿转换后的失真，以幅度的百分比表示。)(单位 : 百分比) */
    t_param		preShoot	;  /*^电压下降沿过冲. 随光标变化 (大下降沿转换后的失真，以幅度的百分比表示。)(单位 : 百分比) */
    t_param		average_Nth	;  /*^周期平均值 (单位 : V)。一个完整周期上波形的电压平均值*/
	t_param		average_FS	;  /*^全屏平均值 (单位 : V)。多个完整周期上波形的电压平均值*/ 
	t_param		DCrms_Nth	;  /*^周期DC-RMS (单位 : V)。一个完整周期上波形的均方根*/
	t_param		DCrms_FS	;  /*^全屏DC-RMS (单位 : V)。多个完整周期上波形的均方根*/ 
	t_param		ACrms_Nth	;  /*^周期AC-RMS (单位 : V)。一个完整周期上移除了 DC 分量的波形的均方根*/
	t_param		ACrms_FS	;  /*^全屏AC-RMS (单位 : V)。多个完整周期上移除了 DC 分量的波形的均方根*/
	t_param		ratio		;  /*^均方根比值*/

} tMEAS_VOLT_DATA;
/*The Measurement Information of Time*/
typedef struct tagMEAS_TIME_DATA {
	t_param		period		;  /*^周期 (单位 : s)*/
	t_param		freq		;  /*^周期 (单位 : Hz)*/
	t_param		phase		;  /*^两个通道波形的相位差 (相位是从源 1 至源 2 计算出的相移. )(单位 : °). */
    t_param		posWidth	;  /* 正脉宽. 随光标变化 (从上升沿的中间阈值到下一个下降沿的中间阈值的时间)(单位 : s) */
    t_param		negWidth	;  /* 负脉宽. 随光标变化 (从下降沿的中间阈值到下一个上升沿的中间阈值的时间)(单位 : s) */
    t_param		burstWidth	;  /* 猝发宽度. 随光标变化 (屏幕上从第一个沿到最后一个沿的时间)(单位 : s) */
    t_param		posDutyCycle;  /* 正占空比 (重复脉冲列的占空比是正脉冲宽度和周期的比率，以百分比表示。)(单位 : 百分比) */
    t_param		negDutyCycle;  /* 负占空比 (重复脉冲列的占空比是正脉冲宽度和周期的比率，以百分比表示。)(单位 : 百分比) */
    t_param		riseTime	;  /* 上升时间. 随光标变化 (信号的上升时间是正向沿的较低阈值交叉点和较高阈值交叉点之间的时差。)(单位 : s) */
    t_param		fallTime	;  /* 下降时间. 随光标变化 (信号的下降时间是负向沿的较高阈值交叉点和较低阈值交叉点之间的时差。)(单位 : s) */
    t_param		x_min		;  /**/
	t_param		x_max		;  /**/
	t_param		posPulseCnt	;  /*正脉宽值*/
	t_param		negPulseCnt	;  /*负脉宽值*/
	t_param		riseEdge	;  /* 针对两个通道波形的上升延迟. 随光标变化 (延迟测量最接近于触发参考点的源 1 所选边沿与源 2 所选边沿在波形中阈值点
                                  处的时间差。负延迟值表示源 1 的所选边沿出现在源 2 的所选边沿之后。)(单位 : s) */
    t_param		fallEdge	;  /* 针对两个通道波形的下降延迟. 随光标变化 (延迟测量最接近于触发参考点的源 1 所选边沿与源 2 所选边沿在波形中阈值点
                                  处的时间差。负延迟值表示源 1 的所选边沿出现在源 2 的所选边沿之后。)(单位 : s) */
    t_param		area_Nth	;  /**/
	t_param		area_FS		;  /**/
    
} tMEASTIME_DATA;
/*测量类参数列表*/
typedef union tagMEAS_PARAM_LIST {
	t_param			list[33]	;  /**/
	struct {
		MEASVOLT_DATA	v			;  /**/
		MEASTIME_DATA	t			;  /**/
	} i;
} tMEASPARAM_LIST;
/*测量数据信息*/
typedef struct tagMEASUREINFO {
	CHANNEL_DATA		*parent		;  /*父对象*/
	VOLTTHRESHOLD_DATA   vt			;  /*特殊电压阈值信息*/
	MEASPARAM_LIST		 param		;  /*测量类参数列表*/

} tMEASURE_INFO;

/************************************************************************/
/*                         menu typedef                                 */
/************************************************************************/
/*语言切换类*/
typedef enum tagLanguageType {
	eEnglish			,  /*英文*/
	eFrench				,  /*法文*/
	eGerman				,  /*德文*/
	eItalian			,  /*意大利文*/
	eJapanese			,  /*日文*/
	eKorean				,  /*韩文*/
	ePortuguese			,  /*??*/
	eRussian			,  /*俄文*/
	eSimplifiedChinese	,  /*简体中文*/
	eSpanish			,  /*西班牙文*/
	eTraditionalChinese	,  /*繁体中文*/

} tLANGUAGE_TYPE;
/*字库切换类[必须与LANGUAGE_TYPE一一对应]*/
typedef enum tagFontType {
	efontEnglish			,  /*英文字库类*/
	efontFrench				,  /*法文字库类*/
	efontGerman				,  /*德文字库类*/
	efontItalian			,  /*意大利文字库类*/
	efontJapanese			,  /*日文字库类*/
	efontKorean				,  /*韩文字库类*/
	efontPortuguese			,  /*??字库类*/
	efontRussian			,  /*俄文字库类*/
	efontSimplifiedChinese	,  /*简体中文字库类*/
	efontSpanish			,  /*西班牙文字库类*/
	efontTraditionalChinese	,  /*繁体中文字库类*/

} tFONT_TYPE;
/*菜单页切换类*/
typedef enum tagMenuPageType {
	eAnalyze		,  /*分析类*/
	eAutoScale		,  /*自动定标类*/
	eChannelInfo	,  /*通道X类*/
	eCursorSet		,  /*光标设置类*/
	eDigitalChannel	,  /*数字通道类*/
	eDisplaySet		,  /*显示设置类*/
	eFileLoad		,  /*文件加载类*/
	eHorizontalSet	,  /*水平设置类*/
	eLanguage		,  /*语言设置类*/
	eLister			,  /*列表程序设置类*/
	eMeasure		,  /*测量类*/
	eNewLabel		,  /*新标签类*/
	ePattern		,  /*码型类*/
	ePrintSet		,  /*打印配置类*/
	eReferWaveform	,  /*参考波形类*/
	eSamplingSet	,  /*采集设置类*/
	eScreenSaverSet	,  /*屏幕保护设置类*/
	eService		,  /*服务类*/
	eTimeSet		,  /*时间设置类*/
	eTrigger		,  /*触发类*/
	eTriggerCoupling,  /*触发模式和耦合类*/
	eWaveformGen	,  /*波形发生器类*/
	eWaveformMath	,  /*波形数学函数类*/

} tMENUPAGE_TYPE;
/*上拉菜单栏选项属性*/
typedef enum tagMenuItemOption {
	MENUUP_IF_TITLE		,  /*标题栏*/
	MENUUP_IF_MENU		,  /*菜单项*/
	MENUUP_IF_SEPARATOR	,  /*分隔线*/
	MENUUP_IF_DISABLED	,  /*未激活状态*/
	MENUUP_IF_ENABLED 	,  /*激活状态*/

} tMENUITEN_OPTION;
/*软键属性*/
typedef enum tagSoftKeyOption {
	SOFTKEY_IF_EMPTY		,  /*不存在软键*/
	SOFTKEY_IF_NOBK			,  /*没有背景的软键*/
	SOFTKEY_IF_RECT			,  /*下方带方框的软键*/
	SOFTKEY_IF_DISABLED		,  /*存在软键但无效的软键[需要在更新时清除][也是默认状态]*/
	SOFTKEY_IF_NEXT			,  /*存在软键但无效的软键[需要在更新时清除][也是默认状态]*/
	SOFTKEY_IF_STATIC		,  /*固定型软键[在当前页不改变状态]*/
	SOFTKEY_IF_SELRECT		,  /*激活状态[软键对应的硬键被选中]*/
	SOFTKEY_IF_ACTIVATE		,  /*激活状态[软键对应的硬键被选中]*/
	SOFTKEY_IF_MENU			,  /*激活上拉菜单[]*/

} tSOFTKEY_OPTION;
/*菜单信息处理数据结构*/
typedef struct tagMenuMeg{
	U16		msgtype	;  /**/
	U16		itemid	;  /**/
} tMENUMSG_DATA;
/*上拉菜单选项数据结构*/
typedef struct tagMenuItem {
	U8                id		;  /*索引*/
	MENUITEM_OPTION   option	;  /*属性: MENUUP_OPTION_TITLE or MENUUP_OPTION_MENU or MENUUP_OPTION_SEPARALINE*/
	const GUI_BITMAP *icon		;  /*菜单项icon*/
	MENUPAGE_DATA	 *next		;  /*下一页(双向链表)*/
	U8                status	;  /*状态: 1--选中;0--没选中*/
	const char       *title		;  /*当其属性为MENUUP_OPTION_TITLE时存取title, 为MENUUP_OPTION_MENU时存取文本字符串*/
	const char		 *kword		;  /*名字(关键字)*/
	const char       *help		;  /*帮助文档*/

} tMENUITEM_DATA;
/*上拉菜单数据结构*/
typedef struct tagMenuUp {
	U8               itemn		;  /*菜单选项个数[包括分隔线和标题]*/
	MENUITEM_DATA   *item		;  /*选项列表*/
	MENUPAGE_DATA	*back		;  /*上一页(双向链表)*/
	void          *(*task)(PROJECT_INFO *info,I8 id);  /*函数*/
	U8               menun		;  /*菜单项个数*/
	GUI_RECT         frame		;  /*上拉菜单定标*/
	GUI_RECT		 client		;  /*客户区*/
	I16				 width,height;  /*上拉菜单尺寸*/
	I16				 MaxXSize	;  /*上拉菜单的菜单选项中的最长宽度*/
	U8               status		;  /*状态: 1--选中;0--没选中*/
	const char      *title		;  /*menu title*/
	/*++++++++++++++++++++++++++++*/
	I8				 index		;  /*上拉菜单项计数变量*/
	I8				 top,base	;  /*当前上拉菜单的菜单项[起始]和[终止]索引[不包括分隔线和标题栏]*/
	I8				 dispdir	;  /*上拉菜单显示方向[=1表示往上;=0表示往下][默认为往下]*/
	/*++++++++++++++++++++++++++++*/
} tMENUUP_DATA;
/*软键数据结构*/
typedef struct tagSoftKey {
	U8                    id		;  /*索引*/
	SOFTKEY_OPTION        option	;  /*状态: 1--选中;0--没选中*/
	void              *(*task)(PROJECT_INFO *info,I8 id)	;  /*函数*/
	MENUPAGE_DATA		 *next		;  /*下一页(双向链表)*/
	MENUUP_DATA          *menuup	;  /*所属上拉菜单*/
	const GUI_BITMAP	 *icon		;  /*图标类关键字*/
	const char			 *title		;  /*标题*/
	const char			 *ktype		;  /*关键字类型字符串*/

} tSOFTKEY_DATA;
/*菜单页数据结构*/
typedef struct tagMenuPage {
	U8                   n		;  /*所在本级菜单的软键个数*/
	SOFTKEY_DATA        *sk		;  /*所属软键列表*/
	MENUPAGE_DATA		*back	;  /*上一页(双向链表)*/
	const char 			*others	;  /*本菜单页中的其他固定软键编号(以字符串形式需要时在每个软键中给出)*/
	const char          *title	;  /*菜单页标题*/
	const char			*kword	;  /*名字(关键字)*/

} tMENUPAGE_DATA;
/*菜单页数据信息*/
typedef struct tagMENUPAGEINFO {
	PROJECT_INFO		*parent		;  /*父对象*/
	LANGUAGE_TYPE		 langtype 	;  /*当前初始化语言种类*/
	I8					 hide		;  /*上拉菜单自动隐藏标志(当有按键响应时复位，当延时到时隐藏菜单，=1有效)*/
	I8					 enhide		;  /*使能隐藏上拉菜单*/
	I8					 enExt		;  /*使能附加菜单*/
	GUI_RECT			 extFrame,extClient	;  /*附加菜单区域和客户区域*/
	void              *(*task)(PROJECT_INFO *info,I8 id)	;  /*函数[这个函数在需要占用部分波形区域显示时使用]*/

	MENUPAGE_TYPE		 number		;  /*当前页的序号*/
	MENUPAGE_DATA		*back		;  /*双向链表指针变量*/
	MENUPAGE_DATA		*now    	;  /*当前处于激活状体的菜单页*/
	MENUPAGE_DATA		*next		;  /*双向链表指针变量*/
	I8					 id			;  /*当前页中处于激活状态的软件ID号*/
	SOFTKEY_DATA		 sk[6]		;  /*当前处于激活状态的软键*/

} tMENUPAGE_INFO;
/*其他显示的字符串数据结构*/
typedef struct tagOTHERTEXTDATA {
	const char		*runstatus[2];	/*运行/停止状态*/
} tOTHERTEXT_DATA;

/************************************************************************/
/*                         thread typedef                               */
/************************************************************************/
// 线程堆栈数据类型定义
#if defined(OS_UCOS)  /*uCOS System*/
#define UCOS_STKMAX	(256)
//typedef OS_STK			thread_stack[UCOS_STKMAX]	;

#else /*Linux system*/
//typedef pthread_t		thread_stack

#endif

/*线程信息结构*/
typedef struct tagThREAD {
	U8				 id					;  /*线程id*/
	void		   (*task)(void *p_arg)	;  /*任务函数*/
	void			*p_arg				;  /*任务输入参数*/
#if defined(OS_UCOS)  /*uCOS System*/
	OS_STK			 stack[UCOS_STKMAX]	;  /*线程堆栈*/
#else   /*Linux system*/
	pthread_t		 stack	 			;  /*线程堆栈*/	
#endif
	U8				 status				;  /*任务状态*/
} tTHREAD_DATA;

/*线程信息结构*/
typedef struct tagThREADINFO {
	PROJECT_INFO	*parent	;  /*父对象*/
	U8				 offset	;  /*id偏移量*/
	U8				 n		;  /*线程个数*/
	THREAD_DATA	    *task	;  /*任务列表*/
} tTHREAD_INFO;

/************************************************************************/
/*                         channel typedef                              */
/************************************************************************/
/*波形窗口光标信息*/
typedef struct tagCURSOR_DATA {
	const GUI_BITMAP *icon		;  /*菜单项icon*/
	int				  x			;  /**/
	int				  y			;  /**/
	t_param			  sens		;  /*水平(垂直)灵敏度*/

} tCURSOR_DATA;
/*通道数据及其他信息数据结构*/
typedef struct tagCHANNELDATA {
	CHANNEL_INFO   *parent	;  /*父对象*/
	/*base data info*/
	U8				id		;  /*当前通道号[1,2,...]*/
	U8				status	;  /**/
	COLOR			color	;  /*通道颜色*/
	t_param			zoom	;  /*衰减倍数*/
	I16				start	;  /**/
	I16				end		;  /**/
	U16				sampleN	;  /*通道原始数据点数(默认为 )*/
	t_ad		   *sort	;  /*排序暂存值*/
	t_ad		   *sample	;  /*通道数据*/
	t_real		   *real	;  /*存放采样数据转换为真实电压值*/
	CURSOR_DATA		hcursor	;  /*水平光标*/
	CURSOR_DATA		vcursor	;  /*垂直光标*/

	/*more ...*/
	MEASURE_INFO	measure	;  /*测量类信息*/
	DPO_INFO	    dpo		;  /*DPO数据信息*/

} tCHANNEL_DATA;
/*通道信息数据结构*/
typedef struct tagCHANNELINFO {
	WAVE_INFO		*parent		;  /*父对象*/
	U8				 n			;  /*总通道个数*/
	I8				 validn		;  /*当前处于工作状态的通道个数*/
	CHANNEL_DATA	*action		;  /*当前通道(1/2/3/4/...)*/
	CHANNEL_DATA	 ch[4]		;  /*数字通道数据结构*/
	LONG			 dpocnt		;  /*DPO计数器*/

} tCHANNEL_INFO;

/************************************************************************/
/*                         wave typedef                                 */
/************************************************************************/
/*波形显示(绘制)模式*/
typedef enum tagWAVEDRAWMODE {
	WAVE_DRAWMODE_DOT	,  /*点*/
	WAVE_DRAWMODE_LINE	,  /*线(矢量)*/
	WAVE_DRAWMODE_GRAY	,  /*灰度级*/
	WAVE_DRAWMODE_TEMP	,  /*色温*/
} tWAVE_DRAWMODE;
//I16* pay, int NumPoints, int xoff, int yoff, int ExPoints
/*The Base Information of Wave*/
typedef struct tagWAVEBASE_INFO {
	t_param  hSens	;  /*波形显示窗口水平灵敏度*/
	t_param  vSens	;  /*波形显示窗口垂直灵敏度*/
	t_param  Period	;  /*周期(单位 : s)*/
	t_param  Vmax	;  /*最大电平 (波形显示的最高值。)(单位 : V)*/
	t_param  Vmin	;  /*最小电平 (波形显示的最低值。)(单位 : V)*/

} tWAVEBASE_INFO;
/*波形窗口框架信息结构*/
typedef struct tagWAVEFRAME {
	GUI_RECT	frame	;
	GUI_RECT	client	;

} tWAVEFRAME_DATA;
/*波形信息结构*/
typedef struct tagWAVEINFO {
	PROJECT_INFO	*parent		;  /*父对象*/
	WAVEFRAME_DATA	 frame		;  /**/
	I8				 gridrate	;  /*波形区域网格亮度*/
	U16				 gridcolor	;  /*波形区域网格颜色*/
	I8				 wavecnt	;  /*波形绘制计数器(记录一次性绘制次数)*/
	WAVE_DRAWMODE	 mode		;  /**/	
	CHANNEL_INFO	*ch			;  /*通道*/

} tWAVE_INFO;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#pragma pack()


#endif /**/
