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
typedef struct ulog_handle_t ULOG_HANDLE_T;

/**
 * @brief 所有变量的总入口，由matlab脚本自动生成其内容。
 */
typedef struct ulog_variable_enter_t ULOG_VARIABLE_ENTER_T;

/**
 * @brief 用户提供的启动函数，在初始化时被调用一次。
 * @note
 * @param pHandle：日志句柄。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
typedef unsigned int (*ULOG_START_T)(ULOG_HANDLE_T * pHandle);

/**
 * @brief 用户提供的写函数，用于向用户空间写入日志数据。
 * @note
 * @param pHandle：日志句柄；pData：数据首地址；size：数据字节数。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
typedef unsigned int (*ULOG_WRITE_T)(ULOG_HANDLE_T * pHandle, void * pData, int size);

/**
 * @brief 用户提供的结束函数，在结束时被调用一次。
 * @note
 * @param pHandle：日志句柄。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
typedef unsigned int (*ULOG_STOP_T)(ULOG_HANDLE_T * pHandle);

/**
 * @brief 用户提供的获得时间戳的函数。
 * @note
 * @param pHandle：日志句柄；pTimestamp：保存时间戳的指针。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
typedef unsigned int (*ULOG_TIMESTAMP_T)(ULOG_HANDLE_T * pHandle, uint64_t * pTimestamp);

/**
 * @brief 初始化函数。
 * @note pHandle与enter只能一对一，不可多对一或多对多。
 * @param
 * pHandle：日志句柄；start：启动函数；write：写函数；stop：结束函数；timestamp：时间戳函数；enter：变量入口；identity：身份信息，用于区别多个句柄。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
unsigned int ULogInit(ULOG_HANDLE_T * pHandle, ULOG_START_T start, ULOG_WRITE_T write,
                      ULOG_STOP_T stop, ULOG_TIMESTAMP_T timestamp, ULOG_VARIABLE_ENTER_T * enter,
                      unsigned int identity);

/**
 * @brief 日志更新函数，以变量ID为索引。
 * @note 变量ID是变量在ULOG_VARIABLE_T类型的变量数组中的索引。
 * @param pHandle：日志句柄；id:变量ID；pValue：变量值。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
unsigned int ULogUpdateID(ULOG_HANDLE_T * pHandle, unsigned int id, void * pValue);

/**
 * @brief 日志更新函数，以变量名为索引。
 * @note 以变量名为索引会涉及多次字符串比对，对运行效率会有影响。
 * @param pHandle：日志句柄；name:变量名；pValue：变量值。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
unsigned int ULogUpdateName(ULOG_HANDLE_T * pHandle, const char * name, void * pValue);

/**
 * @brief 结束日志函数。
 * @note
 * @param pHandle：日志句柄。
 * @retval 操作成功返回ULOG_ERROR_NONE。
 */
unsigned int ULogEnd(ULOG_HANDLE_T * pHandle);

/**
 * @brief 查询句柄身份信息。
 * @note
 * @param pHandle：日志句柄。
 * @retval 身份信息。
 */
unsigned int ULogQueryIdentity(ULOG_HANDLE_T * pHandle);

/**
 * @brief 通过变量名查询变量ID。
 * @note
 * @param pHandle：日志句柄；name:变量名。
 * @retval 变量ID，若变量名不存在，则返回无效值。
 */
unsigned int ULogQueryID(ULOG_HANDLE_T * pHandle, const char * name);

/**
 * @brief 通过变量ID查询变量名。
 * @note
 * @param pHandle：日志句柄；id:变量ID。
 * @retval 变量名，若变量ID不存在，则返回NULL。
 */
const char * ULogQueryName(ULOG_HANDLE_T * pHandle, unsigned int id);

#endif
