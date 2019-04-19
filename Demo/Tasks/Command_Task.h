#ifndef __COMMAND_TASK_H
#define __COMMAND_TASK_H

#include "user_common.h"


#define EVENTBIT_0	(1<<0)				//事件位
#define EVENTBIT_1	(1<<1)
#define EVENTBIT_2	(1<<2)

#define EventBit_keyupdate		EVENTBIT_0

 
typedef enum{
	Control_ByRC = 3,
	Control_ByPC = 1,
	Control_OFF = 2,
  Control_LOCK = 4,
}ControlBy_e;
 
typedef enum{
	SpecialMode_Normal = 0,
  SpecialMode_StandBy = 1,	/* 准备运动模式 */
	SpecialMode_Climbing_Up = 2,	/* 上岛模式 */
  SpecialMode_Climbing_Down = 3,	/* 下岛模式 */
	SpecialMode_Supply = 4, 	/* 取弹模式 */
  SpecialMode_Give = 5, 	/* 交接模式 */
}SpecialMode_e;


typedef struct{
	ControlBy_e Controlby;			//控制方式
	SpecialMode_e SpecialMode;			//特殊模式
	uint8_t isCombineKey;			//使用组合键
}ControlStatus_t;

extern TaskHandle_t xHandleTaskCommand;
extern EventGroupHandle_t xCommandEventGroup;
extern ControlStatus_t ControlStatus;


void vTaskCommand(void *pvParameters);

#endif /* __KEY_TASK_H */
