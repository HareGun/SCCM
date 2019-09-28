/**
  ******************************************************************************
  * @file    Monitor_Task.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   监控任务
  ******************************************************************************
  */
  
  
#include "Monitor_Task.h"
#include "LED.h"
#include "Measurement.h"
#include "Control_Task.h"
#include "BQ24640.h"

/* 任务句柄，任务创建之后得到对应值，以后想操作这个任务时都需要通过这个句柄来操作 */
TaskHandle_t xHandleTaskMonitor = NULL;

monitor_t monitor;

/* 格式：序列长度-序列间隔-序列... */
const uint8_t LEDSTAT_FlashSeq[5][20] = {
  {4,0,0,1,1,0},          /* 一直闪 */
  {8,10,0,1,1,0,0,1,1,0},  /* 快闪2下 */
  {12,10,0,1,1,0,0,1,1,0,0,1,1,0},  /* 快闪3下 */
  {16,10,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0}  /* 快闪4下 */
};

typedef struct{
  uint16_t timeCounter; /* 时间计数器 */
  uint8_t step;         /* 步骤计数器 */
  uint8_t SeqNum;      /* 序列编号 */
}ledFlash_t;

ledFlash_t LEDSTAT_Flash;

/**
  * @brief  状态灯闪烁
  * @param  count 闪烁次数，每隔1s重复
  * @retval None
  */
void LED_STAT_FLASH(void){
  LEDSTAT_Flash.step++;
  LED_STA1(LEDSTAT_FlashSeq[LEDSTAT_Flash.SeqNum][LEDSTAT_Flash.step + 1]);
  if(LEDSTAT_Flash.step > LEDSTAT_FlashSeq[LEDSTAT_Flash.SeqNum][0]){
    LEDSTAT_Flash.step = LEDSTAT_FlashSeq[LEDSTAT_Flash.SeqNum][0] - 1;
    if(LEDSTAT_Flash.timeCounter++ > LEDSTAT_FlashSeq[LEDSTAT_Flash.SeqNum][1]){
      LEDSTAT_Flash.step = 0;
      LEDSTAT_Flash.timeCounter = 0;
    }
  }
}

/**
  * @brief  监控任务
  * @param  pvParameters 任务被创建时传进来的参数
  * @retval None
  */
void vTaskMonitor(void *pvParameters)
{
  uint8_t loopCounter_100ms = 0;
  uint8_t loopCounter_50ms = 0;
  LEDSTAT_Flash.SeqNum = 0;
	LED_Init();
  
  while(!monitor.sys_ready){
    Control_setMode(CONTROL_OFF);
    
    LED_STA1_TOGGLE();
    LED_MODE_TOGGLE();
    LED_CAPLOW_TOGGLE();
    LED_CAPFULL_TOGGLE();
    
    if(BQ_GET_STAT_PIN() && BQ_GET_PG_PIN()){
      monitor.sys_ready = 1;
    }
    vTaskDelay(50);
  }
  
	while(1)
	{
    loopCounter_100ms++;
    loopCounter_50ms++;
    
    if(loopCounter_100ms++ > 9){
      /* 主机离线检测 */
      if(monitor.master_frameCounter < 2){
        monitor.master_timeOutCounter++;
        if(monitor.master_timeOutCounter > 20){
          monitor.master_offLineFlag = 1;
          monitor.master_timeOutCounter = 0;
          /* 离线停止输出 */
          if(control.boostError){
            /* 升压错误且离线 */
            LEDSTAT_Flash.SeqNum = 2;
          }
          else{
            LEDSTAT_Flash.SeqNum = 0;
          }          
          Control_setMode(CONTROL_OFF);
        }
      }
      else{
        monitor.master_offLineFlag = 0;
        monitor.master_timeOutCounter = 0;
        
        Control_setMode(CONTROL_NORMAL);
        if(control.boostError){
          /* 升压错误且在线 */
          LEDSTAT_Flash.SeqNum = 3;
        }
        else{
          LEDSTAT_Flash.SeqNum = 1;
        } 
      }
      monitor.master_frameCounter = 0;
      loopCounter_100ms = 0;
    }
    
    if(loopCounter_50ms > 4){
      LED_STAT_FLASH();
      loopCounter_50ms = 0;
    }
    
    LED_MODE(control.isCapOutput);
    
    switch(measurement.cap_status){
      case CAP_STAT_LOW:
        LED_CAPFULL(0);
        LED_CAPLOW(1);
      break;
      case CAP_STAT_MID:
        LED_CAPFULL(1);
        LED_CAPLOW(1);
      break;
      case CAP_STAT_FULL:
        LED_CAPFULL(1);
        LED_CAPLOW(0);
      break;
      default:
        
      break;
    }
    
    
    
    
    vTaskDelay(10);
			
		
	}	
}

