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
#include "Monitor_Task.h"
#include "PowerCalc_task.h"
#include "DataSend_Task.h"
#include "Control_Task.h"

EventGroupHandle_t xSysEventGroup = NULL;


/**
  * @brief  系统、外设初始化，任务创建，仅执行一次
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskSystemInit(void *pvParameters){
	/* 创建事件标志组 */
	xSysEventGroup = xEventGroupCreate();
	
	//xEventGroupSetBits(xCreatedEventGroup, EventBit_DataOut);
	
	/* 任务创建开始 */
	xTaskCreate(vTaskPowerCalc,"Task PowerCalc",256,NULL,3,&xHandleTaskPowerCalc);
  xTaskCreate(vTaskControl,"Task Control",256,NULL,2,&xHandleTaskControl);
  xTaskCreate(vTaskDataSend,"Task DataSend",256,NULL,1,&xHandleTaskDataSend);
  xTaskCreate(vTaskMonitor, "Task Monitor", 256, NULL, 0, &xHandleTaskMonitor);
	
	//vTaskPrioritySet(NULL, 0);
	//运行完删除本任务
  vTaskDelete(NULL);
	while(1){
    
	}
}

