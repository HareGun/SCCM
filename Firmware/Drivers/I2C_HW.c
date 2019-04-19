/**
  ******************************************************************************
  * @file    I2C_SW.c
  * @author  Hare
  * @version V1.1
  * @date    
  * @brief   硬件I2C应用函数接口
  ******************************************************************************
  */

#include "I2C_HW.h"
#include <stdio.h>
#include <string.h>
#include "GPIO.h"

#define I2C_WR_ADDR		0		/* 写地址（原7位地址<<1|WR）*/
#define I2C_RD_ADDR		1		/* 写地址（原7位地址<<1|RD）*/

/* 等待超时时间 */
#define I2C_HW_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_HW_LONG_TIMEOUT         ((uint32_t)(10 * I2C_HW_FLAG_TIMEOUT))

static __IO uint32_t  I2CTimeout = I2C_HW_LONG_TIMEOUT;   

static void I2C1_HW_BusyUnlock(void);
static uint32_t I2C_TIMEOUT_UserCallback(I2C_TypeDef* I2Cx, uint8_t errorCode);

/**
  * @brief  用作模拟I2C产生时钟信号的延时
  *	@details 	可用逻辑分析仪测量I2C通讯时的频率
  *				工作条件：CPU主频72MHz ，MDK编译环境，0级优化
  *       循环次数    SCL频率
  *           5       421Khz
  * @param  None
  * @retval None
  */
static void I2C_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 5; i++){
  }
}


/**
  * @brief  I2C I/O配置
  * @param  无
  * @retval 无
  */
static void I2C1_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C 有关的时钟 */
	I2C1_APBxClock_CMD(I2C1_CLK, ENABLE);
	I2C1_GPIO_APBxClock_CMD(I2C1_GPIO_CLK, ENABLE);
	
    
  /* I2C_SCL、I2C_SDA */
  GPIO_InitStructure.GPIO_Pin = I2C1_HW_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       /* 开漏输出 */
  GPIO_Init(I2C1_HW_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = I2C1_HW_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       /* 开漏输出 */
  GPIO_Init(I2C1_HW_SDA_PORT, &GPIO_InitStructure);	
  
}


/**
  * @brief  I2C 工作模式配置
  * @param  无
  * @retval 无
  */
static void I2C1_Mode_Config(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C 配置 */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2C1_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	 
	/* I2C的寻址模式 */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* 通信速率 */
  I2C_InitStructure.I2C_ClockSpeed = I2C1_Speed;
  
	/* I2C 初始化 */
  I2C_Init(I2C1, &I2C_InitStructure);
  
	/* 使能 I2C */
  I2C_Cmd(I2C1, ENABLE);   
}


/**
  * @brief  I2C 外设(EEPROM)初始化
  * @param  无
  * @retval 无
  */
void I2C1_HW_Init(void)
{
  I2C1_GPIO_Config(); 
  I2C1_Mode_Config();
}


/**
  * @brief  向I2C设备读多个数据
  * @param  I2Cx      I2Cx
  *         D_Address 设备地址
  *			    R_Address	设备寄存器地址
  *			    len 		  数据长度
  *		    	data_buf 	数据数组
  * @retval 成功返回1，失败返回0
  */
uint8_t I2C_HW_writeBuff(I2C_TypeDef* I2Cx, uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf)
{
   /* Send STRAT condition */
  I2C_GenerateSTART(I2Cx, ENABLE);

  I2CTimeout = I2C_HW_FLAG_TIMEOUT;  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 0);
  } 
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2Cx, D_Address<<1, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 1);
  }  
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2Cx, R_Address);
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 2);
  } 
  
  /* Send the byte to be written */
  for(uint16_t i = 0; i<len; i++){
    I2C_SendData(I2Cx, data_buf[i]);
    
    I2CTimeout = I2C_HW_FLAG_TIMEOUT;  
    /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 3);
    }
  }
  
  /* Send STOP condition */
  I2C_GenerateSTOP(I2Cx, ENABLE);
  
  return 1;
}

/**
  * @brief  向I2C设备读多个数据
  * @param  D_Address 	设备地址
  *		    	R_Address	设备寄存器地址
  *		    	len 		  数据长度
  *		    	data_buf 	数据数组
  * @retval 成功返回1，失败返回0
  */
