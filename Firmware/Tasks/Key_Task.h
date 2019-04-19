#ifndef __KEY_TASK_H
#define __KEY_TASK_H

#include "user_common.h"

extern TaskHandle_t xHandleTaskUserKey;


void vTaskUserKey(void *pvParameters);

#endif /* __KEY_TASK_H */
