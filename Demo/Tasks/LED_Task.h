#ifndef __LED_TASK_H
#define __LED_TASK_H

#include "user_common.h"

extern TaskHandle_t xHandleTaskLED;
void vTaskLed(void *pvParameters);

#endif /* __LED_TASK_H */
