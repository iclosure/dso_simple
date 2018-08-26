
#include "thread.h"


/***********************************************************
 *
 *                  init currentthread
 */
THREAD_INFO		threadinfo;   /*当前工程线程队列信息*/

/***********************************************************
 *
 *
 */
void thread_init(THREAD_INFO *info) {
	thread_initOS();
	thread_create(info, TASK_DSO_ID,thread_task_dso,info->parent);
	thread_create(info, TASK_MEASURE_ID,thread_task_measure,info->parent->wave_info);
	thread_create(info, TASK_LOGO_ID,thread_task_logo,info->parent->infobar);
	thread_create(info, TASK_PROKEY_ID,thread_task_proKey,info->parent->key_info);
	thread_create(info, TASK_GETKEY_ID,thread_task_getKey,info->parent->key_info);
	thread_create(info, TASK_HIDEMENU_ID,thread_task_hideMenu,info->parent->page_info);

}
