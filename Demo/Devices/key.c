/**
  ******************************************************************************
  * @file    key.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   按键应用函数接口
  ******************************************************************************
  */

#include "key.h"
key_t userKeyList[KEY_COUNT];

//TaskHandle_t xHandleTaskKey = NULL;

/**
  * @brief  按键扫描任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskKey(void *pvParameters)
{
//	while(1){
		Key_Scan();
		if(userKeyList[0].flag.keyPressedJump){
			
			
		}
		
//	}	
}

/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE); 	//初始化GPIO时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
	GPIO_InitStructure.GPIO_Pin   = KEY_PIN;	 
	
	GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);	

}


static void Key_Update(void) {
	userKeyList[0].flag.lastKeyStatus = userKeyList[0].flag.KeyStatus;
	userKeyList[0].flag.KeyStatus = GPIO_ReadInputDataBit (KEY_GPIO_PORT,KEY_PIN);
}


void Key_Scan(void){
	Key_Update();
	userKeyList[0].flag.keyPressedJump = 0;
	userKeyList[0].flag.keyReleaseJump = 0;
	if (userKeyList[0].flag.KeyStatus != userKeyList[0].flag.lastKeyStatus) {
		if(userKeyList[0].flag.KeyStatus)
			userKeyList[0].flag.keyReleaseJump = 1;
		else
			userKeyList[0].flag.keyPressedJump = 1;
	}
}

