#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#define _CRT_SECURE_NO_WARNINGS	

#include <stdio.h>
#include <assert.h>
		
/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO          5

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE    128

#define OS_TASK_TMR_PRIO			65533
//#define OS_TASK_TMR_PRIO			255
#define OS_IDLE_PRIO				OS_TASK_IDLE_PRIO
#define OS_STAT_PRIO				OS_TASK_STAT_PRIO

#include <includes.h>
#endif