/**
  ******************************************************************************
  * @file    Chassis_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   底盘任务
  ******************************************************************************
  */
  
  
#include "Chassis_Task.h"
#include "Chassis_control.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskChassis = NULL;

/**
  * @brief  底盘任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskChassis(void *pvParameters)
{
	
	TickType_t xLastWakeTime;
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
  
  Chassis_Init();
	
//	float Chassis_Vx = 0.0f, Chassis_Vy = 0.0f, Chassis_VOmega = 0.0f;
  int counter = 0;
	
	while(1)
	{
    if(++counter >100){
			LED_RED_TOGGLE();
			counter = 0;
		}
    
		
		
		Chassis_processing();
   
    
		vTaskDelayUntil(&xLastWakeTime, 10);  /* 10ms周期 */
	}	
  
}




