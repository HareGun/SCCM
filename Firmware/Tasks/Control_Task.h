#ifndef __CONTROL_TASK_H
#define __CONTROL_TASK_H

#include "user_common.h"


#define CONTROL_CHARGE_MAX_POWER      80.0f

typedef enum{
  CONTROL_OFF,
  CONTROL_NORMAL
}control_mode_e;

typedef struct{
  float chargeCurrent;  /* ����������λ��A*/
  float chargePower;    /* ��繦�ʣ���λ��W ,��Χ 0-80W*/
  uint8_t chargeEnable; /* ���ʹ�� */
  uint8_t boostEnable;  /* ��ѹʹ�� */
  uint8_t isCapOutput;  /* ʹ�õ��ݹ��� */
  control_mode_e mode; 
}control_t;

extern control_t control;

extern TaskHandle_t xHandleTaskControl;
void vTaskControl(void *pvParameters);

void Control_setMode(control_mode_e mode);

#endif /* __CONTROL_TASK_H */
