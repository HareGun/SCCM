#ifndef __KEY_TASK_H
#define __KEY_TASK_H

#include "user_common.h"

extern TaskHandle_t xHandleTaskUserKey;
extern TaskHandle_t xHandleTaskIDSet;


void vTaskUserKey(void *pvParameters);
void vTaskIDSet(void *pvParameters);

#endif /* __KEY_TASK_H */
