/**  
  ******************************************************************************
    * @file ulog.c
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

/* Includes ------------------------------------------------------------------*/
#include "ulog.h"

/**
  * @brief 日志文件头。
  */
static ULog_Header_T ulog_header = {0x55, 0x4c, 0x6f, 0x67, 0x01, 0x12, 0x35, 0x00, 0};

unsigned int ULog_Init(ULog_Handle_T * p_handle, ULog_Start_T start, ULog_Write_T write, ULog_Stop_T stop, ULog_Timestamp_T timestamp, ULog_Variable_Enter_T * enter, unsigned int identity)
{
  unsigned long long timestampTemp;
  unsigned int err = ULog_Error_None;

  p_handle->enter = enter;
  p_handle->identity = identity;
  p_handle->start = start;
  p_handle->stop = stop;
  p_handle->timestamp = timestamp;
  p_handle->write = write;

  p_handle->enter->init();

  err = p_handle->start(p_handle);

  err = p_handle->timestamp(p_handle, &timestampTemp);
  ulog_header.timestamp = timestampTemp;

  err = p_handle->write(p_handle, &ulog_header, sizeof(ulog_header));

  err = p_handle->write(p_handle, p_handle->enter->p_header, p_handle->enter->header_size);

  return err;
}

unsigned int ULog_Update_Name(ULog_Handle_T * p_handle, const char * p_name, void * p_value)
{
  ULog_Variable_Timestamp_T * pTimestamp = (ULog_Variable_Timestamp_T *)p_value;
  unsigned int err = ULog_Error_None;

  err = p_handle->timestamp(p_handle, &(pTimestamp->timestamp));

  for(int i = 0; i < p_handle->enter->number; i++)
  {
    if(strcmp(p_name, p_handle->enter->variable[i].name) == 0)
    {
      int size;

      size = p_handle->enter->variable[i].encoder(p_value);
      err = p_handle->write(p_handle, p_handle->enter->buffer, size);

      break;
    }
  }

  return err;
}

unsigned int ULog_Update_ID(ULog_Handle_T * p_handle, unsigned int id, void * p_value)
{
  ULog_Variable_Timestamp_T * pTimestamp = (ULog_Variable_Timestamp_T *)p_value;
  unsigned int err = ULog_Error_None;

  err = p_handle->timestamp(p_handle, &(pTimestamp->timestamp));

  if(id < p_handle->enter->number)
  {
    int size;

    size = p_handle->enter->variable[id].encoder(p_value);
    err = p_handle->write(p_handle, p_handle->enter->buffer, size);
  }
  else
  {
    err = ULog_Error_Para;
  }
  
  return err;
}

unsigned int ULog_End(ULog_Handle_T * p_handle)
{
  unsigned int err = ULog_Error_None;

  err = p_handle->stop(p_handle);

  return err;
}

unsigned int ULog_GetIdentity(ULog_Handle_T * p_handle)
{
  return p_handle->identity;
}
