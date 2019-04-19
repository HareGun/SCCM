#ifndef __CAN_H
#define __CAN_H

#include "user_common.h"

/********CAN1_Pin_define********/
#define CAN1_RX_GPIO_CLK          	RCC_APB2Periph_GPIOA
#define CAN1_RX_GPIO_PORT           GPIOA
#define CAN1_RX_Pin           		GPIO_Pin_11
#define CAN1_RX_PINSOURCE			GPIO_PinSource11

#define CAN1_TX_GPIO_CLK          	RCC_APB2Periph_GPIOA
#define CAN1_TX_GPIO_PORT           GPIOA
#define CAN1_TX_Pin          	 	GPIO_Pin_12
#define CAN1_TX_PINSOURCE			GPIO_PinSource12
/********CAN1_Pin_define********/

/********CAN1_Config********/
#define CAN1_SJW		CAN_SJW_2tq
#define CAN1_BS1		CAN_BS1_5tq
#define CAN1_BS2		CAN_BS2_3tq
#define CAN1_Prescaler	4

#define CAN1_RX_ID  0x601   /* 本机接收 */
#define CAN1_TX_ID  0x600   /* 本机发送 */

#define CAN1_FILTER_ID_HIGH         (((u32)CAN1_RX_ID<<21)&0xffff0000)>>16
#define CAN1_FILTER_ID_LOW          (((u32)CAN1_RX_ID<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff
#define CAN1_FILTER_MASK_ID_HIGH    0xFFFF
#define CAN1_FILTER_MASK_ID_LOW     0xFFFF
/********CAN1_Config********/

/*******CAN1_NVIC_Config********/
#define CAN1_NVIC_MainPriority 	5
#define CAN1_NVIC_SubPriority 	0
/********CAN1_NVIC_Config********/


void CAN1_QuickInit(void);
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);




#endif /* __CAN_H */
