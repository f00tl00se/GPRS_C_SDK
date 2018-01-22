/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	onenet.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2017-05-08
	*
	*	版本： 		V1.1
	*
	*	说明： 		与onenet平台的数据交互接口层
	*
	*	修改记录：	V1.0：协议封装、返回判断都在同一个文件，并且不同协议接口不同。
	*				V1.1：提供统一接口供应用层使用，根据不同协议文件来封装协议相关的内容。
	************************************************************
	************************************************************
	************************************************************
**/
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "api_event.h"
#include "api_network.h"
#include "api_socket.h"

#include "demo_onenet.h"
#include "demo_edp.h"
#include "EdpKit.h"


#define DEVID	"24644116"

#define APIKEY	"6=BZV5=bpJu=tpxsOLEbIb=hDSQ="

uint8_t ledStatus = 0;
//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	0-成功	1-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
uint8_t OneNet_EDP_DevLink(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};				//协议包

	uint8_t *dataPtr;
	
	uint8_t status = 1;
	
	Trace(1, "OneNet_DevLink""DEVID: %s, APIKEY: %s", DEVID, APIKEY);

	if(EDP_PacketConnect1(DEVID, APIKEY, 256, &edpPacket) == 0)		//根据devid 和 apikey封装协议包
	{
		Net_SendData(edpPacket._data, edpPacket._len);			    //上传平台
		
		dataPtr = Net_GetIPD(250);								//等待平台响应
		if(dataPtr != NULL)
		{
			if(EDP_UnPacketRecv(dataPtr) == CONNRESP)
			{
				switch(EDP_UnPacketConnectRsp(dataPtr))
				{
					case 0:Trace(1, "Tips:	连接成功");status = 0;break;
					
					case 1:Trace(1, "WARN:	连接失败：协议错误");break;
					case 2:Trace(1, "WARN:	连接失败：设备ID鉴权失败");break;
					case 3:Trace(1, "WARN:	连接失败：服务器失败");break;
					case 4:Trace(1, "WARN:	连接失败：用户ID鉴权失败");break;
					case 5:Trace(1, "WARN:	连接失败：未授权");break;
					case 6:Trace(1, "WARN:	连接失败：授权码无效");break;
					case 7:Trace(1, "WARN:	连接失败：激活码未分配");break;
					case 8:Trace(1, "WARN:	连接失败：该设备已被激活");break;
					case 9:Trace(1, "WARN:	连接失败：重复发送连接请求包");break;
					
					default:Trace(1, "ERR:	连接失败：未知错误");break;
				}
			}
		}
		
		EDP_DeleteBuffer(&edpPacket);								//删包
	}
	else
    {
        Trace(1, "WARN:	EDP_PacketConnect Failed");
    }		
	
	return status;
	
}

unsigned char OneNet_EDP_FillBuf(char *buf)
{
	
	char text[16];
	
	memset(text, 0, sizeof(text));
	
	strcpy(buf, ",;");
	
	memset(text, 0, sizeof(text));
    ledStatus = ledStatus?0:1;
	sprintf(text, "led_status,%d;", ledStatus);
	strcat(buf, text);
	
	return strlen(buf);

}

//==========================================================
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_EDP_SendData(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[128];
	
	uint16_t body_len = 0, i = 0;
	
	Trace(1, "Tips:	OneNet_SendData-EDP");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_EDP_FillBuf(buf);		//获取当前需要发送的数据流的总长度
	Trace(1, "body_len=%d, body:%s", body_len, buf);										
	
	if(body_len)
	{
		if(EDP_PacketSaveData(NULL, body_len, NULL, 5, &edpPacket) == 0)					//封包
		{
			for(i = 0; i < body_len; i++)
				edpPacket._data[edpPacket._len++] = buf[i];
			
			Net_SendData(edpPacket._data, edpPacket._len);										//上传数据到平台
			Trace(1, "Send %d Bytes", edpPacket._len);
			
			EDP_DeleteBuffer(&edpPacket);															//删包
		}
		else
		{
            Trace(1, "WARN:	EDP_NewBuffer Failed");
        }
    }
	
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_EDP_RevPro(unsigned char *cmd)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	//协议包
	
	char *cmdid_devid = NULL;
	unsigned short cmdid_len = 0;
	char *req = NULL;
	unsigned int req_len = 0;
	unsigned char type = 0;
	
	short result = 0;
	int num = 0;
	
	type = EDP_UnPacketRecv(cmd);
	switch(type)										//判断是pushdata还是命令下发
	{
		case CMDREQ:									//解命令包
			
			result = EDP_UnPacketCmd(cmd, &cmdid_devid, &cmdid_len, &req, &req_len);
			
			if(result == 0)								//解包成功，则进行命令回复的组包
			{
				EDP_PacketCmdResp(cmdid_devid, cmdid_len, req, req_len, &edpPacket);
				Trace(1, "cmdid: %s, req: %s, req_len: %d", cmdid_devid, req, req_len);
			}
			
		break;
			
		case SAVEACK:
			
			if(cmd[3] == MSG_ID_HIGH && cmd[4] == MSG_ID_LOW)
			{
				Trace(1, "Tips:	Send %s", cmd[5] ? "Err" : "Ok");
			}
			else
			{
                Trace(1, "Tips:	Message ID Err");
            }	
			
		break;
			
		default:
			result = -1;
		break;
	}
	
	Net_Clear();										//清空缓存
	
	if(result == -1)
		return;
	
	if(req != NULL)									//如果找到了
	{
		if(strstr((char *)req, "led"))				    //搜索"led"
		{
			num = atoi((const char *)(req+3));
			ledStatus = num;
            Trace(1, "Receive led value: %d", ledStatus);
		}	
	}
	
	if(type == CMDREQ && result == 0)						//如果是命令包 且 解包成功
	{
		EDP_FreeBuffer(cmdid_devid);						//释放内存
		EDP_FreeBuffer(req);
															//回复命令
		Net_SendData(edpPacket._data, edpPacket._len);	    //上传平台
		EDP_DeleteBuffer(&edpPacket);						//删包
	}

}

//==========================================================
//	函数名称：	OneNet_HeartBeat
//
//	函数功能：	发送心跳请求
//
//	入口参数：	无
//
//	返回参数：	0-发送成功	1-需要重送
//
//	说明：		
//==========================================================
uint8_t OneNet_EDP_SendData_Heart(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};		//协议包
	
	if(EDP_PacketPing(&edpPacket))
		return 1;
	
	Net_SendData(edpPacket._data, edpPacket._len);	//向平台上传心跳请求
	
	EDP_DeleteBuffer(&edpPacket);							//删包
	
	return 0;
	
}