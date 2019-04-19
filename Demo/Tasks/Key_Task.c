/**
  ******************************************************************************
  * @file    Key_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   用户按键任务
  ******************************************************************************
  */
  
  
#include "Key_Task.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskUserKey = NULL;
TaskHandle_t xHandleTaskIDSet = NULL;
uint32_t counter = 0;

void vTaskIDSet(void *pvParameters);

/**
  * @brief  用户按键任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskUserKey(void *pvParameters)
{
	TickType_t xLastWakeTime;
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{	
		Key_Process();
		xEventGroupSetBits(xCreatedEventGroup, EventBit_KeyUpdate);
		
		if(userKeyList[0].longPressed){
			LED_GREEN(0);
			
			xEventGroupClearBits(xCreatedEventGroup, EventBit_DataOut);
			xEventGroupSetBits(xCreatedEventGroup, EventBit_SetID);
			//printf("set id\r\n");
			
		}
		
//		static int uuu = 0;
//		if(userKeyList[0].keyPressedJump){
//			printf("K1 按下\r\n");
//			uuu  = !uuu;
//			if(uuu){
//				xEventGroupSetBits(xCreatedEventGroup, EventBit_DataOut);
//			}
//			else{
//				xEventGroupClearBits(xCreatedEventGroup, EventBit_DataOut);
//			}
//			
//		}
		
		vTaskDelayUntil(&xLastWakeTime, 10);
	}	
}
uint8_t id_temp = 0;

#define SETID_TIMES 3000	//3秒后确定id
/**
  * @brief  ID设置任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskIDSet(void *pvParameters)
{
	EventBits_t uxBits;
	TickType_t xLastWakeTime;
	
	/* 获取当前的系统时间 */
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{	
		uxBits = xEventGroupWaitBits(xCreatedEventGroup, 	/* 事件标志组句柄 */
							EventBit_SetID | EventBit_KeyUpdate, 	/* 事件标志位被设置 */
							pdFALSE, 				/* 选择是否清零被置位的事件标志位 */
							pdTRUE, 				/* 选择是否等待所有标志位都被设置 */
							portMAX_DELAY);			/* 等待延迟时间 */
		
		if((uxBits & (EventBit_SetID | EventBit_KeyUpdate)) == (EventBit_SetID | EventBit_KeyUpdate)){
			
			
			xEventGroupClearBits(xCreatedEventGroup, EventBit_KeyUpdate);
		}
		//vTaskDelayUntil(&xLastWakeTime, 10);
	}	
}

