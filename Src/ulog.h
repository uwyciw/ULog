/**  
  ******************************************************************************
    * @file ulog.h
    * @author lx
    * @version v1.0.0
    * @date 2019-04-24
    * @brief 符合PX4的ULog标准的日志保存模块。
   =============================================================================
                       #####  #####
   =============================================================================

    
  ******************************************************************************
    * @attention
    *
    *
    
  ******************************************************************************
   */ 

#ifndef _ULOG_H_
#define _ULOG_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
#include "ulog_internal.h"

/**
  * @brief 错误编码。
  */
typedef enum
{
  ULog_Error_None   =         0u,     //无错误。
  ULog_Error_Para   =         1u,     //参数错误。
  ULog_Error_Start  =         2u,     //启动错误。
  ULog_Error_Write  =         3u,     //写错误。
  ULog_Error_Stop   =         4u,     //结束错误。
  ULog_Error_Time   =         5u,     //时间戳错误。
}ULog_Error_T;

/**
  * @brief ULog句柄。
  */
typedef struct ulog_handle_s ULog_Handle_T;

/**
  * @brief 所有变量的总入口，由matlab脚本自动生成其内容。
  */
typedef struct ulog_variable_enter_t ULog_Variable_Enter_T;

/**
  * @brief 用户提供的启动函数，在初始化时被调用一次。
  * @note 
  * @param p_handle：日志句柄。
  * @retval 操作成功返回ULog_Error_None。
  */
typedef unsigned int (*ULog_Start_T)(ULog_Handle_T * p_handle);

/**
  * @brief 用户提供的写函数，用于向用户空间写入日志数据。
  * @note 
  * @param p_handle：日志句柄；p_data：数据首地址；size：数据字节数。
  * @retval 操作成功返回ULog_Error_None。
  */
typedef unsigned int (*ULog_Write_T)(ULog_Handle_T * p_handle, void * p_data, int size);

/**
  * @brief 用户提供的结束函数，在结束时被调用一次。
  * @note 
  * @param p_handle：日志句柄。
  * @retval 操作成功返回ULog_Error_None。
  */
typedef unsigned int (*ULog_Stop_T)(ULog_Handle_T * p_handle);

/**
  * @brief 用户提供的获得时间戳的函数。
  * @note 
  * @param p_handle：日志句柄；p_timestamp：保存时间戳的指针。
  * @retval 操作成功返回ULog_Error_None。
  */
typedef unsigned int (*ULog_Timestamp_T)(ULog_Handle_T * p_handle, unsigned long long * p_timestamp);

/**
  * @brief 初始化函数。
  * @note p_handle与enter只能一对一，不可多对一或多对多。
  * @param p_handle：日志句柄；start：启动函数；write：写函数；stop：结束函数；timestamp：时间戳函数；enter：变量入口；identity：身份信息，用于区别多个句柄。
  * @retval 操作成功返回ULog_Error_None。
  */
unsigned int ULog_Init(ULog_Handle_T * p_handle, ULog_Start_T start, ULog_Write_T write, ULog_Stop_T stop, ULog_Timestamp_T timestamp, ULog_Variable_Enter_T * enter, unsigned int identity); 

/**
  * @brief 日志更新函数，以变量名为索引。
  * @note 
  * @param p_handle：日志句柄；p_name:变量名；p_value：变量值。
  * @retval 操作成功返回ULog_Error_None。
  */
unsigned int ULog_Update_Name(ULog_Handle_T * p_handle, const char * p_name, void * p_value);

/**
  * @brief 日志更新函数，以变量ID为索引。
  * @note 变量ID为变量在配置文件中的顺序，从0开始。
  * @param p_handle：日志句柄；id:变量ID；p_value：变量值。
  * @retval 操作成功返回ULog_Error_None。
  */
unsigned int ULog_Update_ID(ULog_Handle_T * p_handle, unsigned int id, void * p_value);

/**
  * @brief 结束日志函数。
  * @note 
  * @param p_handle：日志句柄。
  * @retval 操作成功返回ULog_Error_None。
  */
unsigned int ULog_End(ULog_Handle_T * p_handle);

/**
  * @brief 获得句柄身份信息函数。
  * @note 
  * @param p_handle：日志句柄。
  * @retval 身份信息。
  */
unsigned int ULog_GetIdentity(ULog_Handle_T * p_handle);

#endif
