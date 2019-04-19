#ifndef __M3508_MOTOR_H
#define __M3508_MOTOR_H

#include "user_common.h"

typedef struct{
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realCurrent;		//读回来的实际电流
	uint8_t temperture;			//读回来的电机温度
  uint16_t lastAngle;			//上次的角度
	int32_t totalAngle;			//累积总共角度
	int16_t turnCount;			//转过的圈数
	int16_t targetSpeed;			//目标速度
	int32_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	positionpid_t pid_speed;		//电机速度pid
	positionpid_t pid_angle;		//角度电机pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
}M3508s_t;

#define M3508_CurrentRatio	819.2f	//16384/20A = 819.2->1A
//#define M3508_FIRSTANGLE		3800		/* 电机初始位置 */

/* 角度转编码器值 */
#define M3508_ANGLE_TO_ENCODER(x)   (8192.0f/360.0f * x)

/* 减速后角度转编码器值 */
#define M3508_P19ANGLE_TO_ENCODER(x)   (x/19.0f * 8192.0f)

//void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);/* 移至底盘 */
void M3508_getInfo(M3508s_t *p_M3508, CanRxMsg RxMessage);
int32_t M3508_clearTurnCounter(M3508s_t *p_M3508);


#endif /* __M3508_MOTOR_H */
