
#include "dso.h"
#include "meas.h"
#include "menu.h"
#include "wave.h"
#include "thread.h"


void dso_task(PROJECT_INFO *info) {
	/**/
	thread_lock();
	wave_task(info->wave_info);
	thread_unlock();
	/*上拉菜单事件处理*/
	menu_task(info->page_info);
	/*显示缓存数据到实际屏幕上*/
	thread_lock();
	lcd_display();
	thread_unlock();
}
