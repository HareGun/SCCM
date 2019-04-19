#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stdbool.h>
#include <stdint.h>

/* 允许匿名共用体 */
#pragma anon_unions


typedef struct{
	float target;            /* 设定目标值 */
	float measured;          /* 测量值 */
	float err;               /* 本次偏差值 */
	float err_last;          /* 上一次偏差 */
	float err_beforeLast;    /* 上上次偏差 */
	float Kp, Ki, Kd;        /* Kp, Ki, Kd控制系数 */
	float out;               /* pwm输出 */
	uint32_t maxOutput;      /* 输出限幅 */
  uint32_t integralLimit;  /* 积分限幅 */
}incrementalpid_t;

typedef struct{
	float target;            /* 设定目标值 */
	float measured;          /* 测量值 */
	float err;               /* 本次偏差值 */
	float err_last;          /* 上一次偏差 */
	float integral_err;      /* 所有偏差之和 */
	float Kp, Ki, Kd;        /* Kp, Ki, Kd控制系数 */
	float out;               /* pwm输出 */
	uint32_t maxOutput;      /* 输出限幅 */
  uint32_t integralLimit;  /* 积分限幅 */
}positionpid_t; 






typedef struct{
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
	positionpid_t pid_speed;		//电机速度pid
	positionpid_t pid_angle;		//电机角度pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint8_t loadFinish;			//子弹加载完毕
	uint16_t infoUpdateFrame;	//帧率
	uint8_t offLineFlag;		//设备离线标志
}M2006s_t;

typedef struct{
	uint8_t shootFlag;			//射击标志
	uint8_t fricReady;			//摩擦轮准备标志
	uint8_t fricSpeedLevel;			//摩擦轮速度等级
	uint16_t fricTargetSpeedRaw;	//摩擦轮目标速度
	uint8_t heatOverflowFlag;	//射击超热量标标志
	uint8_t shootReady;			//射击准备标志
	uint8_t shootFreq;			//射击频率
	uint8_t timeCount;			//时间计数
}shootGun_t;





typedef struct{
	int32_t calibrationPosArray[2][3];
	int32_t BigSymbol_positionArray[2][9];
	uint8_t calibrationStep;
	uint8_t calibrationFinish;
	uint8_t targetPosition;
	uint8_t targetInfoUpdate;
}BigSymbol_t;










typedef struct{
  union{
    uint8_t data;
    struct{
      uint8_t KeyStatus:1;
      uint8_t lastKeyStatus:1;
      uint8_t keyPressedJump:1;
      uint8_t keyReleaseJump:1;
      uint8_t longPressed:1;
    };
  }flag;
	uint16_t timeCounter;
}key_t;

typedef struct{
  uint16_t KeyStatus;
  uint16_t lastKeyStatus;
  uint16_t keyPressedJump;
  uint16_t keyReleaseJump;
  uint16_t longPressed;
	uint16_t timeCounter[16];
}keyBoard_t;

typedef struct {
	struct{
		int16_t ch0_RX;
		int16_t ch1_RY;
		int16_t ch2_LX;
		int16_t ch3_LY;

		uint8_t s_left;
		uint8_t s_right;
    
    int16_t ch4_DW; /* 拨轮 */
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
	union {
		uint8_t dataBuff[8];
		struct{
			float chassisVolt;
			float chassisCurrent;
			float chassisPower;
			float chassisPowerBuffer; 
		};
	}data;
	uint8_t infoUpdateFlag;
	uint8_t infoUpdateFrame;
	uint8_t offLineFlag;		//设备离线标志
}GalvanometerData_t;


typedef struct{
  int32_t count;
  int32_t scale;
  float   out;
}ramp_t;

typedef enum
{
		enable					=0x01,//表示是否是使能充电
		unenable				,	//表示不使能充电芯片			
		cap_supply			,//表示超级电容供电，默认是电源供电
		battery_supply  ,//电池给底盘供电
		_2A_current			,//表示启用2A电流对超级电容充电
		_05A_current		,//表示启用0.5A电流对超级电容充电
		under_voltage		,//表示超级电容电压低于78%
		charge_complete ,//表示超级电容电压高于96%
		unenable_cap		, //超级电容失效不使用超级电容模块
		enable_cap        //启用超级电容模块
}Sup_Cap_State;


typedef union {
	uint8_t stateData;
	struct{
		bool chipEnable : 1;		//使能充电芯片引脚
		bool capVLow : 1;			//低压引脚
		bool capFull : 1;			//满电检测引脚
		bool currSet : 1;			//电流设置引脚
		bool supplySW : 1;			//供电切换引脚
		uint8_t NC : 3;	
	};
}SupCapState_t;

//typedef struct{
//  float LpfAttFactor;
//  float in;
//  float out;
//}IIRLPF_t;



#endif /* __TYPEDEFS_H */
