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
    float chassisPower;    /* ���̹��ʣ���λ��W */
    uint8_t chassis_Buff;  /* ���̹��ʻ��� */
    uint8_t cap_usable;    /* ���ݿ��Խ������ */
    int8_t cap_level;     /* ���ݵ����ٷֱ� */
  };
  
}can_dataSend_t;

typedef union{
  uint8_t data[8];
  
   struct{
    float chassisPower;    /* ���̹��ʣ���λ��W */
			uint16_t chassis_volt; 					/* ���������ѹ ��λ ���� */
			uint16_t chassis_current; 			/* ����������� ��λ ���� */
  };
  
}can_dataSendDebug_t;

typedef union{
  uint8_t data[8];
  
  struct{
    float chargePower;    /* ��繦�ʣ���λ��W ,��Χ 0-80W */
    uint8_t chargeEnable; /* ���ʹ�� */
    uint8_t isCapOutput;  /* ʹ�õ��ݹ��� */
  };
  
}can_dataReceive_t;

extern TaskHandle_t xHandleTaskDataSend;

void vTaskDataSend(void *pvParameters);

void can_getInfo(CanRxMsg RxMessage);

#endif /* __DATASEND_TASK_H */
