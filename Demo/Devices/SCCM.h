#ifndef __SCCM_H
#define __SCCM_H

#include "user_common.h"

#define SCCM_SEND_ID   	0x601
#define SCCM_READ_ID		0x600

#define SCCM_CHARGE_MAX_POWER  80.0f

typedef union{
  uint8_t data[8];
   struct{
    float chassis_power;    /* ���̹��ʣ���λ��W */
    uint8_t chassis_buff;   /* ���̹��ʻ��� */
    uint8_t cap_usable;    /* ���ݿ��Խ������ */
    int8_t cap_level;     /* ���ݵ����ٷֱ� */
  };
}SCCM_ReceiveData_t;

typedef union{
  uint8_t data[8];
  struct{
    float charge_power;    /* ��繦�ʣ���λ��W ,��Χ 0-80W */
    uint8_t charge_enable; /* ���ʹ�� */
    uint8_t is_cap_output;  /* ʹ�õ��ݹ��� */
  };
}SCCM_SendData_t;

//typedef union{
//  uint8_t data[8];
//  
   typedef struct{
    float chassisPower;    /* ���̹��ʣ���λ��W */
			uint16_t chassis_volt; 					/* ���������ѹ ��λ ���� */
			uint16_t chassis_current; 			/* ����������� ��λ ���� */
  }SCCM_Debug_t;
  
//};

typedef struct{
  SCCM_ReceiveData_t receiveData;
  SCCM_SendData_t sendData;
  SCCM_Debug_t SCCM_Debug;
  uint16_t infoUpdateFrame;   /* ֡�� */
  uint8_t infoUpdateFlag;     /* ���±�־ */
  uint8_t offLineFlag;        /* ���߱�� */
}SCCM_t;

extern SCCM_t SCCM;

void SCCM_getInfo(CanRxMsg RxMessage);
void SCCM_setConfig(float chargePower, uint8_t chargeEN, uint8_t isCapOutput);


#endif /* __SCCM_H */
