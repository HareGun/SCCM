/**
  ******************************************************************************
  * @file    BQ24640.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   BQ24640充电管理应用函数接口
  ******************************************************************************
  */
  
  
#include "BQ24640.h"
#include "MCP4725.h"


/**
  * @brief  BQ24640引脚初始化
  * @param  None
  * @retval None
  */
void BQ24640_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = BQ_STAT_PIN | BQ_PG_PIN;
	GPIO_Init(BQ_STAT_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BQ_EN_PIN;
	GPIO_Init(BQ_EN_GPIO_PORT, &GPIO_InitStructure);
  
  BQ_EN(0);
  
}

/**
  * @brief  BQ24640设置充电电流
  * @param  current 电流，单位A
  * @retval None
  */
void BQ_setChargeCurrent(float current){
  if(current > BQ_CHARGE_CURRENT_MAX){
    current = BQ_CHARGE_CURRENT_MAX;
  }
  MCP4725_setVoltage(current*BQ_ISET_RATIO);
  
}




