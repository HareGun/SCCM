#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H

#include "user_common.h"

extern TaskHandle_t xHandleTaskChassis;

void vTaskChassis(void *pvParameters);

#endif /* __CHASSIS_TASK_H */
