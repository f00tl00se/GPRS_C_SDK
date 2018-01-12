/******************************************************************************
 * @file	ips_params.c
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
#include "api_debug.h"
#include "ips_params.h"
#include "ips_sys.h"

#define GETHU16(c)         ((((c) >> 8) & 0xff))
#define GETLU16(c)         (((c) & 0xff))
#define MAKEU16(c1,c2)     ((((((u8)((u8)(c1) & 0xff)) << 8)) | ((u8)((u8)(c2) & 0xff))))

DevParams g_DevParams;

/**
 * @brief 从EEPROM中读取参数
 * 
 * @param void 
 */
void IPS_ReadDevParams(void)
{
	// char xdata read_buf[128];
	// u8 i = 0;
	
	// EEPROM_read_n(PARAMS_OFFSET, read_buf, 128);
	
	// g_DevParams.nParamsVer             		= read_buf[PARAMS_VERSION];
	// g_DevParams.nParamsEditCount            = read_buf[PARAMS_EDIT_CNT];

	// g_DevParams.mNConcParams.on_time_h		= read_buf[NCONC_ON_TIME_H];
	// g_DevParams.mNConcParams.on_time_m		= read_buf[NCONC_ON_TIME_M];
	// g_DevParams.mNConcParams.off_time_h		= read_buf[NCONC_OFF_TIME_H];
	// g_DevParams.mNConcParams.off_time_m		= read_buf[NCONC_OFF_TIME_M];	
	// g_DevParams.mNConcParams.check_time_m	= MAKEU16(read_buf[NCONC_CHECK_TIME_M_H], read_buf[NCONC_CHECK_TIME_M_L]);
	// g_DevParams.mNConcParams.max_ec_value	= MAKEU16(read_buf[NCONC_MAX_EC_VALUE_H], read_buf[NCONC_MAX_EC_VALUE_L]);
	// g_DevParams.mNConcParams.min_ec_value	= MAKEU16(read_buf[NCONC_MIN_EC_VALUE_H], read_buf[NCONC_MIN_EC_VALUE_L]);
	// g_DevParams.mNConcParams.supply_time_s	= MAKEU16(read_buf[NCONC_SUPPLY_TIME_S_H], read_buf[NCONC_SUPPLY_TIME_S_L]);

	// g_DevParams.mNCYParams.on_time_h		= read_buf[NCY_ON_TIME_H];
	// g_DevParams.mNCYParams.on_time_m		= read_buf[NCY_ON_TIME_M];
	// g_DevParams.mNCYParams.off_time_h		= read_buf[NCY_OFF_TIME_H];
	// g_DevParams.mNCYParams.off_time_m		= read_buf[NCY_OFF_TIME_M];
	// g_DevParams.mNCYParams.check_time_s		= MAKEU16(read_buf[NCY_CHECK_TIME_S_H], read_buf[NCY_CHECK_TIME_S_L]);
	// g_DevParams.mNCYParams.judge_times		= MAKEU16(read_buf[NCY_JUDGE_TIMES_H], read_buf[NCY_JUDGE_TIMES_L]);
	// g_DevParams.mNCYParams.supply_level		= read_buf[NCY_SUPPLY_LEVEL];
	
	// for (i = 0; i < NCYCLE_TIMER_NUM; i++)
	// {
	// 	g_DevParams.mNCycleParams.timer[i].enable 		= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ENABLE_OFS];
	// 	g_DevParams.mNCycleParams.timer[i].on_time_h	= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ON_H_OFS];
	// 	g_DevParams.mNCycleParams.timer[i].on_time_m	= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ON_M_OFS];
	// 	g_DevParams.mNCycleParams.timer[i].off_time_h	= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_OFF_H_OFS];
	// 	g_DevParams.mNCycleParams.timer[i].off_time_m	= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_OFF_M_OFS];
	// 	g_DevParams.mNCycleParams.timer[i].week_mask	= read_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_WEEK_MASK_OFS];
	// }

}

/**
 * @brief 将配置写入Flash
 * 
 * @param void 
 */
