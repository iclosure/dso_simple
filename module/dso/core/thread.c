
#include "thread.h"
#include <stdlib.h>


/*�̳߳�ʼ��*/
void thread_initOS(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSInit();
#else                 /*Linux system*/

#endif
}
// �߳̿�ʼ
void thread_start(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSStart();
#else                 /*Linux system*/

#endif
}
// �߳�׼����
void thread_ready(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSStatInit();
#else                 /*Linux system*/

#endif
}
/*������������*/
void thread_lock(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSSchedLock();
#else                 /*Linux system*/

#endif
}
/*������������*/
void thread_unlock(void) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSSchedUnlock();
#else                 /*Linux system*/

#endif
}
/****************************************************************
 *
 *                         �߳���ʱ
 *
 *1 s = 10^3 ms�����룩 = 10^6 us ��΢�룩= 10^9 ns�����룩 = 10^12 ps��Ƥ��)\
 *  = 10^15 fs�����룩=10^18����=10^21����=10^43���ʿ˳��� 
 */
void thread_delay(I8 hours, I8 minutes, I8 seconds, I8 milli) {
#if defined(OS_UCOS)  /*uCOS System*/
	OSTimeDlyHMSM(hours,minutes,seconds,milli);
#else                 /*Linux system*/
	usleep(1);
#endif
}
/*����һ�����������id���ڵ�ǰ�����������������ģ�*/
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
/*�ؽ�һ������*/
int  thread_reCreate(THREAD_INFO *info,U8 id,void(*task)(void *p_arg),void *p_arg) {
	if(thread_delete(info,id) < 0) return -1;
	if(thread_create(info,id,task,p_arg) < 0) return -1;
	return 0;
}
/*ɾ��һ������*/
int thread_delete(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return USR_OSTaskDel(info->task[id].id);
#else                 /*Linux system*/
	return pthread_cancel(info->task[id].stack);
#endif
}
// ��������
int thread_suspend(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return OSTaskSuspend(info->task[id].id);
#else                 /*Linux system*/
	return -1;
#endif
}
// ��������
int thread_resume(THREAD_INFO *info, U8 id) {
#if defined(OS_UCOS)  /*uCOS System*/
	return OSTaskResume(info->task[id].id);
#else                 /*Linux system*/
	return -1;
#endif
}