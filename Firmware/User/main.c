/*

*/

#include "user_common.h"
#include "SystemInit_Tasks.h"



#define BNO_CAN_SEND_ID   0x413
#define BNO_UART_PACKAGE_LENGTH 18



#define ST_SAVE_DATA_PAGE     62
#define ST_SAVE_DATA_OFFSET   0
#define ST_SAVE_DATA_LEN      8
#define ST_SAVE_ID            0x49

typedef union{
  struct{
    /* 标志位 */
    union{
      struct{
        uint8_t saveID;        /* 用于指示是否有存储过数据，默认0x49 */
        bool calibrated:1;     /* 传感器已校准 */
      };
      uint32_t flagData;          
    }flag;                  //1*u32
    
    uint32_t can_id;        /* CAN ID 1*u32 */
    
    uint8_t calibData[24];  /* 校准数据，仅前22个 6*u32 */
  };
  uint32_t dataBuff[ST_SAVE_DATA_LEN];
}st_savedData_u;

st_savedData_u st_savedData;

void st_saveDefaultData(void){
  st_savedData_u temp_savedData;
  /* 清空数据*/
  memset(&temp_savedData, 0, sizeof(st_savedData_u));
  
  temp_savedData.flag.saveID = ST_SAVE_ID;
  temp_savedData.flag.calibrated = 0;
  temp_savedData.can_id = BNO_CAN_SEND_ID;
  
  FLASH_Erase(ST_SAVE_DATA_PAGE);
  Flash_write32Buff(ST_SAVE_DATA_PAGE, ST_SAVE_DATA_OFFSET, temp_savedData.dataBuff, ST_SAVE_DATA_LEN);
}

void st_writeSavedData(uint32_t *dataBuff){
  FLASH_Erase(ST_SAVE_DATA_PAGE);
  Flash_write32Buff(ST_SAVE_DATA_PAGE, ST_SAVE_DATA_OFFSET, dataBuff, ST_SAVE_DATA_LEN);
}

void st_readSavedData(uint32_t *dataBuff){
  Flash_read32Buff(ST_SAVE_DATA_PAGE, ST_SAVE_DATA_OFFSET, dataBuff, ST_SAVE_DATA_LEN);
}




RCC_ClocksTypeDef RCC_Clocks;

int main(void){
	
	/* 优先级分组4 （抢占式16）使用os不要分组 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  /* SYSTICK初始化 */
  SysTick_Config(SystemCoreClock/1000);
  delay_init();
  
  //创建系统初始化任务
	xTaskCreate(vTaskSystemInit,   /* 任务函数 */
				"Task SysInit",    /* 任务名 */
				 512,              /* 任务栈大小，单位字 */
				 NULL,             /*  任务形参 */
				 5,                /* 任务优先级，值越大优先级越高 */
				 NULL);  		   /* 任务句柄 */
	
	/* 开始任务调度，成功则不返回 */
	vTaskStartScheduler();
  
  while(1){
  

  }
	
	return 0;
}
