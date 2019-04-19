/**
  ******************************************************************************
  * @file    DevicesMonitor_Tasks.c
  * @author  Hare
  * @version V1.0
  * @date    2019-01-15
  * @brief   各种外设状态监控任务，主要用于离线检测
  ******************************************************************************
  */
  
  
#include "DevicesMonitor_Tasks.h"

TaskHandle_t xHandleDevicesMonitor = NULL;

/**
  * @brief  外设帧率监控任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskDevicesMonitor(void *pvParameters)
{
	while(1)
	{
    
    DevicesMonitor_update();
    vTaskDelay(100);
  }
  
}

