/******************************************************************************
 * @file	ips_sys.h
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
#ifndef __IPS_SYSTEM_H__
#define __IPS_SYSTEM_H__

#include "cs_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif // __cplusplus
#endif // __cplusplus

#define IPS_TRACE_INDEX_MAIN            1
#define IPS_TRACE_INDEX_PARAMS          2
#define IPS_TRACE_INDEX_TIMER_EVENT     3

extern bool ipsExitFlag;

#ifdef __cplusplus
#if __cplusplus
}
#endif // __cplusplus
#endif // __cplusplus

#endif // __IPS_SYSTEM_H__
