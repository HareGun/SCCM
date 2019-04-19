/**
  ******************************************************************************
  * @file    PowerPath.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   PowerPath应用函数接口
  ******************************************************************************
  */
  
  
#include "PowerPath.h"


/**
  * @brief  LM3488 GPIO初始化
  * @param  None
  * @retval None
  */
void PowerPath_Init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(POWERPATH_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = POWERPATH_PIN;
	GPIO_Init(POWERPATH_GPIO_PORT, &GPIO_InitStructure);
  POWERPATH_CAP_OUTPUT(0);
  
}


