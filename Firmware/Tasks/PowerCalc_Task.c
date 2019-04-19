/**
  ******************************************************************************
  * @file    PowerCalc_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   功率计算任务
  ******************************************************************************
  */
  
  
#include "PowerCalc_Task.h"
#include "Measurement.h"


#define POWER_LIMIT     80

Judge_PowerHeatData_t Judge_PowerHeatData;

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskPowerCalc = NULL;

/**
  * @brief  功率计算任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskPowerCalc(void *pvParameters)
{
	TickType_t xLastWakeTime;
  Measurement_Init();
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
    Judge_PowerHeatData.chassisVolt = measurement.bat_voltage;
    Judge_PowerHeatData.chassisCurrent = measurement.bat_current;
    Judge_PowerHeatData.chassisPower = Judge_PowerHeatData.chassisVolt*Judge_PowerHeatData.chassisCurrent;
    //功率缓冲计算
    Judge_PowerHeatData.chassisPowerBuffer -= (Judge_PowerHeatData.chassisPower - POWER_LIMIT)*0.01f;
    
    if(Judge_PowerHeatData.chassisPowerBuffer <= 0.0f){
      Judge_PowerHeatData.chassisPowerBuffer = 0.0f;
    }
    else{
      if(Judge_PowerHeatData.chassisPowerBuffer > 60.0f){
        Judge_PowerHeatData.chassisPowerBuffer = 60.0f;
      }
    }
		vTaskDelayUntil(&xLastWakeTime, 10);
	}	
}

