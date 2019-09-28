#ifndef __DATASEND_TASK_H
#define __DATASEND_TASK_H

#include "user_common.h"

typedef union{
  uint8_t data[29];
  
   struct{
    float Bat_voltage;
    float Bat_current;
    float Bat_power;
    float Bat_Buff;
    float Cap_voltage;
    float Cap_changeCurrent;
    uint8_t cap_status;
    union{
       struct{
        bool BQ_isEnable : 1;
        bool BQ_STAT : 1;
        bool BQ_PG : 1;
        bool LM3488_isEnable : 1;
        bool CAP_isOutput : 1;
        
      };
      uint32_t flagData;          
    }flag;
    

  };
  
}usart_dataSend_t;

typedef union{
  uint8_t data[8];
  
   struct{
    float chassisPower;    /* 底盘功率，单位：W */
    uint8_t chassis_Buff;  /* 底盘功率缓冲 */
    uint8_t cap_usable;    /* 电容可以进行输出 */
    int8_t cap_level;     /* 电容电量百分比 */
  };
  
}can_dataSend_t;

typedef union{
  uint8_t data[8];
  
   struct{
    float chassisPower;    /* 底盘功率，单位：W */
			uint16_t chassis_volt; 					/* 底盘输出电压 单位 毫伏 */
			uint16_t chassis_current; 			/* 底盘输出电流 单位 毫安 */
  };
  
}can_dataSendDebug_t;

typedef union{
  uint8_t data[8];
  
  struct{
    float chargePower;    /* 充电功率，单位：W ,范围 0-80W */
    uint8_t chargeEnable; /* 充电使能 */
    uint8_t isCapOutput;  /* 使用电容供电 */
  };
  
}can_dataReceive_t;

extern TaskHandle_t xHandleTaskDataSend;

void vTaskDataSend(void *pvParameters);

void can_getInfo(CanRxMsg RxMessage);

#endif /* __DATASEND_TASK_H */
