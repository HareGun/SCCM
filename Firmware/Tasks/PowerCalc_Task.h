#ifndef __POWERCALC_TASK_H
#define __POWERCALC_TASK_H

#include "user_common.h"

typedef struct{
  float chassisVolt;
  float chassisCurrent;
  float chassisPower;
  float chassisPowerBuffer;
	uint8_t infoUpdateFlag;
}Judge_PowerHeatData_t;

extern Judge_PowerHeatData_t Judge_PowerHeatData;

extern TaskHandle_t xHandleTaskPowerCalc;

void vTaskPowerCalc(void *pvParameters);

#endif /* __POWERCALC_TASK_H */
