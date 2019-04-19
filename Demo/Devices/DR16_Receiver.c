/**
  ******************************************************************************
  * @file    DR16_Receiver.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   DR16接收机应用函数接口
  ******************************************************************************
  */
  
  
#include "DR16_Receiver.h"

uint8_t DR16_rxBuff[DR16_DBUS_PACKSIZE+2]; 	//接收buff
DR16_DBUS_DATA_t dr16_data;

keyBoard_t dr16_keyBorad;
key_t dr16_mouseKeyLeft;
key_t dr16_mouseKeyRight;

#define DR16_KEY_LONGPRESS_TIMEOUT 50

/**
  * @brief  DR16鼠标按键处理
  * @param  newKeyStatus 新按键状态，按下为1，未按下为0
  *         *key 按键结构体指针 @ref key_t
  * @retval None
  */
void DR16_mouseProcess(uint8_t newKeyStatus, key_t *key){
	key->flag.keyPressedJump = 0;
	key->flag.keyReleaseJump = 0;
	
	key->flag.KeyStatus = newKeyStatus & 0x01;
	
	if (key->flag.KeyStatus != key->flag.lastKeyStatus) {
		if(key->flag.KeyStatus)
			key->flag.keyPressedJump = key->flag.KeyStatus;
		else{
			key->flag.keyReleaseJump = key->flag.lastKeyStatus;
			key->flag.longPressed = 0;
			key->timeCounter = 0;
		}
	}
	
	if(key->flag.KeyStatus){
		key->timeCounter++;
		if(key->timeCounter > DR16_KEY_LONGPRESS_TIMEOUT){
			key->flag.longPressed = key->flag.KeyStatus;
			key->timeCounter = 0;
		}
	}
	
	key->flag.lastKeyStatus = key->flag.KeyStatus;
  
}

/**
  * @brief  DR16键盘按键处理
  * @param  newKeyStatus 新按键状态，按下对应位为1，未按下为0
  *         *keyBoard 按键结构体指针 @ref key_t
  * @retval None
  */
void DR16_keyBoardProcess(uint16_t newKeyStatus, keyBoard_t *keyBoard){
	keyBoard->keyPressedJump = 0;
	keyBoard->keyReleaseJump = 0;
	
	keyBoard->KeyStatus = newKeyStatus;
	
//	keyBoard->keyPressedJump |= (keyBoard->KeyStatus ^ keyBoard->lastKeyStatus) & keyBoard->KeyStatus;
//  keyBoard->keyReleaseJump |= (keyBoard->KeyStatus ^ keyBoard->lastKeyStatus) & keyBoard->lastKeyStatus;
  if (keyBoard->KeyStatus != keyBoard->lastKeyStatus) {
		if(keyBoard->KeyStatus)
			keyBoard->keyPressedJump = keyBoard->KeyStatus;
    
  }

  
  for(int i = 0; i < 16; i++){
    if(keyBoard->KeyStatus & 1<<i){
      keyBoard->timeCounter[i]++;
      if(keyBoard->timeCounter[i] > DR16_KEY_LONGPRESS_TIMEOUT){
        keyBoard->longPressed |= 1<<i;
        keyBoard->timeCounter[i] = 0;
      }
    }
    else{
      keyBoard->longPressed &= ~(1<<i);
			keyBoard->timeCounter[i] = 0;
    }
    
  }
  
	keyBoard->lastKeyStatus = keyBoard->KeyStatus;
  
}


/**
  * @brief  DR16接收机初始化
  * @param  None
  * @retval None
  */
void DR16_receiverInit(void){
	USART1_QuickInit(100000);
	USART1_RXDMA_Config((uint32_t)DR16_rxBuff, DR16_DBUS_PACKSIZE+2);	//+2保证安全
  
}

/**
  * @brief  DR16接收数据处理
  * @param  pData			接收buff数据指针
  * @retval None
  */
