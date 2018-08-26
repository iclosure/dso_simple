
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
	/*�����˵��¼�����*/
	menu_task(info->page_info);
	/*��ʾ�������ݵ�ʵ����Ļ��*/
	thread_lock();
	lcd_display();
	thread_unlock();
}
