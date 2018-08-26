
#include "thread.h"
#include <stdlib.h>


/*线程初始化*/
void thread_initOS(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSInit();
#else                 /*Linux system*/

#endif
}
// 线程开始
void thread_start(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSStart();
#else                 /*Linux system*/

#endif
}
// 线程准备好
void thread_ready(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSStatInit();
#else                 /*Linux system*/

#endif
}
/*给调度器上锁*/
void thread_lock(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSSchedLock();
#else                 /*Linux system*/

#endif
}
/*给调度器解锁*/
void thread_unlock(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSSchedUnlock();
#else                 /*Linux system*/

#endif
}
/****************************************************************
 *
 *                         线程延时
 *
 *1 s = 10^3 ms（毫秒） = 10^6 us （微秒）= 10^9 ns（纳秒） = 10^12 ps（皮秒)\
 *  = 10^15 fs（飞秒）=10^18阿秒=10^21渺秒=10^43普朗克常数 
 */
void thread_delay(I8 hours, I8 minutes, I8 seconds, I8 milli) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSTimeDlyHMSM(hours,minutes,seconds,milli);
#else                 /*Linux system*/
	usleep(1);
#endif
}
/*建立一个任务（这里的id号在当前所有任务中是连续的）*/
int thread_create(THREAD_INFO *info, U8 id,void(*task)(void *p_arg),void *p_arg) {
	if(id > info->task[info->n-1].id)
		return -1;
	info->task[id].id		= info->offset + id;
	info->task[id].task		= task;
	info->task[id].p_arg	= p_arg;
	info->task[id].status	= 1;
#if defined(OS_UCOS)  /*uCOS System*/
	return OSTaskCreate(task,p_arg,&info->task[id].stack[UCOS_STKMAX-1],id);
#else                 /*Linux system*/
	return pthread_create(&info->task[id].stack,NULL,(void*(*)(void *))task,p_arg);
#endif
}
/*重建一个任务*/
int  thread_reCreate(THREAD_INFO *info,U8 id,void(*task)(void *p_arg),void *p_arg) {
	if(thread_delete(info,id) < 0) return -1;
	if(thread_create(info,id,task,p_arg) < 0) return -1;
	return 0;
}
/*删除一个任务*/
int thread_delete(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return USR_OSTaskDel(info->task[id].id);
#else                 /*Linux system*/
	return pthread_cancel(info->task[id].stack);
#endif
}
// 挂起任务
int thread_suspend(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return OSTaskSuspend(info->task[id].id);
#else                 /*Linux system*/
	return -1;
#endif
}
// 唤醒任务
int thread_resume(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return OSTaskResume(info->task[id].id);
#else                 /*Linux system*/
	return -1;
#endif
}