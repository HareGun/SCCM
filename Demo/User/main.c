/*


*/

#include "userCode.h"

//RCC_ClocksTypeDef RCC_Clocks;

uint8_t buf[2048];

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);             /* 初始化Systick */
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);   /* 优先级分组4 （抢占式16）使用os不要分组 */
  
  /* 配置通道 0，上行配置*/
  SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  /* 配置通道 0，下行配置*/ 
  SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  
//  SEGGER_RTT_ConfigUpBuffer(1, "JScope_u2", buf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  
  SEGGER_RTT_SetTerminal(0);
  
	/* 创建系统初始化任务 */
	xTaskCreate(vTaskSystemInit,    /* 任务函数 */
              "Task SysInit",     /* 任务名 */
              512,                /* 任务栈大小，单位字 */
              NULL,               /* 任务形参 */
              5,                  /* 任务优先级，值越大优先级越高 */
              NULL);  		        /* 任务句柄 */
	
	/* 开始任务调度，成功则不返回 */
	vTaskStartScheduler();
	
	//用os后不会执行到这里
	while(1)
  {
    
	}
  
	return 0;
}

