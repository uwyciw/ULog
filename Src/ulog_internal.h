/**
  ******************************************************************************
    * @file ulog_internal.h
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

#ifndef _ULOG_INTERNAL_H_
#define _ULOG_INTERNAL_H_

/* Includes ------------------------------------------------------------------*/

/**
 * @brief 将传入的某个变量的值按一字节对齐，编排到默认缓存中，并在前面加上日志头。
 * @note
 * @param 。
 * @retval 最终使用缓存的字节数。
 */
typedef unsigned int (*ULOG_ENCODER_T)(void * pValue);

/**
 * @brief 变量访问接口。
 */
typedef struct {
    char * name;
    ULOG_ENCODER_T encoder;
} ULOG_VARIABLE_T;

/**
 * @brief 所有变量的总入口。
 */
struct ULog_Variable_Enter_T {
    void (*init)(void);      // 用于初始化一些入口变量的值。
    unsigned char * pHeader; // 日志文件的头部地址。
    unsigned int headerSize; // 日志文件头部大小。
    unsigned char * pBuffer; // 缓存空间。
    unsigned int number;     // 变量的数量。
    ULOG_VARIABLE_T * pVariable;
};

/**
 * @brief 时间戳变量，所有的变量类型定义时，时间戳放在结构体的第一元素位置。
 */
typedef struct {
    uint64_t timestamp;
    unsigned char data[];
} ULog_Variable_Timestamp_T;

/**
 * @brief ULog句柄。
 */
struct ULog_Handle_T {
    unsigned int (*start)(struct ULog_Handle_T * pHandle);
    unsigned int (*write)(struct ULog_Handle_T * pHandle, void * pData, int size);
    unsigned int (*stop)(struct ULog_Handle_T * pHandle);
    unsigned int (*timestamp)(struct ULog_Handle_T * pHandle, uint64_t * pTimestamp);
    struct ULog_Variable_Enter_T * enter;
    unsigned int identity;
};

/**
 * @brief 为方便拷贝，使用1字节对齐。
 */
#pragma pack(push, 1)
/**
 * @brief 文件头。
 */
typedef struct {
    unsigned char fileMagic[7];
    unsigned char version;
    uint64_t timestamp;
} ULOG_HEADER_T;

/**
 * @brief 格式类型。
 */
typedef struct {
    unsigned short msgSize;
    unsigned char msgType;
    char * format;
} ULOG_MESSAGE_FORMAT_T;

/**
 * @brief 订阅类型。
 */
typedef struct {
    unsigned short msgSize;
    unsigned char msgType;
    unsigned char multiId;
    unsigned short msgId;
    char * msgName;
} ULOG_MESSAGE_SUBSCRIBE_T;
#pragma pack(pop)

#endif
