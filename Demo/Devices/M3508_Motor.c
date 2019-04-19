/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   M3508无刷电机，配套C620电调驱动应用函数接口
  ******************************************************************************
  */
  
  
#include "M3508_Motor.h"


/**
  * @brief  从CAN报文中获取M3508电机信息
  * #param[out] p_M3508     指向3508的结构体
  * @param[in]  RxMessage 	CAN报文接收结构体
  * @retval None
  */
void M3508_getInfo(M3508s_t *p_M3508, CanRxMsg RxMessage){
	//报文id确认
//	if((RxMessage.StdId < M3508_READID_START) || (RxMessage.StdId > M3508_READID_END))
//		return;
//	uint32_t StdId;
//	StdId = RxMessage.StdId - M3508_READID_START;
	
	//解包数据，数据格式详见C620电调说明书P33
	p_M3508->realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	p_M3508->realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	p_M3508->realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	p_M3508->temperture = RxMessage.Data[6];
  
  if(p_M3508->realAngle - p_M3508->lastAngle < -6000){
		p_M3508->turnCount++;
	}
	
	if(p_M3508->lastAngle - p_M3508->realAngle < -6000){
		p_M3508->turnCount--;
	}
	
	p_M3508->lastAngle =  p_M3508->realAngle;
	
	p_M3508->totalAngle = p_M3508->realAngle + (8192*p_M3508->turnCount);
	
	//帧率统计，数据更新标志位
	p_M3508->infoUpdateFrame++;
	p_M3508->infoUpdateFlag = 1;
}	


/**
  * @brief  清零M3508累积角度
  * #param[out] p_M3508     指向3508的结构体
  * @param[in]  RxMessage 	CAN报文接收结构体
  * @retval int32_t  返回清空前的圈数
  */
int32_t M3508_clearTurnCounter(M3508s_t *p_M3508){
	int16_t tempCount = p_M3508->turnCount;
  p_M3508->lastAngle = p_M3508->totalAngle = p_M3508->realAngle;
  p_M3508->turnCount = 0;
  
	return tempCount;
}	


///**
//  * @brief  设定M3508电机的目标电流值
//  * @param  motorName 	电机名字 @ref M3508Name_e
//  *			current		电流值，范围 -16384~0~16384
//  * @retval None
//  */
//inline void M3508_setTargetCurrent(M3508Name_e motorName, int16_t current){
//	M3508s[motorName].targetCurrent = current;
//}

///**
//  * @brief  设定M3508电机的目标角度
//  * @param  motorName 	电机名字 @ref M3508Name_e
//  *			angle		电流值，范围 0~8191
//  * @retval None
//  */
//inline void M3508_setTargetAngle(M3508Name_e motorName, uint16_t angle){
//	M3508s[motorName].targetAngel = angle;
//}

/**
  * @brief  设定M3508电机的目标速度
  * @param  motorName 	电机名字 @ref M3508Name_e
  *			speed		电流值，范围 -16384~0~16384
  * @retval None
  */
//void M3508_setTargetSpeed(M3508Name_e motorName, int16_t speed){
//	M3508s[motorName].targetSpeed = speed;
//}



