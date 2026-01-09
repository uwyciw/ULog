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
#include "ulog_internal.h"
#include <stdint.h>
#include <string.h>

/**
 * @brief 错误编码。
 */
typedef enum {
    ULOG_ERROR_NONE = 0u,  // 无错误。
    ULOG_ERROR_PARA = 1u,  // 参数错误。
    ULOG_ERROR_START = 2u, // 启动错误。
    ULOG_ERROR_WRITE = 3u, // 写错误。
    ULOG_ERROR_STOP = 4u,  // 结束错误。
} ULOG_ERROR_T;

/**
 * @brief ULog句柄。
 */
typedef struct ULog_Handle_T ULOG_HANDLE_T;

/**
 * @brief 所有变量的总入口，由matlab脚本自动生成其内容。
 */
typedef struct ULog_Variable_Enter_T ULOG_VARIABLE_ENTER_T;

/**
 * @brief 用户提供的启动函数，在初始化时被调用一次。
 * @note
 * @param p_handle：日志句柄。
 * @retval 操作成功返回ULog_Error_None。
 */
typedef unsigned int (*ULOG_START_T)(ULOG_HANDLE_T * pHandle);

/**
 * @brief 用户提供的写函数，用于向用户空间写入日志数据。
 * @note
 * @param p_handle：日志句柄；p_data：数据首地址；size：数据字节数。
 * @retval 操作成功返回ULog_Error_None。
 */
typedef unsigned int (*ULOG_WRITE_T)(ULOG_HANDLE_T * pHandle, void * pData, int size);

/**
 * @brief 用户提供的结束函数，在结束时被调用一次。
 * @note
 * @param p_handle：日志句柄。
 * @retval 操作成功返回ULog_Error_None。
 */
typedef unsigned int (*ULOG_STOP_T)(ULOG_HANDLE_T * pHandle);

/**
 * @brief 用户提供的获得时间戳的函数。
 * @note
 * @param p_handle：日志句柄；p_timestamp：保存时间戳的指针。
 * @retval 操作成功返回ULog_Error_None。
 */
typedef unsigned int (*ULOG_TIMESTAMP_T)(ULOG_HANDLE_T * pHandle, uint64_t * pTimestamp);

/**
 * @brief 初始化函数。
 * @note p_handle与enter只能一对一，不可多对一或多对多。
 * @param
 * p_handle：日志句柄；start：启动函数；write：写函数；stop：结束函数；timestamp：时间戳函数；enter：变量入口；identity：身份信息，用于区别多个句柄。
 * @retval 操作成功返回ULog_Error_None。
 */
unsigned int ULogInit(ULOG_HANDLE_T * pHandle, ULOG_START_T start, ULOG_WRITE_T write,
                      ULOG_STOP_T stop, ULOG_TIMESTAMP_T timestamp, ULOG_VARIABLE_ENTER_T * enter,
                      unsigned int identity);

/**
 * @brief 日志更新函数，以变量名为索引。
 * @note
 * @param p_handle：日志句柄；p_name:变量名；p_value：变量值。
 * @retval 操作成功返回ULog_Error_None。
 */
unsigned int ULogUpdateName(ULOG_HANDLE_T * pHandle, const char * pName, void * pValue);

/**
 * @brief 日志更新函数，以变量ID为索引。
 * @note 变量ID为变量在配置文件中的顺序，从0开始。
 * @param p_handle：日志句柄；id:变量ID；p_value：变量值。
 * @retval 操作成功返回ULog_Error_None。
 */
unsigned int ULogUpdateID(ULOG_HANDLE_T * pHandle, unsigned int id, void * pValue);

/**
 * @brief 结束日志函数。
 * @note
 * @param p_handle：日志句柄。
 * @retval 操作成功返回ULog_Error_None。
 */
unsigned int ULogEnd(ULOG_HANDLE_T * pHandle);

/**
 * @brief 获得句柄身份信息函数。
 * @note
 * @param p_handle：日志句柄。
 * @retval 身份信息。
 */
unsigned int ULogGetIdentity(ULOG_HANDLE_T * pHandle);

#endif
