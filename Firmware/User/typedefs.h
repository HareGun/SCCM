#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f10x.h"

//允许匿名共用体
#pragma anon_unions

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;


typedef struct{
	float Target; 					//设定目标值
	float Measured; 				//测量值
	float err; 						//本次偏差值
	float err_last; 				//上一次偏差
	float err_beforeLast; 			//上上次偏差
	float Kp, Ki, Kd;				//Kp, Ki, Kd控制系数
	float pwm; 						//pwm输出
	uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;			//积分限幅 
}incrementalpid_t;

typedef struct{
	float Target; 					//设定目标值
	float Measured; 				//测量值
	float err; 						//本次偏差值
	float err_last; 				//上一次偏差
	float integral_err; 			//所有偏差之和
	float Kp, Ki, Kd;				//Kp, Ki, Kd控制系数
	float pwm; 						//pwm输出
	uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;			//积分限幅 
}positionpid_t;

typedef struct{
	uint32_t GPIO_CLK;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}GPIOPins_t;


typedef struct{
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realCurrent;		//读回来的实际电流
	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
	int16_t targetSpeed;			//目标速度
	uint16_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	incrementalpid_t pid;		//电机pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
	
}M3508s_t;

typedef struct{
//	uint16_t motorInfoID;		//该电机读数据的CAN ID
	uint16_t realAngle;			//读回来的机械角度
	int32_t totalAngle;			//累积总共角度
//	int16_t realSpeed;			//读回来的速度
	int16_t realCurrent;		//读回来的实际电流
//	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
//	int16_t targetSpeed;			//目标速度
	int32_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	uint16_t lastAngle;			//上次的角度
	int16_t turnCount;			//转过的圈数
	incrementalpid_t pid_speed;		//电机速度pid
	positionpid_t pid_angle;		//角度电机pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
}M6623s_t;

typedef struct{
//	uint16_t motorInfoID;		//该电机读数据的CAN ID
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realTorque;			//读回来的实际转矩
	uint16_t lastAngle;			//上次的角度
	int32_t totalAngle;			//累积总共角度
	int16_t turnCount;			//转过的圈数
//	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
	int16_t targetSpeed;			//目标速度
	int32_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	incrementalpid_t pid_speed;		//电机速度pid
	positionpid_t pid_angle;		//电机角度pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint8_t loadFinish;			//子弹加载完毕
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
}M2006s_t;

typedef struct{
	uint16_t KeyStatus;
	uint16_t lastKeyStatus;
	uint16_t keyPressedJump;
	uint16_t keyReleaseJump;
	uint16_t longPressed;
	uint16_t timer;
}key_t;

typedef struct {
	struct{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;

		uint8_t s_left;
		uint8_t s_right;
	}rc;
	
	struct{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t keyLeft;
		uint8_t keyRight;
		
	}mouse;
	
	union {
		uint16_t key_code;
		struct{
			bool press_W:1;
			bool press_S:1;
			bool press_A:1;
			bool press_D:1;
			bool press_Shift:1;
			bool press_Ctrl:1;
			bool press_Q:1;
			bool press_E:1;
			
			bool press_R:1;
			bool press_F:1;
			bool press_G:1;
			bool press_Z:1;
			bool press_X:1;
			bool press_C:1;
			bool press_V:1;
			bool press_B:1;
		};
	}keyBoard;
	
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
}DR16_DBUS_DATA_t;






typedef struct {
	float x;
	float y;
	float radian;
	float degrees;
	float distance;
}rocker_t;


typedef struct {
		float w;
		float x;
		float y;
		float z;
}quaternion_t;

typedef struct {
		float x;
		float y;
		float z;
}vector_t;

typedef struct {
		int16_t x;
		int16_t y;
		int16_t z;
}vector16_t;

typedef struct {
	float roll;
	float pitch;
	float yaw;
}eular_t;

typedef struct{
	vector_t gyro;
	eular_t eular;
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t devStatus;
	uint8_t infoUpdateFlag;
	uint16_t infoUpdateFrame;
	uint8_t offLineFlag;
}GY_IMU_t;



#endif /* __TYPEDEFS_H */
