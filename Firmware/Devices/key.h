#ifndef __KEY_H
#define __KEY_H

#include "user_common.h"

#define	KEY_ON	 1		//按键按下
#define	KEY_OFF	 0		//按键放开

#define KEY_COUNT 1

extern uint8_t keyCode;


#define KEY1_GPIO_CLK               RCC_APB2Periph_GPIOB
#define KEY1_GPIO_PORT              GPIOB
#define KEY1_PIN                    GPIO_Pin_12





extern key_t userKeyList[KEY_COUNT];

void Key_Init(void);
void Key_Process(void);

//extern TaskHandle_t xHandleTaskKey;
//void vTaskKey(void *pvParameters);

#endif /* __KEY_H */


