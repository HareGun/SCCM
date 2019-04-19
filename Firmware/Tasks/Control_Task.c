/**
  ******************************************************************************
  * @file    Control_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   控制任务
  ******************************************************************************
  */
  
  
#include "Control_Task.h"

#include "MCP4725.h"
#include "BQ24640.h"
#include "LM3488.h"
#include "PowerPath.h"
#include "Measurement.h"


/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskControl = NULL;


control_t control;

/**
  * @brief  设置充电功率
  * @param  power_mW 充电功率，单位毫瓦
  * @retval None
  */
void BQ_setChargePower(float power_W){
  if(power_W > CONTROL_CHARGE_MAX_POWER){
    power_W = CONTROL_CHARGE_MAX_POWER;
  }
  else if(power_W < 0.0f){
    power_W = 0;
  }
  
  if(measurement.bat_voltage != 0){
    control.chargeCurrent = power_W/measurement.bat_voltage;
  }
  else{
    control.chargeCurrent = 0;
  }
  
  BQ_setChargeCurrent(control.chargeCurrent);
}

/**
  * @brief  设置充电功率
  * @param  power_mW 充电功率，单位毫瓦
  * @retval None
  */
void Control_setMode(control_mode_e mode){
  control.mode = mode;
}


/**
  * @brief  控制任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskControl(void *pvParameters)
{
  TickType_t xLastWakeTime;
  
  PowerPath_Init();
  LM3488_Init();
  MCP4725_Init();
	BQ24640_Init();
  control.mode = CONTROL_OFF;
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
    
    switch(control.mode){
      case CONTROL_OFF:
        control.boostEnable = 0;
        control.chargeEnable = 0;
        control.isCapOutput = 0;
        control.chargePower = 0.0f;
      break;
      
      case CONTROL_NORMAL:
        /* 滞回比较 */
        if(measurement.cap_voltage > 7.0f){
          control.boostEnable = 1;
        }
        else if(measurement.cap_voltage < 5.0f){
          control.boostEnable = 0;
        }
        
        if(!measurement.cap_usable){
          control.isCapOutput = 0;
        }
      break;
      default:
        control.boostEnable = 0;
        control.chargeEnable = 0;
        control.isCapOutput = 0;
        control.chargePower = 0.0f;
        break;
      
    }
    
    
    LM3488_EN(control.boostEnable);
    POWERPATH_CAP_OUTPUT(control.isCapOutput);
    BQ_EN(control.chargeEnable);
    
    BQ_setChargePower(control.chargePower);
    
		vTaskDelayUntil(&xLastWakeTime, 10);
	}	
}

