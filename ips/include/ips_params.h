/******************************************************************************
 * @file	ips_params.h
 * @brief	
 * @author	rong.li
 * @version	v2.1
 * @date	2017-12-27
 * 
 * @note	
 *  Copyright (C) 2017. All rights reserved.
 * 
 * @par
 *  Change Logs:
 *  Date           Author       Notes
 *  2017-12-27     rong.li      added file to project
 *****************************************************************************/
#ifndef __IPS_PARAMS_H__
#define __IPS_PARAMS_H__

#include "cs_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif // __cplusplus
#endif // __cplusplus

#define DEV_PARAMS_VERSION				3		///< 当前设备参数版本

/**
 * @brief 营养液循环参数结构体定义
 * 
 */
typedef struct tagNCycleTimer {	
	UINT8 enable;								///< 定时器使能标志(1-开启 0-关闭)
	UINT8 on_time_h;							///< 定时器起始时间(小时)
	UINT8 on_time_m;							///< 定时器起始时间(分钟)
	UINT8 off_time_h;							///< 定时器结束时间(小时)
	UINT8 off_time_m;							///< 定时器结束时间(分钟)
	UINT8 week_mask;							///< 定时器一周有效掩码\n
										    	///< (bit0~bit7分别代表\n
												///< 日、一、二、三、四、五、六)\n
										    	///< 1-开启 0-关闭
} NCycleTimer;

#define NCYCLE_TIMER_ENABLE_OFS			0		///< 定时器使能标志位偏移
#define NCYCLE_TIMER_ON_H_OFS			1		///< 定时器开启时间(小时)偏移
#define NCYCLE_TIMER_ON_M_OFS			2		///< 定时器开启时间(分钟)偏移
#define NCYCLE_TIMER_OFF_H_OFS			3		///< 定时器关闭时间(小时)偏移
#define NCYCLE_TIMER_OFF_M_OFS			4		///< 定时器关闭时间(分钟)偏移
#define NCYCLE_TIMER_WEEK_MASK_OFS		5		///< 定时器一周使能掩码偏移
#define NCYCLE_TIMER_LEN				6		///< 定时器数据长度
#define NCYCLE_TIMER_NUM				16		///< 定时器总数

/**
 * @brief 营养液循环定时器结构体定义
 * 
 */
typedef struct tagNCycleParams {	
	NCycleTimer timer[NCYCLE_TIMER_NUM];
} NCycleParams;
	
#define NCYCLE_PARAMS_LEN	\
			(NCYCLE_TIMER_NUM*NCYCLE_TIMER_LEN)	///< 营养液循环参数数据长度

/**
 * @brief 营养液浓度参数结构体定义
 * 
 */
typedef struct tagNConcParams
{
	UINT8  on_time_h;							///< 检查起始时间(小时)
	UINT8  on_time_m;							///< 检查起始时间(分钟)
	UINT8  off_time_h;							///< 检查结束时间(小时)
	UINT8  off_time_m;							///< 检查结束时间(分钟)	
	UINT16 check_time_m;						///< 检查间隔时间(单位：分钟)
	UINT16 max_ec_value;						///< 最大EC值
	UINT16 min_ec_value;						///< 最小EC值
	UINT16 supply_time_s;						///< 补给时间(单位：秒)
} NConcParams;

#define NCONC_PARAMS_LEN				12		///< 营养液浓度参数数据长度

/**
 * @brief 营养液容量参数结构体定义
 * 
 */
typedef struct tagNCYParams
{	
	UINT8  on_time_h;							///< 检查起始时间(小时)
	UINT8  on_time_m;							///< 检查起始时间(分钟)
	UINT8  off_time_h;							///< 检查结束时间(小时)
	UINT8  off_time_m;							///< 检查结束时间(分钟)
	UINT16 check_time_s;						///< 检查间隔时间(单位：秒)
	UINT16 judge_times;							///< 判断次数
#define LOW_LEVEL	0							///< 低电平
#define HIGH_LEVEL	1							///< 高电平
	UINT8	supply_level;						///< 补水电平(0-低电平 1-高电平)
} NCYParams;

#define NCY_PARAMS_LEN                  9		///< 营养液容量参数数据长度

