#include <stdio.h>
#include "ulog.h"
#include "Topic.h"
#include "sine_data.h"

ULog_Handle_T ulog;
FILE * file;

unsigned int ULog_Start(ULog_Handle_T * p_handle)
{
    file = fopen("./log.ulg", "w");

    return ULog_Error_None;
}

unsigned int ULog_Write(ULog_Handle_T * p_handle, void * p_data, int size)
{
    fwrite(p_data, size, 1, file);

    return ULog_Error_None;
}

unsigned int ULog_Stop(ULog_Handle_T * p_handle)
{
    fclose(file);

    return ULog_Error_None;
}

unsigned int ULog_Timestamp(ULog_Handle_T * p_handle, unsigned long long * p_timestamp)
{
    static unsigned long long time = 0;

    *p_timestamp = time++;

    return ULog_Error_None;
}

void main()
{
  ULog_Tof_T tof;
  ULog_Imu_T imu;

  ULog_Init(&ulog, ULog_Start, ULog_Write, ULog_Stop, ULog_Timestamp, &ulog_enter_Topic, 1);

  for(int i = 0; i < 1000; i++)
  {
      tof.high = sine_data_1[i%99];
      tof.status = tof.status?0:1;
      imu.counter = imu.counter + 1;
      imu.gyp[0] = sine_data_2[i%99];
      imu.gyp[1] = sine_data_3[i%99];
      imu.gyp[2] = sine_data_4[i%99];
      ULog_Update_Name(&ulog, "Tof", &tof);
      ULog_Update_ID(&ulog, 1, &imu);
  }

  ULog_End(&ulog);
}






