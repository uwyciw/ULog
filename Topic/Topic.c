#include "Topic.h"

__weak static unsigned char default_buffer[];

static unsigned int ULog_Encoder_Tof(void * pValue);
static unsigned int ULog_Encoder_Imu(void * pValue);
static void ULog_Topic_Enter_Init();

ULOG_VARIABLE_T ulog_enter_array[] = 
{
  {"Tof", ULog_Encoder_Tof},
  {"Imu", ULog_Encoder_Imu},
};

ULOG_VARIABLE_ENTER_T ulog_enter_Topic = 
{
  ULog_Topic_Enter_Init, 0, 0, default_buffer, 2, ulog_enter_array
};

static unsigned int ULog_Encoder_Tof(void * pValue)
{
  ULog_Tof_T * pVar = (  ULog_Tof_T *)pValue;
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

static unsigned int ULog_Encoder_Imu(void * pValue)
{
  ULog_Imu_T * pVar = (  ULog_Imu_T *)pValue;
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
  ULOG_MESSAGE_FORMAT_T format[] = 
  {
    {51, 0x46, "Tof:uint64_t timestamp;uint32_t status;float high;"},
    {55, 0x46, "Imu:uint64_t timestamp;double[3] gyp;uint64_t counter;"},
  };

  ULOG_MESSAGE_SUBSCRIBE_T subscribe[] = 
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
    memcpy(&ulog_header_buffer[counter], format[i].format, format[i].msgSize);
    counter = counter + format[i].msgSize;
  }

  for(int i = 0; i < 2; i++)
  {
    memcpy(&ulog_header_buffer[counter], &subscribe[i], 6);
    counter = counter + 6;
    memcpy(&ulog_header_buffer[counter], subscribe[i].msgName, subscribe[i].msgSize-3);
    counter = counter + subscribe[i].msgSize - 3;
  }

  ulog_enter_Topic.pHeader = ulog_header_buffer;
  ulog_enter_Topic.headerSize = 132;
}
