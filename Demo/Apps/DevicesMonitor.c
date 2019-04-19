/**
  ******************************************************************************
  * @file    DevicesMonitor.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   �ⲿ�豸֡�ʼ�⺯���ӿ�
  ******************************************************************************
  */
  
  
#include "DevicesMonitor.h"
#include "DR16_Receiver.h"
#include "Chassis_control.h"
#include "SCCM.h"


//��С֡��
#define GY_IMU_FRAMEMIN		5


/**
  * @brief  ����豸֡�����㣬ÿ200ms����һ��
  * @param  None
  * @retval None
  */
void DevicesMonitor_update(void){
	//M3508
	for(int i = 0; i<4; i++){
		if(Chassis.M3508s[i].infoUpdateFrame < 5){
			Chassis.M3508s[i].offLineFlag = 1;
		}
		else{
			Chassis.M3508s[i].offLineFlag = 0;
		}
		Chassis.M3508s[i].infoUpdateFrame = 0;
	}
	
	//SCCM
	if(SCCM.infoUpdateFrame < 5){
		SCCM.offLineFlag = 1;
	}
	else{
		SCCM.offLineFlag = 0;
	}
	SCCM.infoUpdateFrame = 0;
	
	//ң����
	if(dr16_data.infoUpdateFrame < 5){
		dr16_data.offLineFlag = 1;
		LED_GREEN(0);
	}
	else{
		dr16_data.offLineFlag = 0;
	}
	dr16_data.infoUpdateFrame = 0;
	

	
		
	
}
