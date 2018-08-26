
#ifndef DSO_THREAD_H
#define DSO_THREAD_H

#include "dso_type.h"


/**********************************************************
 *
 *                    Task ID
 */
#define TASK_NUM			(7)
#define TASK_OFFSET_ID		(4)

#define TASK_DSO_ID			(0)
#define TASK_MEASURE_ID		(1)
#define TASK_LOGO_ID		(2)
#define TASK_PROKEY_ID		(3)
#define TASK_GETKEY_ID		(4)
#define TASK_HIDEMENU_ID	(5)
#define TASK_COUNTER_ID		(6)
/**********************************************************
 *
 *                 thread functions
 */
void thread_initOS(void);
void thread_start(void);
void thread_ready(void);
void thread_lock(void);
void thread_unlock(void);
void thread_delay(I8 hours, I8 minutes, I8 seconds, I8 milli);
int  thread_create(THREAD_INFO *info, U8 id,void(*task)(void *p_arg),void *p_arg);
int  thread_reCreate(THREAD_INFO *info,U8 id,void(*task)(void *p_arg),void *p_arg);
int  thread_delete(THREAD_INFO *info, U8 id);
int  thread_suspend(THREAD_INFO *info, U8 id);
int  thread_resume(THREAD_INFO *info, U8 id);

/**********************************************************
 *
 *                 thread tasks
 */
void thread_init(THREAD_INFO *info);
void thread_task_dso(void *p_arg);
void thread_task_measure(void *p_arg);
void thread_task_logo(void *p_arg);
void thread_task_getKey(void *p_arg);
void thread_task_proKey(void *p_arg);
void thread_task_hideMenu(void *p_arg);
void thread_task_counter(void *p_arg);


#endif /**/
