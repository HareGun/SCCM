/**
  ******************************************************************************
  * @file    DataSend_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   数据发送任务
  ******************************************************************************
  */
  
  
#include "DataSend_Task.h"
#include "PowerCalc_Task.h"
#include "Control_Task.h"
#include "Measurement.h"
#include "CAN.h"
#include "BQ24640.h"


usart_dataSend_t usart_dataSend;
can_dataSend_t can_dataSend;
can_dataReceive_t can_dataReceive;

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskDataSend = NULL;

/**
  * @brief  数据包校验生成
  * @param[in]  buff	数据包
  * @param[in]  len   数据包总长度（包括校验位）
  * @retval 	校验值
  */
uint8_t uartChecksum(uint8_t* buff, uint8_t len){
	uint8_t sum = 0;
	
	for(uint8_t i=0; i<len-1; i++){
		sum += buff[i]; 
	}
  
  return sum;	
}

void uart_sendData(void){
  usart_dataSend.Bat_current = Judge_PowerHeatData.chassisCurrent;
  usart_dataSend.Bat_voltage = Judge_PowerHeatData.chassisVolt;
  usart_dataSend.Bat_power = Judge_PowerHeatData.chassisPower;
  usart_dataSend.Bat_Buff = Judge_PowerHeatData.chassisPowerBuffer;
  usart_dataSend.Cap_voltage = measurement.cap_voltage;
  usart_dataSend.Cap_changeCurrent = control.chargeCurrent;
  usart_dataSend.cap_status = measurement.cap_status;
  usart_dataSend.flag.BQ_isEnable = control.chargeEnable;
  usart_dataSend.flag.BQ_PG = BQ_GET_PG_PIN();
  usart_dataSend.flag.BQ_STAT = BQ_GET_STAT_PIN();
  usart_dataSend.flag.LM3488_isEnable = control.boostEnable;
  usart_dataSend.flag.CAP_isOutput = control.isCapOutput;
  
  uint8_t temp[40];
  temp[0] = 0x5A;
  temp[1] = 0x5A;
  memcpy(&temp[2], usart_dataSend.data,sizeof(uint8_t[29]));
  temp[31] = uartChecksum(temp, 32);
  for(int i = 0; i<32; i++){
    USART_sendChar(USART1, temp[i]);
  }
  
}

void can_sendData(void){
  can_dataSend.chassisPower = Judge_PowerHeatData.chassisPower;
	can_dataSend.chassis_Buff = Judge_PowerHeatData.chassisPowerBuffer;
	can_dataSend.cap_usable = measurement.cap_usable;
	
	CAN_SendData(CAN1, CAN_ID_STD, CAN1_TX_ID, can_dataSend.data);
  
}

void can_getInfo(CanRxMsg RxMessage){
  memcpy(can_dataReceive.data, RxMessage.Data, sizeof(uint8_t[8]));
  control.chargePower = can_dataReceive.chargePower;
  control.chargeEnable = can_dataReceive.chargeEnable;
  if(!measurement.cap_usable){
    control.isCapOutput = 0;
  }
  else{
    control.isCapOutput = can_dataReceive.isCapOutput;
  }
  
	
	CAN_SendData(CAN1, CAN_ID_STD, CAN1_TX_ID, can_dataSend.data);
  
}

/**
  * @brief  数据发送任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskDataSend(void *pvParameters)
{
	TickType_t xLastWakeTime;
	
  USART1_QuickInit(115200);
  USART1_RXDMA_Config((uint32_t)USART1_buff, USART1_BUFFLEN);
  CAN1_QuickInit();
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{	
		uart_sendData();
    can_sendData();
		vTaskDelayUntil(&xLastWakeTime, 20);
		//vTaskDelay(100);
	}	
}

