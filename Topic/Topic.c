#include "Topic.h"

__weak static unsigned char default_buffer[];

static unsigned int ULog_Encoder_Tof(void * p_value);
static unsigned int ULog_Encoder_Imu(void * p_value);
static void ULog_Topic_Enter_Init();

ULog_Variable_T ulog_enter_array[] = 
{
  {"Tof", ULog_Encoder_Tof},
  {"Imu", ULog_Encoder_Imu},
};

ULog_Variable_Enter_T ulog_enter_Topic = 
{
  ULog_Topic_Enter_Init, 0, 0, default_buffer, 2, ulog_enter_array
};

static unsigned int ULog_Encoder_Tof(void * p_value)
{
  ULog_Tof_T * pVar = (  ULog_Tof_T *)p_value;
  unsigned char * pData;

  pData = (unsigned char *)&(pVar->timestamp);
  memcpy(&default_buffer[5], pData, 8);

  pData = (unsigned char *)&(pVar->status);
  memcpy(&default_buffer[13], pData, 4);

  pData = (unsigned char *)&(pVar->high);
  memcpy(&default_buffer[17], pData, 4);

  default_buffer[0] = 18;
  default_buffer[1] = 0;
  default_buffer[2] = 0x44;
  default_buffer[3] = 0;
  default_buffer[4] = 0;

  return 21;
}

static unsigned int ULog_Encoder_Imu(void * p_value)
{
  ULog_Imu_T * pVar = (  ULog_Imu_T *)p_value;
  unsigned char * pData;

  pData = (unsigned char *)&(pVar->timestamp);
  memcpy(&default_buffer[5], pData, 8);

  pData = (unsigned char *)(pVar->gyp);
  memcpy(&default_buffer[13], pData, 24);

  pData = (unsigned char *)&(pVar->counter);
  memcpy(&default_buffer[37], pData, 8);

  default_buffer[0] = 42;
  default_buffer[1] = 0;
  default_buffer[2] = 0x44;
  default_buffer[3] = 1;
  default_buffer[4] = 0;

  return 45;
}

static unsigned char default_buffer[45] = {0};

static void ULog_Topic_Enter_Init()
{
  ULog_Message_Format_T format[] = 
  {
    {51, 0x46, "Tof:uint64_t timestamp;uint32_t status;float high;"},
    {55, 0x46, "Imu:uint64_t timestamp;double[3] gyp;uint64_t counter;"},
  };

  ULog_Message_Subscribe_T subscribe[] = 
  {
    {7, 0x41, 0, 0, "Tof"},
    {7, 0x41, 0, 1, "Imu"},
  };

  static unsigned char ulog_header_buffer[132] = {0};
  int counter = 0;

  for(int i = 0; i < 2; i++)
  {
    memcpy(&ulog_header_buffer[counter], &format[i], 3);
    counter = counter + 3;
    memcpy(&ulog_header_buffer[counter], format[i].format, format[i].msg_size);
    counter = counter + format[i].msg_size;
  }

  for(int i = 0; i < 2; i++)
  {
    memcpy(&ulog_header_buffer[counter], &subscribe[i], 6);
    counter = counter + 6;
    memcpy(&ulog_header_buffer[counter], subscribe[i].message_name, subscribe[i].msg_size-3);
    counter = counter + subscribe[i].msg_size - 3;
  }

  ulog_enter_Topic.p_header = ulog_header_buffer;
  ulog_enter_Topic.header_size = 132;
}
