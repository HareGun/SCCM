/**
  ******************************************************************************
  * @file    LM3488.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   LM3488应用函数接口
  ******************************************************************************
  */
  
  
#include "LM3488.h"


/**
  * @brief  LM3488 GPIO初始化
  * @param  None
  * @retval None
  */
void LM3488_Init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LM3488_EN_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LM3488_EN_PIN;
	GPIO_Init(LM3488_EN_GPIO_PORT, &GPIO_InitStructure);
  LM3488_EN(0);
  
}


