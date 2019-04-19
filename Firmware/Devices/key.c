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
uint8_t keyCode = 0;

GPIOPins_t Keys_GPIO[KEY_COUNT] = {
	{KEY1_GPIO_CLK, KEY1_GPIO_PORT, KEY1_PIN},
};


/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void Key_Init(void)
{		
	for(int i = 0; i < KEY_COUNT; i++){
		GPIO_QuickInit(Keys_GPIO[i].GPIO_CLK, Keys_GPIO[i].GPIOx, Keys_GPIO[i].GPIO_Pin, GPIO_Mode_IPU);
	}

}



void Key_Process(void){
	keyCode = 0;
	for(int i = 0; i < KEY_COUNT; i++){
		userKeyList[i].keyReleaseJump = 0;
		userKeyList[i].keyPressedJump = 0;
		
		
		userKeyList[i].KeyStatus = !GPIO_ReadInputDataBit (Keys_GPIO[i].GPIOx, Keys_GPIO[i].GPIO_Pin);
		
		if (userKeyList[i].KeyStatus != userKeyList[i].lastKeyStatus) {
			if(userKeyList[i].KeyStatus){
				keyCode = i+1;
				userKeyList[i].keyPressedJump = userKeyList[i].KeyStatus;
			}
			else{
				
				userKeyList[i].keyReleaseJump = userKeyList[i].lastKeyStatus;
				userKeyList[i].longPressed = 0;
				userKeyList[i].timer = 0;
			}
		}
		
		if(userKeyList[i].KeyStatus){
			userKeyList[i].timer++;
			if(userKeyList[i].timer > 100){
				userKeyList[i].longPressed = userKeyList[i].KeyStatus;
				userKeyList[i].timer = 0;
			}
		}
		
		userKeyList[i].lastKeyStatus = userKeyList[i].KeyStatus;
	}
	
	
}

