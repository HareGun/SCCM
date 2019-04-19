/**
  ******************************************************************************
  * @file    LED_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   LED灯任务
  ******************************************************************************
  */
  
  
#include "LED_Task.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskLED = NULL;

/**
  * @brief  LED灯任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskLed(void *pvParameters)
{
	
	while(1)
	{
		LED_GREEN(1);
		vTaskDelay(100);
		LED_GREEN(0);
		vTaskDelay(100);
		
		vTaskDelay(1200);
			
		
	}	
}

