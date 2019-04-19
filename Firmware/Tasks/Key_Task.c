/**
  ******************************************************************************
  * @file    Key_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   用户按键任务
  ******************************************************************************
  */
  
  
#include "Key_Task.h"
#include "key.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskUserKey = NULL;
TaskHandle_t xHandleTaskIDSet = NULL;
uint32_t counter = 0;

void vTaskIDSet(void *pvParameters);

/**
  * @brief  用户按键任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskUserKey(void *pvParameters)
{
	TickType_t xLastWakeTime;
  
	Key_Init();
  
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
  
	while(1)
	{	
		Key_Process();
		
		
		vTaskDelayUntil(&xLastWakeTime, 10);
	}	
}


