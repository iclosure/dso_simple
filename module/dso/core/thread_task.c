
#include "thread.h"
#include "key.h"
#include "dso.h"
#include "menu.h"
#include "wave.h"
#include "meas.h"
#include <math.h>


/**********************************************************
 *
 *                  global rariale
 */
/**/
static THREAD_DATA _thread_data[TASK_NUM] = {
	{TASK_DSO_ID,thread_task_dso,},
	{TASK_MEASURE_ID,thread_task_measure,},
	{TASK_MEASURE_ID,thread_task_logo,},
	{TASK_PROKEY_ID,thread_task_proKey,},
	{TASK_GETKEY_ID,thread_task_getKey,},
	{TASK_HIDEMENU_ID,thread_task_hideMenu,},
	{TASK_COUNTER_ID,thread_task_counter,},
	
};
/**/
THREAD_INFO	threadinfo = {	/*当前工程线程队列信息*/
	NULL, TASK_OFFSET_ID, TASK_NUM, _thread_data,
};
/**********************************************************
 *
 *                  thread functions
 */
/*主进程任务*/
void thread_task_dso(void *p_arg) {
	PROJECT_INFO *info=(PROJECT_INFO*)p_arg;
	thread_ready();
	while (1) {
		/*应用程序*/
		dso_task(info);
		/*延时*/
		thread_delay(0,0,0,5);
	}
}
/*参数计算和显示任务*/
void thread_task_measure(void *p_arg) {
	WAVE_INFO *info=(WAVE_INFO *)p_arg;
	thread_ready();
	while(1) {
		/*应用程序*/
		meas_task(info);
		/*延时100ms*/
		thread_delay(0,0,0,100);
	}
}
/*LOGO显示进程*/
void thread_task_logo(void *p_arg) {
	INFOBAR_INFO *info=(INFOBAR_INFO*)p_arg;
	char sign=-1;
	I16 x0 = info->logo_rect.x0+(INFOBAR_XSIZE-bmLogo.XSize)/2;
	I16 y0 = info->logo_rect.y0+(INFOBAR_LOGO_HEIGHT+5-bmLogo.YSize)/2;
	thread_ready();
	while(1) {
		thread_lock();
		GUI_ClearBitmap(&bmLogo,x0,y0,BAR_FILLCOLOR);
		GUI_DrawBitmapEx(&bmLogo,x0+bmLogo.XSize/2,y0,bmLogo.XSize/2,0,info->cnt,1000);
		thread_unlock();
		if(sign == 1)
			info->cnt += 10;
		else if(sign == -1)
			info->cnt -= 10;
		if(info->cnt >= 1000)
			sign = -1;
		if(info->cnt <= -1000)
			sign = 1;
		/*延时*/
		thread_delay(0,0,0,5);
	}
}
/*按键响应处理任务*/
void thread_task_proKey(void *p_arg) {
	KEY_INFO *info=(KEY_INFO*)p_arg;
	info->newkey.index = KEY_INVALID;
	thread_ready();
	while (1) {
		/*响应按键*/
#if defined(WIN32)
		if(info->newkey.index == KEY_MENU_POWER) break;
#endif
		thread_lock();
		key_response(info);
		info->newkey.index = KEY_INVALID;
		thread_unlock();
		/*延时*/
		thread_delay(0,0,0,5); 
	}
}
/*获取按键任务*/
void thread_task_getKey(void *p_arg) {
	KEY_INFO *info=(KEY_INFO*)p_arg;
	thread_ready();
	while (1) {
		/*读取按键*/
		key_getDecode(info);
		/*延时*/
		thread_delay(0,0,0,5); 
	}
}
/*自动隐藏上拉菜单任务*/
void thread_task_hideMenu(void *p_arg) {
	MENUPAGE_INFO *info = (MENUPAGE_INFO*)p_arg;
	thread_ready();
	while(1) {
		if(info->hide == 0) {
			/* 延时 5 秒 */
			loop : info->enhide = 1;
			thread_delay(0,0,5,0);
			if(info->enhide == 0) goto loop;
			menu_clearMenuUp(info);
		}
		/*延时*/
		thread_delay(0,0,0,5);
	}
}
/*模拟计数器进程*/
void thread_task_counter(void *p_arg) {
	thread_ready();
	while(1) {
		/* 延时 15 秒 */
		thread_delay(0,0,5,0);
		//if() {
				
		//}
	}
}