void IPS_WriteDevParams(void)
{
	// char xdata write_buf[128] = {0xff,};
	// u8 i = 0;
	
	// g_DevParams.nParamsVer = DEV_PARAMS_VERSION;
	// g_DevParams.nParamsEditCount++;
	// if (g_DevParams.nParamsEditCount == 0xFF) g_DevParams.nParamsEditCount = 0;
	
	// write_buf[PARAMS_VERSION]			= g_DevParams.nParamsVer;
	// write_buf[PARAMS_EDIT_CNT]			= g_DevParams.nParamsEditCount;
	
	// write_buf[NCONC_ON_TIME_H]			= g_DevParams.mNConcParams.on_time_h;
	// write_buf[NCONC_ON_TIME_M]			= g_DevParams.mNConcParams.on_time_m;
	// write_buf[NCONC_OFF_TIME_H]			= g_DevParams.mNConcParams.off_time_h;
	// write_buf[NCONC_OFF_TIME_M]			= g_DevParams.mNConcParams.off_time_m;	
	// write_buf[NCONC_CHECK_TIME_M_H]		= GETHU16(g_DevParams.mNConcParams.check_time_m);
	// write_buf[NCONC_CHECK_TIME_M_L]		= GETLU16(g_DevParams.mNConcParams.check_time_m);
	// write_buf[NCONC_MAX_EC_VALUE_H]		= GETHU16(g_DevParams.mNConcParams.max_ec_value);
	// write_buf[NCONC_MAX_EC_VALUE_L]		= GETLU16(g_DevParams.mNConcParams.max_ec_value);
	// write_buf[NCONC_MIN_EC_VALUE_H]		= GETHU16(g_DevParams.mNConcParams.min_ec_value);
	// write_buf[NCONC_MIN_EC_VALUE_L]		= GETLU16(g_DevParams.mNConcParams.min_ec_value);
	// write_buf[NCONC_SUPPLY_TIME_S_H]	= GETHU16(g_DevParams.mNConcParams.supply_time_s);
	// write_buf[NCONC_SUPPLY_TIME_S_L]	= GETLU16(g_DevParams.mNConcParams.supply_time_s);

	// write_buf[NCY_ON_TIME_H]			= g_DevParams.mNCYParams.on_time_h;
	// write_buf[NCY_ON_TIME_M]			= g_DevParams.mNCYParams.on_time_m;
	// write_buf[NCY_OFF_TIME_H]			= g_DevParams.mNCYParams.off_time_h;
	// write_buf[NCY_OFF_TIME_M]			= g_DevParams.mNCYParams.off_time_m;	
	// write_buf[NCY_CHECK_TIME_S_H]		= GETHU16(g_DevParams.mNCYParams.check_time_s);
	// write_buf[NCY_CHECK_TIME_S_L]		= GETLU16(g_DevParams.mNCYParams.check_time_s);
	// write_buf[NCY_JUDGE_TIMES_H]		= GETHU16(g_DevParams.mNCYParams.judge_times);
	// write_buf[NCY_JUDGE_TIMES_L]		= GETLU16(g_DevParams.mNCYParams.judge_times);
	// write_buf[NCY_SUPPLY_LEVEL]			= g_DevParams.mNCYParams.supply_level;

	// for (i = 0; i < NCYCLE_TIMER_NUM; i++)
	// {
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ENABLE_OFS] 		= g_DevParams.mNCycleParams.timer[i].enable;
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ON_H_OFS] 		= g_DevParams.mNCycleParams.timer[i].on_time_h;
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_ON_M_OFS]			= g_DevParams.mNCycleParams.timer[i].on_time_m;
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_OFF_H_OFS]		= g_DevParams.mNCycleParams.timer[i].off_time_h;
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_OFF_M_OFS]		= g_DevParams.mNCycleParams.timer[i].off_time_m;
	// 	write_buf[NCYCLE_PARAMS_START+i*NCYCLE_TIMER_LEN+NCYCLE_TIMER_WEEK_MASK_OFS]	= g_DevParams.mNCycleParams.timer[i].week_mask;
	// }
	
	// EEPROM_SectorErase(PARAMS_OFFSET);
	// EEPROM_write_n(PARAMS_OFFSET, write_buf, 128);
//	g_wdt_feed = 0;
}

/**
 * @brief 检查配置参数的合理性
 * 
 * @param void 
 */
void IPS_CheckDevParams(void)
{
	int i = 0;
	
	// if (g_DevParams.nParamsEditCount == 0xFF)
	// {
		g_DevParams.nParamsVer = DEV_PARAMS_VERSION;
		g_DevParams.nParamsEditCount = 0;

		g_DevParams.mNConcParams.on_time_h = 0;
		g_DevParams.mNConcParams.on_time_m = 0;
		g_DevParams.mNConcParams.off_time_h = 23;
		g_DevParams.mNConcParams.off_time_m = 59;		
		g_DevParams.mNConcParams.check_time_m = 30;
		g_DevParams.mNConcParams.max_ec_value = 1600;
		g_DevParams.mNConcParams.min_ec_value = 900;
		g_DevParams.mNConcParams.supply_time_s = 60;

		g_DevParams.mNCYParams.on_time_h = 0;
		g_DevParams.mNCYParams.on_time_m = 0;
		g_DevParams.mNCYParams.off_time_h = 0;
		g_DevParams.mNCYParams.off_time_m = 0;
		g_DevParams.mNCYParams.check_time_s = 10;
		g_DevParams.mNCYParams.judge_times = 6;
		g_DevParams.mNCYParams.supply_level = LOW_LEVEL;
		
		memset(&g_DevParams.mNCycleParams, 0, NCYCLE_PARAMS_LEN);
		for (i = 0; i < NCYCLE_TIMER_NUM; i++) {
			g_DevParams.mNCycleParams.timer[i].week_mask = 0x7F;
		}
		
		// date_time[RTC_YEAR] = 17;
		// date_time[RTC_MONTH] = 1;
		// date_time[RTC_DAY] = 1;
		// date_time[RTC_HOUR] = 1;
		// date_time[RTC_MINUTE] = 0;
		// date_time[RTC_SECOND] = 0;
		// date_time[RTC_WEEK] = 1;
		// Write_RTC(&date_time);
		
		// WriteParams();
	// }
}

