/******************************************************************************
 * @file	ips_timer_event.c
 * @brief	
 * @author	rong.li
 * @version	v1.0
 * @date	2017-12-27
 * 
 * @note	
 *  Copyright (C) 2017. All rights reserved.
 * 
 * @par
 *  Change Logs:
 *  Date           Author       Notes
 *  2017-12-27     rong.li      first version
 *****************************************************************************/
#include "assert.h"
#include "api_os.h"
#include "ips_sys.h"

#define IPS_TIMER_INTERVAL_TIME_MS              100                     ///< 定时器间隔时间(ms)

#define IPS_TIMER_MANAGER_TASK_STACK_SIZE       (1024 * 2)              ///< 循环任务线程桟大小
#define IPS_TIMER_MANAGER_TASK_PRIORITY         0                       ///< 循环任务线程优先级 
#define IPS_TIMER_MANAGER_TASK_NAME             "IPS Timer Event Task"  ///< 循环任务线程名称 

HANDLE ipsTimerManagerTaskHandle    = NULL;        ///< 定时器管理线程句柄
HANDLE ipsTimerEventTblMutex        = NULL;        ///< 定时器任务表互斥锁

static idata TimerEvent m_TimerEventTbl[TOTAL_TIMER];


/**
 * @brief 
 * 
 * @param elpasedTicks 消逝的时间(ms)
 */
void timerManagerPoll(UINT32 elpasedTicks)
{

}

/**
 * @brief 定时器管理线程
 * 
 * @param pData 
 */
void ipsTimerManagerTask(VOID *pData)
{
    while (1)
    {
        OS_Sleep(IPS_TIMER_INTERVAL_TIME_MS);
        ipsTimerEventPoll(IPS_TIMER_INTERVAL_TIME_MS);
    }
}

/**
 * @brief 打开定时任务模块
 * 
 * @param void 
 * @return true 
 * @return false 
 */
bool IPS_OpenTimerEventModule(void)
{
    // 创建互斥锁
    ipsTimerEventTblMutex = OS_CreateMutex();
    Assert(ipsTimerEventTblMutex);

    // 创建定时器管理线程
    ipsTimerManagerTaskHandle = OS_CreateTask(
                                    ipsTimerManagerTask,
                                    NULL, NULL, 
                                    IPS_TIMER_MANAGER_TASK_STACK_SIZE, 
                                    IPS_TIMER_MANAGER_TASK_PRIORITY, 
                                    0, 0, 
                                    IPS_TIMER_MANAGER_TASK_NAME);
    Assert(ipsTimerManagerTaskHandle); 
}

void IPS_CloseTimerEventModule(void)
{
    if (ipsTimerManagerTaskHandle) {
        OS_DeleteTask(ipsTimerManagerTaskHandle);
    }
}