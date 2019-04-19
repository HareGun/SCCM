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
	RCC_AHB1PeriphClockCmd(LED_GREEN_GPIO_CLK | LED_RED_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(LED_LIST_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	
	GPIO_InitStructure.GPIO_Pin = LED_GREEN_PIN;
	GPIO_Init(LED_GREEN_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_RED_PIN;
	GPIO_Init(LED_RED_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LED_LIST_PINALL;
	GPIO_Init(LED_LIST_GPIO_PORT, &GPIO_InitStructure);
  
  /* 默认关闭 */ 
	LED_GREEN(0);
	LED_RED(0);
  GPIO_WriteBit(LED_LIST_GPIO_PORT, LED_LIST_PINALL, Bit_SET);
  
}

