/**
  ******************************************************************************
  * @file    Command_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   ����������������������ڵ��̣���̨�ȿ�������ַ�
  * @Note  
  ******************************************************************************
  */


  
#include "Command_Task.h"
#include "Chassis_control.h"
#include "SCCM.h"

/* �����������񴴽�֮��õ���Ӧֵ���Ժ�������������ʱ����Ҫͨ�������������� */
TaskHandle_t xHandleTaskCommand = NULL;

EventGroupHandle_t xCommandEventGroup = NULL;

ControlStatus_t ControlStatus;


/**
  * @brief  ��ϼ��жϴ��� 
  * @param  None
  * @retval None
  */
void Control_combineKeyScan(void)
{
	if(dr16_keyboard_isJumpKeyPressed(KEYBOARD_PRESSED_CTRL, KEY_FULL_MATCH, 0) ||
      dr16_keyboard_isJumpKeyPressed(KEYBOARD_PRESSED_SHIFT, KEY_FULL_MATCH,0))
  {
			//�����Ctrl��shift���Ȱ��£�����û������������ʱ�ж�Ϊ��ϼ�
			ControlStatus.isCombineKey = 1;
	}
  
	if(dr16_keyBorad.KeyStatus == KEYBOARD_PRESSED_NONE){
			//�����ϼ�ȫ���ɿ���ر���ϼ�
			ControlStatus.isCombineKey = 0;
	}
	
}

/**
  * @brief  ��ϼ����� 
  * @param  None
  * @retval None
  */
void Control_combineKeyHandle(void)
{
  
}

/**
  * @brief  ����ϼ����� 
  * @param  None
  * @retval None
  */
void Control_notCombineKeyHandle(void)
{
	
}


/**
  * @brief  ������������
  * @param  pvParameters ���񱻴���ʱ�������Ĳ���
  * @retval None
  */
void vTaskCommand(void *pvParameters)
{
	TickType_t xLastWakeTime;
	
	/* ��ȡ��ǰ��ϵͳʱ�� */
	xLastWakeTime = xTaskGetTickCount();
  
  ControlStatus.SpecialMode = SpecialMode_Normal;
  
  
  
  float temp_charge_power;    /* ��繦�ʣ���λ��W ,��Χ 0-80W */
  uint8_t temp_charge_enable; /* ���ʹ�� */
  uint8_t temp_is_cap_output;  /* ʹ�õ��ݹ��� */
	
	while(1)
	{
    
    switch(dr16_data.rc.s_left){
      /* ���Կ��� */
      case DR16_SWITCH_UP:
        ControlStatus.Controlby = Control_ByPC;  
      
      break;
      
      /* RC���� */
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
