/**
  ******************************************************************************
  * @file    SystemInit_Tasks.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   各种外设初始化，全部的任务初始化的地方
  ******************************************************************************
  */
  
  
#include "SystemInit_Tasks.h"
#include "Command_Task.h"


EventGroupHandle_t xSystemInitEventGroup = NULL;


/**
  * @brief  系统、外设初始化，任务创建，仅执行一次
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskSystemInit(void *pvParameters)
{
  LED_Init();
	KEY_Init();
	CAN1_QuickInit();
//	CAN2_QuickInit();
	DR16_receiverInit();
  
  

  vTaskDelay(100);
	/* 创建事件标志组 */
	xSystemInitEventGroup = xEventGroupCreate();
	
	/* 任务创建开始 */
	xTaskCreate(vTaskDevicesMonitor, "DEVMonitor", 100, NULL, 0, &xHandleDevicesMonitor);
	xTaskCreate(vTaskChassis,"Task Chassis",256,NULL,2,&xHandleTaskChassis);
  xTaskCreate(vTaskCommand,"Task Command",256,NULL,2,&xHandleTaskCommand);
  
  
	//vTaskDelay(100);
	//vTaskPrioritySet(NULL, 0);
	//运行完删除本任务
  vTaskDelete(NULL);
	
}