/**
 * @brief 设备全局参数结构体定义
 * 
 */
typedef struct tagDevParams
{	
	UINT8      		nParamsVer;					///< 设备参数版本全局变量
	UINT8			nParamsEditCount;			///< 设备参数修改次数
	NConcParams		mNConcParams;		    	///< 营养液浓度参数全局变量
	NCYParams		mNCYParams;			    	///< 营养液容量参数全局变量
	NCycleParams	mNCycleParams;		   		///< 营养液循环参数全局变量
} DevParams;

/**
 * @brief EEPROM参数存放地址定义
 * 
 */
#define PARAMS_OFFSET        	    	MOVC_ShiftAddress

#define PARAMS_VERSION    		    	0x0000	///< 设备参数版本
#define PARAMS_EDIT_CNT      	    	0x0001 	///< 设备参数修改次数

#define NCONC_ON_TIME_H			    	0x0002	///< 营养液浓度检查开始时间(小时)
#define NCONC_ON_TIME_M			    	0x0003	///< 营养液浓度检查开始时间(分钟)
#define NCONC_OFF_TIME_H		   	 	0x0004	///< 营养液浓度检查结束时间(小时)
#define NCONC_OFF_TIME_M		    	0x0005	///< 营养液浓度检查结束时间(分钟)
#define NCONC_CHECK_TIME_M_H	    	0x0006 	///< 营养液浓度检查间隔时间(单位：分钟)(高位)
#define NCONC_CHECK_TIME_M_L	  		0x0007 	///< 营养液浓度检查间隔时间(单位：分钟)(低位)
#define NCONC_MAX_EC_VALUE_H	    	0x0008 	///< 营养液浓度最大EC值(高位)
#define NCONC_MAX_EC_VALUE_L	    	0x0009 	///< 营养液浓度最大EC值(低位)
#define NCONC_MIN_EC_VALUE_H	    	0x000A 	///< 营养液浓度最小EC值(高位)
#define NCONC_MIN_EC_VALUE_L	    	0x000B 	///< 营养液浓度最小EC值(低位)
#define NCONC_SUPPLY_TIME_S_H	    	0x000C 	///< 营养液浓度补给时间(单位：秒)(高位)
#define NCONC_SUPPLY_TIME_S_L	    	0x000D 	///< 营养液浓度补给时间(单位：秒)(低位)

#define NCY_ON_TIME_H			    	0x000E	///< 营养液容量检查开始时间(小时)
#define NCY_ON_TIME_M			    	0x000F	///< 营养液容量检查开始时间(分钟)
#define NCY_OFF_TIME_H			    	0x0010	///< 营养液容量检查结束时间(小时)
#define NCY_OFF_TIME_M			    	0x0011	///< 营养液容量检查结束时间(分钟)
#define NCY_CHECK_TIME_S_H		    	0x0012 	///< 营养液容量检查间隔时间(单位：秒)(高位)
#define NCY_CHECK_TIME_S_L		    	0x0013 	///< 营养液容量检查间隔时间(单位：秒)(低位)
#define NCY_JUDGE_TIMES_H		    	0x0014 	///< 营养液容量判断次数(高位)
#define NCY_JUDGE_TIMES_L		    	0x0015 	///< 营养液容量判断次数(低位)
#define NCY_SUPPLY_LEVEL		    	0x0016	///< 营养液容量补水电平

#define NCYCLE_PARAMS_START		    	0x0017 	///< 定时器参数起始地址
#define NCYCLE_PARAMS_END	\
			(NCYCLE_PARAMS_START+NCYCLE_PARAMS_LEN-1)	///< 定时器参数结束地址

extern DevParams	g_DevParams; 	    		///< 设备全局变量

/**
 * @brief 从EEPROM中读取参数
 * 
 */
void IPS_ReadDevParams(void);

/**
 * @brief 检查配置参数的合理性
 * 
 * @param void 
 */
void IPS_CheckDevParams(void);

/**
 * @brief 将配置写入Flash
 * 
 * @param void 
 */
void IPS_WriteDevParams(void);

/**
 * @brief 打印设备参数
 * 
 * @param void 
 */
void IPS_PrintDevParams(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif // __cplusplus
#endif // __cplusplus

#endif // __IPS_PARAMS_H__
