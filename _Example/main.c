#include "Topic.h"
#include "sine_data.h"
#include "ulog.h"
#include <stdio.h>

ULOG_HANDLE_T ulog;
FILE * file;

unsigned int ULog_Start(ULOG_HANDLE_T * pHandle)
{
    file = fopen("./log.ulg", "w");

    return ULOG_ERROR_NONE;
}

unsigned int ULog_Write(ULOG_HANDLE_T * pHandle, void * pData, int size)
{
    fwrite(pData, size, 1, file);

    return ULOG_ERROR_NONE;
}

unsigned int ULog_Stop(ULOG_HANDLE_T * pHandle)
{
    fclose(file);

    return ULOG_ERROR_NONE;
}

unsigned int ULog_Timestamp(ULOG_HANDLE_T * pHandle, uint64_t * pTimestamp)
{
    static uint64_t time = 0;

    *pTimestamp = time++;

    return ULOG_ERROR_NONE;
}

void main()
{
    ULog_Tof_T tof;
    ULog_Imu_T imu;

    ULogInit(&ulog, ULog_Start, ULog_Write, ULog_Stop, ULog_Timestamp, &ulog_enter_Topic, 1);

    for (int i = 0; i < 1000; i++) {
        tof.high = sine_data_1[i % 99];
        tof.status = tof.status ? 0 : 1;
        imu.counter = imu.counter + 1;
        imu.gyp[0] = sine_data_2[i % 99];
        imu.gyp[1] = sine_data_3[i % 99];
        imu.gyp[2] = sine_data_4[i % 99];
        ULogUpdateName(&ulog, "Tof", &tof);
        ULogUpdateID(&ulog, 1, &imu);
    }

    ULogEnd(&ulog);
}