void DR16_dataProcess(uint8_t *pData){
	if (pData == NULL){
		return;
	}
	dr16_data.rc.ch0_RX = (pData[0] | (pData[1] << 8)) & 0x07FF;
	dr16_data.rc.ch1_RY = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	dr16_data.rc.ch2_LX = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	dr16_data.rc.ch3_LY = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	dr16_data.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	dr16_data.rc.s_right = ((pData[5] >> 4) & 0x0003);
	dr16_data.mouse.x = (pData[6]) | (pData[7] << 8);
	dr16_data.mouse.y = (pData[8]) | (pData[9] << 8);
	dr16_data.mouse.z = (pData[10]) | (pData[11] << 8);
	dr16_data.mouse.keyLeft = pData[12];
	dr16_data.mouse.keyRight = pData[13];
	dr16_data.keyBoard.key_code = pData[14] | (pData[15] << 8);
  
  dr16_data.rc.ch4_DW = (pData[16] | (pData[17] << 8)) & 0x07FF;

	//your control code ….
	
	dr16_data.infoUpdateFrame++;
	
	dr16_data.rc.ch0_RX -=1024;
	dr16_data.rc.ch1_RY -=1024;
	dr16_data.rc.ch2_LX -=1024;
	dr16_data.rc.ch3_LY -=1024;
  dr16_data.rc.ch4_DW -=1024;
	
	/* prevent remote control zero deviation */
	if(dr16_data.rc.ch0_RX <= 5 && dr16_data.rc.ch0_RX >= -5)
		dr16_data.rc.ch0_RX = 0;
	if(dr16_data.rc.ch1_RY <= 5 && dr16_data.rc.ch1_RY >= -5)
		dr16_data.rc.ch1_RY = 0;
	if(dr16_data.rc.ch2_LX <= 5 && dr16_data.rc.ch2_LX >= -5)
		dr16_data.rc.ch2_LX = 0;
	if(dr16_data.rc.ch3_LY <= 5 && dr16_data.rc.ch3_LY >= -5)
		dr16_data.rc.ch3_LY = 0;
  if(dr16_data.rc.ch4_DW <= 5 && dr16_data.rc.ch4_DW >= -5)
		dr16_data.rc.ch4_DW = 0;
	
	
	DR16_mouseProcess(dr16_data.mouse.keyLeft, &dr16_mouseKeyLeft);
	DR16_mouseProcess(dr16_data.mouse.keyRight, &dr16_mouseKeyRight);
  
  //DR16_keyBoardProcess(dr16_data.keyBoard.key_code, &dr16_keyBorad);
}

/**
  * @brief  按键按下跳变检测,调用后会清除对应的跳变位
  * @param  KeyCode		需要检测的键值
  * 		mode		0 - 有匹配项
  *						1 - 完全匹配
  * @retval 是否有这个键值的按键按下跳变
  */
uint16_t dr16_keyboard_isJumpKeyPressed(uint16_t KeyCode, uint8_t mode, uint8_t clearBit){
  uint16_t temp;
	if(mode){	//1 - 完全匹配
    temp = dr16_keyBorad.keyPressedJump == KeyCode;
	}
	else{		//0 - 有匹配项
    temp = dr16_keyBorad.keyPressedJump & KeyCode;
	}
  
  if(clearBit){
    //dr16_keyBorad.keyPressedJump &= ~KeyCode;
  }
	return temp;
}


/**
  * @brief  按键按下检测
  * @param  KeyCode		需要检测的键值
  * @retval 是否有这个键值的按键按下
  */
uint16_t dr16_keyboard_isPressedKey(uint16_t KeyCode, uint8_t mode){
	if(mode){	//1 - 完全匹配
		return dr16_data.keyBoard.key_code == KeyCode;
	}
	else{		//0 - 有匹配项
		return dr16_data.keyBoard.key_code & KeyCode;
	}
	
}





