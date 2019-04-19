#ifndef __KEY_H
#define __KEY_H

#include "user_common.h"

#define	KEY_ON	 1		//按键按下
#define	KEY_OFF	 0		//按键放开

#define KEY_COUNT 1


//#define KEY_GPIO_CLK             	RCC_AHB1Periph_GPIOD
//#define KEY_PIN                  	GPIO_Pin_10
//#define KEY_GPIO_PORT           	GPIOD

#define KEY_GPIO_CLK             	RCC_AHB1Periph_GPIOD
#define KEY_PIN                  	GPIO_Pin_7
#define KEY_GPIO_PORT           	GPIOD


extern key_t userKeyList[KEY_COUNT];

void KEY_Init(void);
void Key_Scan(void);

//extern TaskHandle_t xHandleTaskKey;
//void vTaskKey(void *pvParameters);

#endif /* __KEY_H */


