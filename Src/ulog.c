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
static ULOG_HEADER_T ulog_header = {0x55, 0x4c, 0x6f, 0x67, 0x01, 0x12, 0x35, 0x00, 0};

unsigned int ULogInit(ULOG_HANDLE_T * pHandle, ULOG_START_T start, ULOG_WRITE_T write,
                      ULOG_STOP_T stop, ULOG_TIMESTAMP_T timestamp, ULOG_VARIABLE_ENTER_T * enter,
                      unsigned int identity)
{
    uint64_t timestampTemp;
    unsigned int err = ULOG_ERROR_NONE;

    pHandle->enter = enter;
    pHandle->identity = identity;
    pHandle->start = start;
    pHandle->stop = stop;
    pHandle->timestamp = timestamp;
    pHandle->write = write;

    pHandle->enter->init();

    err = pHandle->start(pHandle);

    err = pHandle->timestamp(pHandle, &timestampTemp);
    ulog_header.timestamp = timestampTemp;

    err = pHandle->write(pHandle, &ulog_header, sizeof(ulog_header));

    err = pHandle->write(pHandle, pHandle->enter->pHeader, pHandle->enter->headerSize);

    return err;
}

unsigned int ULogUpdateName(ULOG_HANDLE_T * pHandle, const char * name, void * pValue)
{
    ULOG_VARIABLE_TIMESTAMP_T * pTimestamp = (ULOG_VARIABLE_TIMESTAMP_T *)pValue;
    unsigned int err = ULOG_ERROR_NONE;

    err = pHandle->timestamp(pHandle, &(pTimestamp->timestamp));

    for (int i = 0; i < pHandle->enter->number; i++) {
        if (strcmp(name, pHandle->enter->pVariable[i].name) == 0) {
            int size;

            size = pHandle->enter->pVariable[i].encoder(pValue);
            err = pHandle->write(pHandle, pHandle->enter->pBuffer, size);

            break;
        }
    }

    return err;
}

unsigned int ULogUpdateID(ULOG_HANDLE_T * pHandle, unsigned int id, void * pValue)
{
    ULOG_VARIABLE_TIMESTAMP_T * pTimestamp = (ULOG_VARIABLE_TIMESTAMP_T *)pValue;
    unsigned int err = ULOG_ERROR_NONE;

    err = pHandle->timestamp(pHandle, &(pTimestamp->timestamp));

    if (id < pHandle->enter->number) {
        int size;

        size = pHandle->enter->pVariable[id].encoder(pValue);
        err = pHandle->write(pHandle, pHandle->enter->pBuffer, size);
    } else {
        err = ULOG_ERROR_PARA;
    }

    return err;
}

unsigned int ULogEnd(ULOG_HANDLE_T * pHandle)
{
    unsigned int err = ULOG_ERROR_NONE;

    err = pHandle->stop(pHandle);

    return err;
}

unsigned int ULogQueryIdentity(ULOG_HANDLE_T * pHandle) { return pHandle->identity; }

unsigned int ULogQueryID(ULOG_HANDLE_T * pHandle, const char * name)
{
    unsigned int i;

    for (i = 0; i < pHandle->enter->number; i++) {
        if (strcmp(name, pHandle->enter->pVariable[i].name) == 0) {
            return i;
        }
    }

    return i;
}

const char * ULogQueryName(ULOG_HANDLE_T * pHandle, unsigned int id)
{
    if (id < pHandle->enter->number) {
        return pHandle->enter->pVariable[id].name;
    } else {
        return NULL;
    }
}
