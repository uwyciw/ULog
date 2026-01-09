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
typedef unsigned int (*ULog_Encoder_T)(void * p_value);

/**
  * @brief 变量访问接口。
  */
typedef struct 
{
  char * name;
  ULog_Encoder_T encoder;
}ULog_Variable_T;

/**
  * @brief 所有变量的总入口。
  */
struct ulog_variable_enter_t
{
  void (*init)(void);           //用于初始化一些入口变量的值。
  unsigned char * p_header;     //日志文件的头部地址。
  unsigned int header_size;     //日志文件头部大小。
  unsigned char * buffer;       //缓存空间。
  unsigned int number;          //变量的数量。
  ULog_Variable_T * variable;   
};

/**
  * @brief 时间戳变量，所有的变量类型定义时，时间戳放在结构体的第一元素位置。
  */
typedef struct 
{
  unsigned long long timestamp;
  unsigned char data[];
}ULog_Variable_Timestamp_T;

/**
  * @brief ULog句柄。
  */
struct ulog_handle_s
{
  unsigned int (*start)(struct ulog_handle_s * p_handle);
  unsigned int (*write)(struct ulog_handle_s * p_handle, void * p_data, int size);
  unsigned int (*stop)(struct ulog_handle_s * p_handle);
  unsigned int (*timestamp)(struct ulog_handle_s * p_handle, unsigned long long * p_timestamp);
  struct ulog_variable_enter_t * enter;
  unsigned int identity;
};


/**
  * @brief 为方便拷贝，使用1字节对齐。
  */
#pragma pack(push, 1)
/**
  * @brief 文件头。
  */
typedef struct 
{
  unsigned char file_magic[7];
  unsigned char version;
  unsigned long long timestamp;
}ULog_Header_T;

/**
  * @brief 格式类型。
  */
typedef struct  
{
  unsigned short msg_size;
  unsigned char msg_type;
  char * format;
}ULog_Message_Format_T;

/**
  * @brief 订阅类型。
  */
typedef struct 
{
  unsigned short msg_size;
  unsigned char msg_type;
  unsigned char multi_id;
  unsigned short msg_id;
  char * message_name;
}ULog_Message_Subscribe_T;
#pragma pack(pop)

#endif
