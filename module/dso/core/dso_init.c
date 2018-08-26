
#include "GUI.h"
#include "GUI_Protected.h"
#include "dso.h"
#include "meas.h"
#include "menu.h"
#include "wave.h"
#include "thread.h"
#include <string.h>
#include <stdio.h>


// ��λϵͳ(���WIN32�������)
void dso_reset(PROJECT_INFO *info) {
	LCD_SelectLCD(1);
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	/*****************����*******************/
	GUI_SetBkColor(DesktopBkColor);
	GUI_Clear();
	/*****************�˵�ҳ******************/
	menu_setNewPage(info->page_info,info->page_info->now,0);
	/*****************���********************/
	wave_expFrame();
	wave_setNetAndGrid(info->wave_info,30);
	infobar_init(info->infobar);
	statusbar_initStatic(info->statusbar);
	wave_init(info->wave_info);
	param_init(info);
	/******************��ʾ*******************/
	lcd_display();
}
// ��ʼ��DSO
void dso_init(PROJECT_INFO *info) {
	GUI_Init();
	dso_initVariable(info,0);
	meas_init(info->wave_info);
	thread_init(info->thread_info);
	dso_reset(info);
}
/*��ʼ����ϵͳ*/
void dso_start(PROJECT_INFO *info) {
	thread_start();
	thread_suspend(info->thread_info,TASK_HIDEMENU_ID);
}

/* ʱ����� */
/*
//#include <sys/time.h>
#i fdefined(LINUX)
void runTimeTest(void)
{
	struct timeval tv;
	float t1,t2;
	
	gettimeofday(&tv, NULL);
	t1 = (tv.tv_sec + tv.tv_usec)/1024.0;
	// 
	// (������ӱ������)
	// 
	gettimeofday(&tv, NULL);
	t2 = (tv.tv_sec + tv.tv_usec)/1024.0;
	printf("t2-t1 = %f\n",t2-t1);
}
#endif 
*/
