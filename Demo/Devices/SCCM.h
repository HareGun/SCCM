#ifndef __SCCM_H
#define __SCCM_H

#include "user_common.h"

#define SCCM_SEND_ID   	0x601
#define SCCM_READ_ID		0x600

#define SCCM_CHARGE_MAX_POWER  80.0f

typedef union{
  uint8_t data[8];
   struct{
    float chassis_power;    /* 底盘功率，单位：W */
    uint8_t chassis_buff;   /* 底盘功率缓冲 */
    uint8_t cap_usable;    /* 电容可以进行输出 */
    int8_t cap_level;     /* 电容电量百分比 */
  };
}SCCM_ReceiveData_t;

typedef union{
  uint8_t data[8];
  struct{
    float charge_power;    /* 充电功率，单位：W ,范围 0-80W */
    uint8_t charge_enable; /* 充电使能 */
    uint8_t is_cap_output;  /* 使用电容供电 */
  };
}SCCM_SendData_t;

//typedef union{
//  uint8_t data[8];
//  
   typedef struct{
    float chassisPower;    /* 底盘功率，单位：W */
			uint16_t chassis_volt; 					/* 底盘输出电压 单位 毫伏 */
			uint16_t chassis_current; 			/* 底盘输出电流 单位 毫安 */
  }SCCM_Debug_t;
  
//};

typedef struct{
  SCCM_ReceiveData_t receiveData;
  SCCM_SendData_t sendData;
  SCCM_Debug_t SCCM_Debug;
  uint16_t infoUpdateFrame;   /* 帧率 */
  uint8_t infoUpdateFlag;     /* 更新标志 */
  uint8_t offLineFlag;        /* 掉线标记 */
}SCCM_t;

extern SCCM_t SCCM;

void SCCM_getInfo(CanRxMsg RxMessage);
void SCCM_setConfig(float chargePower, uint8_t chargeEN, uint8_t isCapOutput);


#endif /* __SCCM_H */