uint8_t I2C_HW_readBuff(I2C_TypeDef* I2Cx, uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf)
{
  I2CTimeout = I2C_HW_LONG_TIMEOUT;
  uint16_t i = 0;
  
  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
  { 
    if((I2CTimeout--) == 0){
      I2C1_HW_BusyUnlock();
      return I2C_TIMEOUT_UserCallback(I2Cx, 9);
    }
  }
  
  /* Send START condition */
  I2C_GenerateSTART(I2Cx, ENABLE);
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0){
      return I2C_TIMEOUT_UserCallback(I2Cx, 10);
    }      
  }
  
  /* Send Devices address for write */
  I2C_Send7bitAddress(I2Cx, D_Address<<1, I2C_Direction_Transmitter);

  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 11);
  }
    
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2Cx, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2Cx, R_Address);  

   
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 12);
  }
    
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2Cx, ENABLE);
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 13);
  }
    
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2Cx, D_Address<<1, I2C_Direction_Receiver);
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 14);
  }
  
  /* While there is data to be read */
  while(len)  
  {
    if(len == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2Cx, DISABLE);
      /* Send STOP condition */
      I2C_GenerateSTOP(I2Cx, ENABLE);
    }
    
    I2CTimeout = I2C_HW_LONG_TIMEOUT;
    /* Test on EV7 and clear it */   
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
		{
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 15);
		} 
    
    data_buf[i] = I2C_ReceiveData(I2Cx);

    /* Point to the next location where the byte read will be saved */
    i++;  
    /* Decrement the read bytes counter */
    len--;        
  }   
  
  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
  
  return 1;
}

/**
  * @brief  检查设备是否存在
  * @param  D_Address 	设备地址
  * @retval 返回1表示设备正常，返回0表示找不到设备
  */
uint8_t I2C_HW_checkDevice(I2C_TypeDef* I2Cx, uint8_t D_Address)
{

	//I2C_GenerateSTOP(I2Cx, ENABLE); /*发送停止信号，复位所有I2C设备*/
	  
  /* Send STRAT condition */
  I2C_GenerateSTART(I2Cx, ENABLE);

  I2CTimeout = I2C_HW_FLAG_TIMEOUT;  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 80);
  } 
  
  I2CTimeout = I2C_HW_FLAG_TIMEOUT;
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2Cx, D_Address<<1, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(I2Cx, 81);
  }  

	I2C_GenerateSTOP(I2Cx, ENABLE); /* 发送结束信号  */

	return 1;
}


/**
  * @brief  用于解除I2C BUSY
  * @param  I2Cx
  * @retval None
  */
static void I2C1_HW_BusyUnlock(void)
{
  GPIO_QuickInit(I2C1_GPIO_CLK, I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN, GPIO_Mode_Out_OD);    /* 通用开漏输出 */
  GPIO_SetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);          /* I2C SCL = 1 */

  I2CTimeout = I2C_HW_LONG_TIMEOUT;
  /* 检测I2C SDA为高电平 */
  while((!GPIO_ReadOutputDataBit(I2C1_HW_SDA_PORT, I2C1_HW_SDA_PIN)) && (I2CTimeout != 0)) {
      GPIO_ResetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);     /* I2C SCL = 0 */
      I2C_Delay();        
      GPIO_SetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);       /* I2C SCL = 1 */
      I2C_Delay();      
      /* 修复总线超时处理 */
      if((--I2CTimeout) == 0) {
          I2C_TIMEOUT_UserCallback(I2C1, 66);
      }
  }
  GPIO_ResetBits(I2C1_HW_SDA_PORT, I2C1_HW_SDA_PIN);         /* I2C SDA = 0 */
  GPIO_QuickInit(I2C1_GPIO_CLK, I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN, GPIO_Mode_AF_OD);    /* 复用开漏输出 */
  I2C_SoftwareResetCmd(I2C1, ENABLE);
  I2C_SoftwareResetCmd(I2C1, DISABLE);
}


/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示IIC读取失败.
  */
static uint32_t I2C_TIMEOUT_UserCallback(I2C_TypeDef* I2Cx, uint8_t errorCode)
{
  I2C_GenerateSTOP(I2Cx, ENABLE); /*发送停止信号，复位所有I2C设备*/
  /* Block communication and all processes */
	printf("I2C HW Timeout ErrorCode = %d\r\n",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/

