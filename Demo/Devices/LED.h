#ifndef __LED_H
#define __LED_H

#include "user_common.h"


#define LED_GREEN_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_GREEN_PIN                 GPIO_Pin_5
#define LED_GREEN_GPIO_PORT           GPIOB

#define LED_RED_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define LED_RED_PIN                   GPIO_Pin_4
#define LED_RED_GPIO_PORT             GPIOB

#define LED_GREEN_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_GREEN_PIN                 GPIO_Pin_5
#define LED_GREEN_GPIO_PORT           GPIOB

/* Á÷Ë®µÆ */
#define LED_LIST_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED_LIST_GPIO_PORT            GPIOE

#define LED1_PIN                      GPIO_Pin_9
#define LED2_PIN                      GPIO_Pin_10
#define LED3_PIN                      GPIO_Pin_11
#define LED4_PIN                      GPIO_Pin_12
#define LED5_PIN                      GPIO_Pin_13
#define LED6_PIN                      GPIO_Pin_14
#define LED7_PIN                      GPIO_Pin_15
#define LED_LIST_PINALL               0xFE00

#define LED_GREEN(isOn) 				GPIO_WriteBit(LED_GREEN_GPIO_PORT,LED_GREEN_PIN, (BitAction)!isOn)
#define LED_RED(isOn) 				  GPIO_WriteBit(LED_RED_GPIO_PORT,LED_RED_PIN, (BitAction)!isOn)

#define LED_GREEN_TOGGLE() 			GPIO_ToggleBits(LED_GREEN_GPIO_PORT, LED_GREEN_PIN)
#define LED_RED_TOGGLE() 			  GPIO_ToggleBits(LED_RED_GPIO_PORT, LED_RED_PIN)

#define LED_LIST(n, isOn)       GPIO_WriteBit(LED_LIST_GPIO_PORT, 1<<(n+9), (BitAction)!isOn)


void LED_Init(void);

#endif /* __LED_H */
