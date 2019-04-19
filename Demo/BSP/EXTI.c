/**
  ******************************************************************************
  * @file    EXTI.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   EXTI外部中断应用函数接口
  ******************************************************************************
  */

#include "EXTI.h"


/**
  * @brief  EXTI外部中断配置
  * @param  EXTI_Line 	  			外部中断源
  *			EXTI_Mode				中断模式：触发事件/触发中断
  *			EXTI_Trigger			中断触发沿
  * 		EXTI_LineCmd			使能/关闭中断线
  * @retval None
  */
void EXTI_Config(uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTI_Trigger, FunctionalState EXTI_LineCmd){
	EXTI_InitTypeDef EXTI_InitStructure;
	
	//选择外部中断源
	EXTI_InitStructure.EXTI_Line = EXTI_Line;
	
	//中断模式，触发事件/触发中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode;
	
	//触发沿，上升沿/下降沿/双边沿
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
	
	//使能，enable/disable
	EXTI_InitStructure.EXTI_LineCmd = EXTI_LineCmd;
	
	EXTI_Init(&EXTI_InitStructure);
	
}
