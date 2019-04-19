#ifndef __SYSTEMINIT_TASKS_H
#define __SYSTEMINIT_TASKS_H

#include "user_common.h"

#define EVENTBIT_0	(1<<0)				//ÊÂ¼þÎ»
#define EVENTBIT_1	(1<<1)
#define EVENTBIT_2	(1<<2)

#define EventBit_SetID		EVENTBIT_0
#define EventBit_KeyUpdate	EVENTBIT_1
#define EventBit_DataOut	EVENTBIT_2


extern uint8_t id;
extern uint8_t debug;

extern EventGroupHandle_t xCreatedEventGroup;

void vTaskSystemInit(void *pvParameters);


#endif /* __SYSTEMINIT_TASKS_H */
