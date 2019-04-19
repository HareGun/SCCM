#ifndef __MONITOR_TASK_H
#define __MONITOR_TASK_H

#include "user_common.h"

typedef enum{
  CAP_VOL_LOW,
  CAP_CHARGING,
  CAP_FULL,
}cap_status;

typedef struct{
  uint8_t sys_ready;              /* ϵͳ�������� */
  uint16_t master_timeOutCounter; /* �����ȴ���ʱ */
  uint32_t master_frameCounter;   /* ����֡�� */
  uint8_t master_offLineFlag;     /* �������߱�־λ */
}monitor_t;

extern monitor_t monitor;

extern TaskHandle_t xHandleTaskMonitor;
void vTaskMonitor(void *pvParameters);

#endif /* __MONITOR_TASK_H */
