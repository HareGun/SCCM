/**
  ******************************************************************************
  * @file    SCCM.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   超级电容充电管理函数接口
  ******************************************************************************
  */
  
  
#include "SCCM.h"



SCCM_t SCCM;

/**
  * @brief  从CAN报文中获取信息
  * @param  RxMessage 	CAN报文接收结构体
  * @retval None
  */
void SCCM_getInfo(CanRxMsg RxMessage){
	//报文id确认
	if(RxMessage.StdId != SCCM_READ_ID)
		return;

	memcpy(SCCM.receiveData.data, RxMessage.Data, sizeof(uint8_t[8]));
	
	SCCM.infoUpdateFrame++;
	SCCM.infoUpdateFlag = 1;
	
}

/**
  * @brief  配置充电管理状态
  * @param  chargePower 	充电功率，单位：W ,范围 0-80W
  *         chargeEN      充电使能
  *         isCapOutput   使用电容供电
  * @retval None
  */
void SCCM_setConfig(float chargePower, uint8_t chargeEN, uint8_t isCapOutput){
  if(chargePower > SCCM_CHARGE_MAX_POWER){
    chargePower = SCCM_CHARGE_MAX_POWER;
  }
  else if(chargePower < 0.0f){
    chargePower = 0;
  }
  
  SCCM.sendData.charge_power = chargePower;
  SCCM.sendData.charge_enable = chargeEN;
	SCCM.sendData.is_cap_output = isCapOutput;
  
  CAN_SendData(CAN1, CAN_ID_STD, SCCM_SEND_ID, SCCM.sendData.data);
}






