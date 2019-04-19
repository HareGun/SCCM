#ifndef __MONITOR_TASK_H
#define __MONITOR_TASK_H

#include "user_common.h"

typedef enum{
  CAP_VOL_LOW,
  CAP_CHARGING,
  CAP_FULL,
}cap_status;

typedef struct{
  uint8_t sys_ready;              /* 系统启动就绪 */
  uint16_t master_timeOutCounter; /* 主机等待超时 */
  uint32_t master_frameCounter;   /* 主机帧率 */
  uint8_t master_offLineFlag;     /* 主机掉线标志位 */
}monitor_t;

extern monitor_t monitor;

extern TaskHandle_t xHandleTaskMonitor;
void vTaskMonitor(void *pvParameters);

#endif /* __MONITOR_TASK_H */
