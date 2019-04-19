/**
  ******************************************************************************
  * @file    LED.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   LED灯应用函数接口
  ******************************************************************************
  */
  
  
#include "LED.h"


/**
  * @brief  LED灯初始化
  * @param  None
  * @retval None
  */
void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = LED_STA1_PIN | LED_MODE_PIN |
                                LED_CAPLOW_PIN | LED_CAPFULL_PIN;
	GPIO_Init(LED_STA1_GPIO_PORT, &GPIO_InitStructure);
	
	LED_STA1(0);
  LED_MODE(0);
  LED_CAPLOW(0);
  LED_CAPFULL(0);
  
}


