
#include <string.h>
#include <stdio.h>
#include <api_os.h>
#include <api_event.h>
#include <api_socket.h>
#include <api_network.h>
#include <api_debug.h>

#include "demo_edp.h"

/*******************************************************************/
/////////////////////////socket configuration////////////////////////

#define DNS_DOMAIN  "jjfaedp.hedevice.com"
#define SERVER_PORT 876
#define RECEIVE_BUFFER_MAX_LENGTH 1024
/*******************************************************************/


#define MAIN_TASK_STACK_SIZE    (2048 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "OneNET Test Main Task"

#define TEST_TASK_STACK_SIZE    (2048 * 2)
#define TEST_TASK_PRIORITY      1
#define TEST_TASK_NAME          "EDP Test Task"

static HANDLE onenetTaskHandle = NULL;

int socketFd = -1;

/// 接收缓冲区
uint8_t     buffer[RECEIVE_BUFFER_MAX_LENGTH];
uint16_t    recv_cnt = 0;
HANDLE      buffer_mutex = NULL;

HANDLE sem = NULL;
int errorCode = 0;

void Net_Clear(void);

/**
 * @brief 事件分发
 * 
 * @param pEvent 
 */
void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case API_EVENT_ID_NO_SIMCARD:
            Trace(10,"!!NO SIM CARD%d!!!!",pEvent->param1);
            break;

        case API_EVENT_ID_NETWORK_REGISTERED_HOME:
        case API_EVENT_ID_NETWORK_REGISTERED_ROAMING:
            Trace(2,"network register success");
            Network_StartAttach();
            break;

        case API_EVENT_ID_NETWORK_ATTACHED:
            Trace(2,"network attach success");
            Network_PDP_Context_t context = {
                .apn        ="cmnet",
                .userName   = ""    ,
                .userPasswd = ""
            };
            Network_StartActive(context);
            break;

        case API_EVENT_ID_NETWORK_ACTIVATED:
            Trace(2,"network activate success");
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;

        case API_EVENT_ID_SOCKET_CONNECTED:
            Trace(2,"event connect");
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;

        case API_EVENT_ID_SOCKET_SENT:
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;
        case API_EVENT_ID_SOCKET_RECEIVED:
        {
            int fd = pEvent->param1;
            int length = pEvent->param2>RECEIVE_BUFFER_MAX_LENGTH?RECEIVE_BUFFER_MAX_LENGTH:pEvent->param2;
            Net_Clear();
            OS_LockMutex(buffer_mutex);
            recv_cnt = Socket_TcpipRead(fd,buffer,length);
            OS_UnlockMutex(buffer_mutex);
            Trace(2,"socket %d received %d bytes data:%s",fd,length,buffer);
            break;
        }
        case API_EVENT_ID_SOCKET_CLOSED:
        {
            int fd = pEvent->param1;
            Trace(2,"socket %d closed",fd);
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;
        }
        case API_EVENT_ID_SOCKET_ERROR:
        {
            int fd = pEvent->param1;
            Trace(2,"socket %d error occurred,cause:%d",fd,pEvent->param2);
            errorCode = pEvent->param2;
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;
        }
        default:
            break;
    }
}

void CreateSem(HANDLE* sem_)
{
    *sem_ = 0;
    // *sem = OS_CreateSemaphore(0);
}

void WaitSem(HANDLE* sem_)
{
    // OS_WaitForSemaphore(*sem,OS_WAIT_FOREVER);
    // OS_DeleteSemaphore(*sem);
    // *sem = NULL;
    while(*sem_ == 0)
        OS_Sleep(1);
    *sem_ = 0;
}

/**
 * @brief 清空缓冲区
 * 
 * @param void 
 */
void Net_Clear(void)
{
    Trace(2,"clear buffer");
    OS_LockMutex(buffer_mutex);
    memset(buffer, 0, sizeof(buffer));
	recv_cnt = 0;
    OS_UnlockMutex(buffer_mutex);
}

/**
 * @brief 获取平台返回的数据
 * 
 * @param timeOut 等待的时间（单位ms）
 * @return unsigned char* 返回数据的指针
 */
uint8_t *Net_GetIPD(uint16_t timeOut)
{
	do
	{
		if (recv_cnt > 0)
        {
            return buffer;
        }								
		
		OS_Sleep(10);
        if (timeOut >= 10)
        {
            timeOut -= 10;
        }
        else
        {
            timeOut = 0;
        }						
	} while(timeOut>0);
	
	return NULL;
}

bool Net_Connect()
{
    if(DNS_GetHostByName2(DNS_DOMAIN,(char*)buffer) != 0)
        return false;
    Trace(2,"DNS,domain:%s,ip:%s,strlen(ip):%d",DNS_DOMAIN,buffer,strlen(buffer));
    CreateSem(&sem);
    socketFd = Socket_TcpipConnect(TCP,buffer,SERVER_PORT);
    Trace(2,"connect tcp server,socketFd:%d",socketFd);
    WaitSem(&sem);
    Trace(2,"connect end");
    if(errorCode != 0)
    {
        errorCode = 0;
        Trace(2,"error ocurred");
        return false;
    }
    return true;
}

bool Net_SendData(unsigned char *data, unsigned short len)
{
    Trace(2,"Write");
    CreateSem(&sem);
    int ret = Socket_TcpipWrite(socketFd,data,len);
    if(ret <= 0)
    {
        Trace(2,"socket write fail:%d",ret);
        return false;
    }    
    WaitSem(&sem);
    Trace(2,"### write end");
    if(errorCode != 0)
    {
        errorCode = 0;
        Trace(2,"error ocurred");
        return false;
    }
    return true;
}

bool Net_Close()
{
    CreateSem(&sem);
    Socket_TcpipClose(socketFd);
    WaitSem(&sem);
    return true;
}

void edpTestTask(void* param)
{
    uint8_t *dataPtr = NULL;
    int count = 0;
    WaitSem(&sem);
    Trace(2,"start connect now");
    while (!Net_Connect())
    {
        OS_Sleep(1000);
    }
    Trace(2,"connect success");

    Trace(2,"start link now");
    while (OneNet_EDP_DevLink())
    {
        OS_Sleep(1000);
    }
    Trace(2,"link success");
    Net_Clear();
    while(1)
    {
        if (count > 1000)
        {
            OneNet_EDP_SendData_Heart();
            Trace(2,"OneNet_EDP_SendData");
            OneNet_EDP_SendData();
            count = 0;
        }

        dataPtr = Net_GetIPD(0);
		if(dataPtr != NULL)
		{
            OneNet_EDP_RevPro(dataPtr);
        }	

        OS_Sleep(10);
        count++;
    }
}


void onenet_MainTask(void *pData)
{
    API_Event_t* event=NULL;

    CreateSem(&sem);
    buffer_mutex = OS_CreateMutex();
    OS_CreateTask(edpTestTask,
        NULL, NULL, TEST_TASK_STACK_SIZE, TEST_TASK_PRIORITY, 0, 0, TEST_TASK_NAME);
    while(1)
    {
        if(OS_WaitEvent(onenetTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event->pParam2);
            OS_Free(event);
        }
    }
}

void onenet_Main(void)
{
    onenetTaskHandle = OS_CreateTask(onenet_MainTask,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&onenetTaskHandle);
}

