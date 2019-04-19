#ifndef __CONTROL_TASK_H
#define __CONTROL_TASK_H

#include "user_common.h"


#define CONTROL_CHARGE_MAX_POWER      80.0f

typedef enum{
  CONTROL_OFF,
  CONTROL_NORMAL
}control_mode_e;

typedef struct{
  float chargeCurrent;  /* 充电电流，单位：A*/
  float chargePower;    /* 充电功率，单位：W ,范围 0-80W*/
  uint8_t chargeEnable; /* 充电使能 */
  uint8_t boostEnable;  /* 升压使能 */
  uint8_t isCapOutput;  /* 使用电容供电 */
  control_mode_e mode; 
}control_t;

extern control_t control;

extern TaskHandle_t xHandleTaskControl;
void vTaskControl(void *pvParameters);

void Control_setMode(control_mode_e mode);

#endif /* __CONTROL_TASK_H */
