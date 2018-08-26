
#include "key.h"
#include "dso_fileDir.h"
#include "dso.h"
#include "global.h"
#include "menu.h"
#include "wave.h"
#include "dpo.h"
#include "thread.h"
#include "bmp.h"
#include <string.h>
#if defined(WIN32)  /*Windows System*/
#include "Win.h"
#endif

GUI_RECT	SoftKeyArea= {SOFTKEY_SX,SOFTKEY_SY,SOFTKEY_EX,SOFTKEY_EX};  /*波形绘制窗口*/

/************************************************************
 *
 *
 */
KEY_INFO keyinfo	;  /*(当前)按键信息*/

/*******************************************************************
 *
 *                   public code
 */
#if defined(WIN32)  /*Windows System*/
/*复位系统(针对WIN32仿真而言)*/
static void _resetSystem(PROJECT_INFO *info) {
	/*清屏*/
	GUI_SetBkColor(DesktopBkColor);
	GUI_Clear();
	lcd_display();
	// 
	/*释放指针变量占用的空间*/
	dso_initVariable(info,1);
	/*复位所有变量*/
	//
	// 刷新波形窗口
	wave_fresh();
	// 清DPO缓存
	dpo_clearAll(info->wave_info->ch);
}
#else             /*Linux system*/

#endif
/*主函数入口*/
// 
void key_getDecode(KEY_INFO *info) {
	int i=0;
	KEY_DATA *key=&info->newkey;
	key->index = KEY_INVALID;
#if defined(WIN32)  /*Windows System*/
	do{
		key->status = SIM_HARDKEY_GetState(i);
		if(key->status)
		{
			key->index = i;
			if(key->index != info->oldkey.index) {
				info->oldkey.index = key->index;
				info->ischange = 1;
			} else {
				info->ischange = 0;
			}
			while(SIM_HARDKEY_GetState(i));  /*等待按键松开*/
			break;
		}
	} while(++i < KEY_NUM);
	/*模拟电源开关功能*/
	/********************************/
	if(key->index == KEY_MENU_POWER) {
		thread_lock();
		_resetSystem(info->parent);
		/*模拟电源开关功能*/
		/********************************/
		while(SIM_HARDKEY_GetState(KEY_MENU_POWER) == 0);  /*读取按键状态*/;
		while(SIM_HARDKEY_GetState(KEY_MENU_POWER) == 1);  /*等待按键松开*/
		/********************************/
		dso_init(info->parent);
		thread_unlock();
		dso_start(info->parent);
	}
#else           /*Linux system*/
	i=0;
#endif
}
/*Up按键处理函数*/
void key_up(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	menuup_clrStatus(menu,menu->index);
	menu->index --;
	if(menu->index < 0) {  /*将MenuIndex下限限制在0*/
#ifdef MENUUP_UP_CYCLE
		menu->index= menu->menun-1;
#else
		menu->index++;
#endif
	}
	menuup_setStatus(menu,menu->index); 
	menu_preDraw1MenuUp(info);
}
/*Down按键处理函数*/
void key_down(MENUPAGE_INFO *info) {
	MENUUP_DATA *menu=info->sk[info->id].menuup;
	menuup_clrStatus(menu,menu->index);
	menu->index ++;
	if(menu->index >= menu->menun) {
#ifdef MENUUP_DOWN_CYCLE
		menu->index= 0;
#else
		menu->index--;
#endif
	}
	menuup_setStatus(menu,menu->index);
	menu_preDraw1MenuUp(info);
}
static void _displayMenuUp(MENUPAGE_INFO *info,U8 id);
/*一键返回上一级[页]菜单*/
void key_back(MENUPAGE_INFO *info) {
	if(info->back) {
		if(info->sk[info->id].menuup)
			menu_clearMenuUp(info);
		menu_setNewPage(info,info->back,-1);
	}
}
/*再次激活已被激活的有上拉菜单的软键处理函数*/
static void _doActionMenuUp(MENUPAGE_INFO *info,void(*key_dir)(MENUPAGE_INFO *)) {
	if(info->hide == 1) {  /*激活当前隐藏的上拉菜单*/
		if(info->task && info->enExt==0) {
			info->task(info->parent,info->id);
		} else {
			info->hide  = 0;
			info->enExt = 0;
			menu_drawFrame(info); /*恢复隐藏的上拉菜单*/
		}
	} else {
		info->enhide = 0;
		key_dir(info);
	}
	menu_drawOneSoftKey(info,0,info->id);
}
/*处理旋钮函数*/
static void _doEntryKey(MENUPAGE_INFO *info) {
	SOFTKEY_DATA *sk=&info->sk[info->id];
	KEY_DECODE key=info->parent->key_info->newkey.index;
	if(sk->option == SOFTKEY_IF_MENU) { /*SOFTKEY_IF_MENU*/
		if(key == KEY_MENU_UP) {
			_doActionMenuUp(info,key_up); 
		} else {
			_doActionMenuUp(info,key_down); 
		}
	} else if(sk->option == SOFTKEY_IF_ACTIVATE){ /*SOFTKEY_IF_ACTIVATE*/
		if(key == KEY_MENU_UP) {
			/**/
		} else {
			/**/
		}
		if(sk->task)
			sk->task(info->parent,info->id);
	}

}
/*响应按键*/
void key_response(KEY_INFO *info) {
	KEY_DATA *key=&info->newkey;
	MENUPAGE_INFO *page_info=info->parent->page_info;
	CHANNEL_INFO  *ch_info=info->parent->wave_info->ch;
	/**********************/
	if(page_info->hide == 1)
		thread_suspend(info->parent->thread_info, TASK_HIDEMENU_ID);
	else if(page_info->hide == 0) 
		thread_resume(info->parent->thread_info, TASK_HIDEMENU_ID);
	/**********************/
	if(KEY_MENU_PAGE1<=key->index && key->index<=KEY_MENU_PAGE23) {
		if(page_info->number != key->index-KEY_MENU_PAGE1) {
			page_info->number = key->index-KEY_MENU_PAGE1;
			menu_setNewPage(page_info,menu_all[page_info->number],0);
		} return ;
	}
	if(KEY_MENU_SK1<=key->index && key->index<=KEY_MENU_SK6) {
		menu_selectSoftKey(page_info,key->index-KEY_MENU_SK1); 
		return ;
	}
	switch(key->index) {
	case KEY_MENU_CH1	: channel_select(ch_info,0); break;
	case KEY_MENU_CH2	: channel_select(ch_info,1); break;
	case KEY_MENU_CH3	: channel_select(ch_info,2); break;
	case KEY_MENU_CH4	: channel_select(ch_info,3); break;
	case KEY_MENU_HELP	: if(page_info->hide==0) page_info->enExt = !page_info->enExt;break;
	case KEY_MENU_BM_24	: bmp_to24bpp(info->parent,FILEDIR_OUT_BM_24); break;
	case KEY_MENU_BACK	: key_back(page_info); break;
	case KEY_MENU_UP	:
	case KEY_MENU_DOWN	: _doEntryKey(page_info); break;
	case KEY_MENU_OK	: break;
	case KEY_INVALID	: 
	default				: break;
	}
}
/*判断id是否是当前菜单页中存在(有效)的软键id*/
static I8 _isValidId(MENUPAGE_INFO info,U8 id) {
	switch(info.sk[id].option) {
	case SOFTKEY_IF_EMPTY: return -1;
	case SOFTKEY_IF_NOBK : return -1;
	default : return 1;
	}
}
/**/
static void _displayMenuUp(MENUPAGE_INFO *info,U8 id) {
	info->sk[id].option = SOFTKEY_IF_MENU;
	info->hide = 0;
	info->enExt = 0;
	info->task = NULL;
	menu_drawMenuUp(info);
	info->sk[id].menuup->status = 1;
}
/**/
void menu_selectSoftKey(MENUPAGE_INFO *info,U8 id) {
	if(_isValidId(*info,id) < 0)
		return ;
	if(info->id == id) {  /*选择上一次激活的软键*/
		switch(info->sk[id].option) {
		case SOFTKEY_IF_NEXT: menu_setNewPage(info,info->sk[id].next,1); break;
		case SOFTKEY_IF_STATIC:
			if(info->sk[id].menuup) {  /*激活所属上拉菜单并初始化显示在屏幕上*/
				_displayMenuUp(info,id);
			} else {
				info->sk[id].option = SOFTKEY_IF_ACTIVATE;
			}
			menu_drawOneSoftKey(info,1,id);
			break;
		case SOFTKEY_IF_MENU:
			_doActionMenuUp(info,key_down);
			break;
		default: break;
		}
	} else {
		SOFTKEY_DATA *oldsk,*newsk;
		/*处理旧软键*/
		oldsk = &info->sk[info->id];
		if(oldsk->option==SOFTKEY_IF_ACTIVATE || oldsk->option==SOFTKEY_IF_MENU) {
			if(oldsk->option == SOFTKEY_IF_MENU) {
				menu_clearMenuUp(info);
			}
			oldsk->option = SOFTKEY_IF_STATIC;
			menu_drawOneSoftKey(info,0,info->id);
		} else if(oldsk->option == SOFTKEY_IF_SELRECT) {
			oldsk->option = SOFTKEY_IF_RECT;
			menu_drawOneSoftKey(info,0,info->id);
		}
		/*处理新软键*/
		info->id = id; newsk = &info->sk[id];
		if(newsk->option == SOFTKEY_IF_STATIC) {  /*激活SOFTKEY_IF_STATIC属性的软键*/
			if(newsk->menuup) {
				info->enhide = 0;
				_displayMenuUp(info,id);
			} else {
				newsk->option = SOFTKEY_IF_ACTIVATE;
			}
		} else if(newsk->next) {
			if(newsk->next) {
				menu_setNewPage(info,newsk->next,1);
				return;
			}
		} else if(newsk->option == SOFTKEY_IF_RECT) {
			newsk->option = SOFTKEY_IF_SELRECT;
		}
		menu_drawOneSoftKey(info,1,id);
	}
}
