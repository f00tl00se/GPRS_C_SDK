/******************************************************************************
 * @file	ips_main.c
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
#include "stdint.h"
#include "stdbool.h"
#include "api_os.h"
#include "api_event.h"
#include "api_debug.h"
#include "ips_params.h"
#include "ips_sys.h"
       
#define IPS_MAIN_TASK_STACK_SIZE        (1024 * 2)      ///< 主线程桟大小
#define IPS_MAIN_TASK_PRIORITY          0               ///< 主线程优先级 
#define IPS_MAIN_TASK_NAME              "IPS Main Task" ///< 主线程名称   

HANDLE ipsMainTaskHandle    = NULL;

bool ipsExitFlag = false;

void LoopTask(VOID *pData)
{
    uint64_t count = 0;
    while(1)
    {
        ++count;
        if(count == 3000)
        {
            count = 0;
            Trace(1,"Test Test");
            OS_Sleep(1000);
            Trace(1,"Test Test2");
        }
    }
}
void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case API_EVENT_ID_POWER_ON:
            break;
        case API_EVENT_ID_NO_SIMCARD:
            break;
        case API_EVENT_ID_NETWORK_REGISTERED_HOME:
        case API_EVENT_ID_NETWORK_REGISTERED_ROAMING:
            break;
        default:
            break;
    }
}

/**
 * @brief 循环任务线程
 * 
 * @param pData 
 */
void ipsLoopTask(VOID *pData)
{

}

/**
 * @brief ips主线程
 * 
 * @param pData 线程参数
 */
void ipsMainTask(VOID *pData)
{
    API_Event_t* event=NULL;

    // 读取、检查、打印设备参数
    IPS_ReadDevParams();
    IPS_CheckDevParams();
    IPS_PrintDevParams();

    // 创建循环任务线程
    ipsLoopTaskHandle = OS_CreateTask(ipsLoopTask ,
        NULL, NULL, IPS_LOOP_TASK_STACK_SIZE, IPS_LOOP_TASK_PRIORITY, 
        0, 0, IPS_LOOP_TASK_NAME);
        
    while(!ipsExitFlag)
    {
        if(OS_WaitEvent(mainTaskHandle, &event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event);
        }
    }
}

/**
 * @brief ips入口函数
 * 
 * @param void 
 */
void ips_Main(void)
{
    ipsMainTaskHandle = OS_CreateTask(ipsMainTask ,
        NULL, NULL, IPS_MAIN_TASK_STACK_SIZE, IPS_MAIN_TASK_PRIORITY, 
        0, 0, IPS_MAIN_TASK_NAME);
    OS_SetUserMainHandle(&ipsMainTaskHandle);
}