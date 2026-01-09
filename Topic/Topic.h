#ifndef _Topic_H_
#define _Topic_H_

#include "ulog.h"

extern ULog_Variable_Enter_T ulog_enter_Topic;


typedef struct 
{ 
  uint64_t timestamp; 
  uint32_t status;
  float high;
}ULog_Tof_T; 

typedef struct 
{ 
  uint64_t timestamp; 
  double gyp[3];
  uint64_t counter;
}ULog_Imu_T; 

#endif
