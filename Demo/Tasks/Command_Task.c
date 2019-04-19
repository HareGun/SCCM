/**
  ******************************************************************************
  * @file    Command_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   操作命令解析控制任务，用于底盘，云台等控制命令分发
  * @Note  
  ******************************************************************************
  */


  
#include "Command_Task.h"
#include "Chassis_control.h"
#include "SCCM.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskCommand = NULL;

EventGroupHandle_t xCommandEventGroup = NULL;

ControlStatus_t ControlStatus;


/**
  * @brief  组合键判断处理 
  * @param  None
  * @retval None
  */
void Control_combineKeyScan(void)
{
	if(dr16_keyboard_isJumpKeyPressed(KEYBOARD_PRESSED_CTRL, KEY_FULL_MATCH, 0) ||
      dr16_keyboard_isJumpKeyPressed(KEYBOARD_PRESSED_SHIFT, KEY_FULL_MATCH,0))
  {
			//如果有Ctrl或shift键先按下，并且没有其他键按下时判断为组合键
			ControlStatus.isCombineKey = 1;
	}
  
	if(dr16_keyBorad.KeyStatus == KEYBOARD_PRESSED_NONE){
			//如果组合键全部松开则关闭组合键
			ControlStatus.isCombineKey = 0;
	}
	
}

/**
  * @brief  组合键处理 
  * @param  None
  * @retval None
  */
void Control_combineKeyHandle(void)
{
  
}

/**
  * @brief  非组合键处理 
  * @param  None
  * @retval None
  */
void Control_notCombineKeyHandle(void)
{
	
}


/**
  * @brief  控制命令任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskCommand(void *pvParameters)
{
	TickType_t xLastWakeTime;
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
  
  ControlStatus.SpecialMode = SpecialMode_Normal;
  
  
  
  float temp_charge_power;    /* 充电功率，单位：W ,范围 0-80W */
  uint8_t temp_charge_enable; /* 充电使能 */
  uint8_t temp_is_cap_output;  /* 使用电容供电 */
	
	while(1)
	{
    
    switch(dr16_data.rc.s_left){
      /* 电脑控制 */
      case DR16_SWITCH_UP:
        ControlStatus.Controlby = Control_ByPC;  
      
      break;
      
      /* RC控制 */
      case DR16_SWITCH_MID:
        ControlStatus.Controlby = Control_ByRC;
        Chassis_setMode(CHASSIS_MODE_NORMAL);
        
        switch(dr16_data.rc.s_right){
          case DR16_SWITCH_UP:
            temp_is_cap_output = 1;
            temp_charge_enable = 1;
          break;

          case DR16_SWITCH_MID:          
            temp_charge_enable = 1;
            temp_is_cap_output = 0;
          break;
          case DR16_SWITCH_DOWN:
            temp_charge_enable = 0;
            temp_is_cap_output = 0;
          break;
          
          
        }
        
        Chassis_setSpeed((float)dr16_data.rc.ch2_LX / DR16_ROCKER_MAXVALUE * Chassis.speedLimit,
                             (float)dr16_data.rc.ch3_LY / DR16_ROCKER_MAXVALUE * Chassis.speedLimit,
                             (float)dr16_data.rc.ch0_RX / DR16_ROCKER_MAXVALUE * Chassis.speedLimit,
                             0);
        
      break;
        
      case DR16_SWITCH_DOWN:
        ControlStatus.Controlby = Control_OFF;
        Chassis_setMode(CHASSIS_MODE_OFF);
        temp_charge_enable = 0;
      break;
      
      default:
        
      break;
    }
    
    
    temp_charge_power = abs(dr16_data.rc.ch4_DW / DR16_ROCKER_MAXVALUE * 80);
    
    SCCM_setConfig(temp_charge_power,temp_charge_enable,temp_is_cap_output);
		vTaskDelayUntil(&xLastWakeTime, 10);
	}	


}
