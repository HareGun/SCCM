#ifndef __LED_H
#define __LED_H

#include "user_common.h"


#define LED_STA1_GPIO_CLK             RCC_APB2Periph_GPIOB
#define LED_STA1_GPIO_PORT           	GPIOB
#define LED_STA1_PIN                  GPIO_Pin_1

#define LED_MODE_GPIO_CLK             RCC_APB2Periph_GPIOB
#define LED_MODE_GPIO_PORT            GPIOB
#define LED_MODE_PIN                  GPIO_Pin_2

#define LED_CAPLOW_GPIO_CLK           RCC_APB2Periph_GPIOB
#define LED_CAPLOW_GPIO_PORT          GPIOB
#define LED_CAPLOW_PIN                GPIO_Pin_10

#define LED_CAPFULL_GPIO_CLK          RCC_APB2Periph_GPIOB
#define LED_CAPFULL_GPIO_PORT         GPIOB
#define LED_CAPFULL_PIN               GPIO_Pin_11

#define LED_STA1(isOn) 				    GPIO_WriteBit(LED_STA1_GPIO_PORT,LED_STA1_PIN, (BitAction)!isOn)
#define LED_STA1_TOGGLE() 				GPIO_ToggleBits(LED_STA1_GPIO_PORT, LED_STA1_PIN)

#define LED_MODE(isOn) 				    GPIO_WriteBit(LED_MODE_GPIO_PORT,LED_MODE_PIN, (BitAction)!isOn)
#define LED_MODE_TOGGLE() 		  	GPIO_ToggleBits(LED_MODE_GPIO_PORT, LED_MODE_PIN)

#define LED_CAPLOW(isOn) 				  GPIO_WriteBit(LED_CAPLOW_GPIO_PORT,LED_CAPLOW_PIN, (BitAction)!isOn)
#define LED_CAPLOW_TOGGLE()       GPIO_ToggleBits(LED_CAPLOW_GPIO_PORT, LED_CAPLOW_PIN)

#define LED_CAPFULL(isOn)         GPIO_WriteBit(LED_CAPFULL_GPIO_PORT,LED_CAPFULL_PIN, (BitAction)!isOn)
#define LED_CAPFULL_TOGGLE()      GPIO_ToggleBits(LED_CAPFULL_GPIO_PORT, LED_CAPFULL_PIN)

typedef struct{
  
  
  
}led_list_t;

void LED_Init(void);

#endif /* __LED_H */
