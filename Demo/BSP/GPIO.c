/**
  ******************************************************************************
  * @file    GPIO.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   GPIO应用函数接口
  ******************************************************************************
  */
  
  
#include "GPIO.h"


/**
  * @brief  GPIO快速初始化
  * @param  RCC_AHB1Periph 	GPIO时钟 	RCC_AHB1Periph_GPIOA~K
  *			GPIOx			GPIO端口	GPIOA~K
  *			GPIO_Pin		GPIO引脚	GPIO_Pin_0~15
  *			GPIO_Mode		配置GPIO的模式 @ref GPIOPuPd_TypeDef
  *			GPIO_OType		配置GPIO的输出模式，输入时为0x00 @ref GPIOPuPd_TypeDef
  *			GPIO_PuPd		配置GPIO是否上/下拉 @ref GPIOPuPd_TypeDef
  * @retval None
  */
void GPIO_QuickInit(uint32_t RCC_AHB1Periph, GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_OType = GPIO_OType;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