/**
 * @brief 打印设备参数
 * 
 * @param void 
 */
void IPS_PrintDevParams(void)
{
	Trace(IPS_TRACE_INDEX_PARAMS, "============== DevParams ==============\n");
	Trace(IPS_TRACE_INDEX_PARAMS, "nParamsVer=%d\n", g_DevParams.nParamsVer);
	Trace(IPS_TRACE_INDEX_PARAMS, "nParamsEditCount=%d\n", 
		g_DevParams.nParamsEditCount);
	Trace(IPS_TRACE_INDEX_PARAMS, "NCycleParams:\n");
	for (i = 0; i < NCYCLE_TIMER_NUM; i++)
	{
		Trace(IPS_TRACE_INDEX_PARAMS, " [%d] enable=%d\n", 
			i, g_DevParams.mNCycleParams.timer[i].enable);
		Trace(IPS_TRACE_INDEX_PARAMS, " [%d] on_time=%02d:%02d\n", 
			i, 
			g_DevParams.mNCycleParams.timer[i].on_time_h, 
			g_DevParams.mNCycleParams.timer[i].on_time_m);
		Trace(IPS_TRACE_INDEX_PARAMS, " [%d] off_time=%02d:%02d\n", 
			i, 
			g_DevParams.mNCycleParams.timer[i].off_time_h, 
			g_DevParams.mNCycleParams.timer[i].off_time_m);
		Trace(IPS_TRACE_INDEX_PARAMS, " [%d] week_mask=0x%x\n", 
			i, g_DevParams.mNCycleParams.timer[i].week_mask);
	}
	Trace(IPS_TRACE_INDEX_PARAMS, "NConcParams:\n");
	Trace(IPS_TRACE_INDEX_PARAMS, " on_time=%02d:%02d\n", 
		g_DevParams.mNConcParams.on_time_h,
		g_DevParams.mNConcParams.on_time_m);
	Trace(IPS_TRACE_INDEX_PARAMS, " off_time=%02d:%02d\n", 
		g_DevParams.mNConcParams.off_time_h,
		g_DevParams.mNConcParams.off_time_m);
	Trace(IPS_TRACE_INDEX_PARAMS, " check_time_m=%d\n",
		g_DevParams.mNConcParams.check_time_m);
	Trace(IPS_TRACE_INDEX_PARAMS, " max_ec_value=%d\n",
		g_DevParams.mNConcParams.max_ec_value);
	Trace(IPS_TRACE_INDEX_PARAMS, " min_ec_value=%d\n", 
		g_DevParams.mNConcParams.min_ec_value);
	Trace(IPS_TRACE_INDEX_PARAMS, " supply_time_s=%d\n", 
		g_DevParams.mNConcParams.supply_time_s);
	
	Trace(IPS_TRACE_INDEX_PARAMS, "NCYParams:\n");
	Trace(IPS_TRACE_INDEX_PARAMS, " on_time=%02d:%02d\n", 
		g_DevParams.mNCYParams.on_time_h,
		g_DevParams.mNCYParams.on_time_m);
	Trace(IPS_TRACE_INDEX_PARAMS, " off_time=%02d:%02d\n", 
		g_DevParams.mNCYParams.off_time_h,
		g_DevParams.mNCYParams.off_time_m);
	Trace(IPS_TRACE_INDEX_PARAMS, " check_time_s=%d\n", 
		g_DevParams.mNCYParams.check_time_s);
	Trace(IPS_TRACE_INDEX_PARAMS, " judge_times=%d\n", 
		g_DevParams.mNCYParams.judge_times);
	Trace(IPS_TRACE_INDEX_PARAMS, " supply_level=%d\n", 
		g_DevParams.mNCYParams.supply_level);
	Trace(IPS_TRACE_INDEX_PARAMS, "=======================================\n");
}
