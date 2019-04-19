/**
  ******************************************************************************
  * @file    I2C_HW.c
  * @author  Hare
  * @version V1.1
  * @date    
  * @brief   硬件I2C应用函数接口
  *			 2018-01-27 修复I2C读函数返回值错误导致DMP初始化失败的问题
  ******************************************************************************
  */

#include "I2C_HW.h"

static I2C_TypeDef* I2C_using = I2C2;

static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT; 
static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);


/**
  * @brief  硬件I2C GPIO初始化
  * @param  None
  * @retval None
  */
static void I2C2_GPIOInit(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure; 

	/*!< I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	/*!< I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_AHB1PeriphClockCmd(I2C2_HW_SCL_GPIO_CLK | I2C2_HW_SDA_GPIO_CLK, ENABLE);

	/*!< GPIO configuration */
	/* Connect PXx to I2C_SCL*/
	GPIO_PinAFConfig(I2C2_HW_SCL_GPIO_PORT, I2C2_HW_SCL_PINSOURCE, GPIO_AF_I2C2);
	/* Connect PXx to I2C_SDA*/
	GPIO_PinAFConfig(I2C2_HW_SDA_GPIO_PORT, I2C2_HW_SDA_PINSOURCE, GPIO_AF_I2C2);  

	/*!< Configure EEPROM_I2C pins: SCL */   

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = I2C2_HW_SCL_Pin;
	GPIO_Init(I2C2_HW_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure EEPROM_I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C2_HW_SDA_Pin;
	GPIO_Init(I2C2_HW_SDA_GPIO_PORT, &GPIO_InitStructure);
 
}

/**
  * @brief  硬件I2C2初始化
  * @param  None
  * @retval None
  */
void I2C2_HW_Init(void)
{
	I2C2_GPIOInit();
	I2C_InitTypeDef  I2C_InitStructure; 

	/* I2C 配置 */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;	
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		                    /* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
	I2C_InitStructure.I2C_OwnAddress1 =I2C2_OWN_ADDRESS7; 
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;	
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* I2C的寻址模式 */
	I2C_InitStructure.I2C_ClockSpeed = I2C2_Speed;	                            /* 通信速率 */
	I2C_Init(I2C2, &I2C_InitStructure);	                                      /* I2C2 初始化 */
	I2C_Cmd(I2C2, ENABLE);  	                                                /* 使能 I2C2 */

	I2C_AcknowledgeConfig(I2C2, ENABLE);  
}



/**
  * @brief  检查设备是否存在
  * @param  D_Address 	设备地址
  * @retval 返回1表示设备正常，返回0表示找不到设备
  */
uint8_t I2C_CheckDevice(uint8_t D_Address){
	uint8_t ucAck;

	I2C_GenerateSTOP(I2C_using, ENABLE);	/*发送停止信号，复位所有I2C设备*/
	
	I2C_GenerateSTART(I2C_using, ENABLE);;		/* 发送起始信号 */

	I2C_Send7bitAddress(I2C_using, D_Address, I2C_Direction_Transmitter);/* 发送写地址 */
	ucAck = I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	/* 等待设备响应 */

	I2C_GenerateSTOP(I2C_using, ENABLE); 			/* 发送结束信号  */

	return ucAck;
}


/**
  * @brief  向I2C设备写多个数据
  * @param  D_Address 	设备地址
  *			R_Address	设备寄存器地址
  *			len 		数据长度
  *			data_buf 	数据数组
  * @retval 成功返回0，失败返回1
  */
uint8_t I2C_WriteBuff(uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf){
	
	//1,发送起始信号
	I2C_GenerateSTART(I2C_using, ENABLE);;
	
	/* 检测 EV5 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_MODE_SELECT)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
	} 
	
	//2,发送7位设备地址+写方向
	I2C_Send7bitAddress(I2C_using, D_Address << 1, I2C_Direction_Transmitter);
	
	/*3. 检测 EV6 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
	} 
	
	//4，发送寄存器地址
	I2C_SendData(I2C_using, R_Address);

	/*5. 检测 EV8 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_BYTE_TRANSMITTED))  
	{
	if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
	} 
	
	for (uint16_t i=0;i<len;i++){
		//6,发送一个数据
		I2C_SendData(I2C_using, data_buf[i]);
	
		/*7. 检测 EV8 事件并清除标志 */
		I2CTimeout = I2CT_FLAG_TIMEOUT;
		while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
		} 
	 
	}
	
	/* 8,发送结束信号  */
	I2C_GenerateSTOP(I2C_using, ENABLE);
	
	return 0;
}


/**
  * @brief  向I2C设备读多个数据
  * @param  D_Address 	设备地址
  *			R_Address	设备寄存器地址
  *			len 		数据长度
  *			data_buf 	数据数组
  * @retval 成功返回1，失败返回0
  */
uint8_t I2C_ReadBuff(uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf)
{
	uint8_t i = 0;
	
	/* 检测I2C是否忙 */
	I2CTimeout = I2CT_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(I2C_using, I2C_FLAG_BUSY))   {
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
    }
	
	//发送起始信号
	I2C_GenerateSTART(I2C_using, ENABLE);
		
	/* 检测 EV5 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_MODE_SELECT)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
	} 

	//发送7位设备地址+写方向
	I2C_Send7bitAddress(I2C_using, D_Address << 1, I2C_Direction_Transmitter);
	
	//检测EV6事件
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
	} 
	/* Clear EV6 by setting again the PE bit */
	I2C_Cmd(I2C_using, ENABLE);

	//发送寄存器地址
	I2C_SendData(I2C_using, R_Address);
	    
	/* 检测EV8_2事件并清除 */ 
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
	if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
	}
	
	//发送启动信号，重新启动I2C总线，开始接收数据
	I2C_GenerateSTART(I2C_using, ENABLE);
	
	/* 检测 EV5 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_MODE_SELECT)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
	}
	
	//发送7位设备地址+读方向
	I2C_Send7bitAddress(I2C_using, D_Address << 1, I2C_Direction_Receiver);
	
	/* 检测 EV6 事件并清除标志 */
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(!I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
	}
	
	//开始接收len个数据
	while(len){
		
		if(len == 1){
			//当为最后一个数据时产生非应答信号并发送停止信号
			I2C_AcknowledgeConfig(I2C_using, DISABLE);
			I2C_GenerateSTOP(I2C_using, ENABLE);
		}
		
		I2CTimeout = I2CT_LONG_TIMEOUT;
		while(I2C_CheckEvent(I2C_using, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  {
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(15);
		} 
		
		data_buf[i] = I2C_ReceiveData(I2C_using);
		
		i++;
		len--;
	}
	
	/* Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig(I2C_using, ENABLE);
	
	return 0;
}

uint8_t I2C_writeRegister8(uint8_t D_Address, uint8_t R_Address, uint8_t data){
    return I2C_WriteBuff(D_Address, R_Address, 1, &data);
}

// Read 8-bit from register
uint8_t I2C_readRegister8(uint8_t D_Address, uint8_t R_Address){
	uint8_t data;
    if(!I2C_ReadBuff(D_Address, R_Address, 1, &data))
		return data;
	else 
		return 0;
}

int16_t I2C_readRegister16(uint8_t D_Address, uint8_t R_Address){
    int16_t value;
	uint8_t data[2];
	if(!I2C_ReadBuff(D_Address, R_Address, 2, data)){
		value = data[0] << 8 | data[1];
		return value;
	}
	else 
		return 0;
}

uint8_t I2C_writeRegister16(uint8_t D_Address, uint8_t R_Address, int16_t value){
	uint8_t data[2];
	data[0] = (uint8_t)(value >> 8);
	data[1] = (uint8_t)value;
	
	return I2C_WriteBuff(D_Address, R_Address, 2, data);
}

// Read register bit
bool I2C_readRegisterBit(uint8_t D_Address, uint8_t R_Address, uint8_t pos){
    uint8_t value;
		value =  I2C_readRegister8(D_Address, R_Address);
    return ((value >> pos) & 1);
}

// Write register bit
uint8_t I2C_writeRegisterBit(uint8_t D_Address, uint8_t R_Address, uint8_t pos, bool state){
    uint8_t value;
    value = I2C_readRegister8(D_Address, R_Address);

    if (state){
        value |= (1 << pos);
    }
		else {
        value &= ~(1 << pos);
    }

	return I2C_writeRegister8(D_Address, R_Address, value);
}


/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode:打印错误代码.
  * @retval 返回0,表示IIC读取失败.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
	//I2C_GenerateSTOP(I2C_using, ENABLE);	/*发送停止信号，复位所有I2C设备*/
  /* Block communication and all processes */
	//setPos(0,0);
	printf("I2C Timeout ErrorCode = %d\n",errorCode);
	return 1;
}

/*========MPU6050 DMP库支持================================================================================================*/

static unsigned short RETRY_IN_MLSEC  = 55;

/**
  * @brief  设置iic重试时间
  * @param  ml_sec：重试的时间，单位毫秒
  * @retval 重试的时间，单位毫秒
  */
void Set_I2C_Retry(unsigned short ml_sec)
{
  RETRY_IN_MLSEC = ml_sec;
}

/**
  * @brief  获取设置的iic重试时间
  * @param  none
  * @retval none
  */
unsigned short Get_I2C_Retry(void)
{
  return RETRY_IN_MLSEC;
}

int Sensors_I2C_WriteRegister(unsigned char slave_addr,
                                        unsigned char reg_addr,
                                        unsigned short len,
                                        const unsigned char *data_ptr)
{
  char retries=0;
  int ret = 0;
  unsigned short retry_in_mlsec = Get_I2C_Retry();

tryWriteAgain:
  ret = 0;
  ret = I2C_WriteBuff( slave_addr, reg_addr, len, ( unsigned char *)data_ptr);

  if(ret && retry_in_mlsec)
  {
    if( retries++ > 4 )
        return ret;

    delay_ms(retry_in_mlsec);
    goto tryWriteAgain;
  }
  return ret;
}


/**
  * @brief  向IIC设备的寄存器连续读出数据,带超时重试设置，供mpu接口调用
  * @param  Address: IIC设备地址
  * @param  RegisterAddr: 寄存器地址
  * @param  RegisterLen: 要读取的数据长度
  * @param  RegisterValue: 指向存储读出数据的指针
  * @retval 0正常，非0异常
  */
int Sensors_I2C_ReadRegister(unsigned char slave_addr,
                                       unsigned char reg_addr,
                                       unsigned short len,
                                       unsigned char *data_ptr)
{
  char retries=0;
  int ret = 0;
  unsigned short retry_in_mlsec = Get_I2C_Retry();

tryReadAgain:
  ret = 0;
  ret = I2C_ReadBuff( slave_addr, reg_addr, len, ( unsigned char *)data_ptr);

  if(ret && retry_in_mlsec)
  {
    if( retries++ > 4 )
        return ret;

    delay_ms(retry_in_mlsec);
    goto tryReadAgain;
  }
  return ret;
}

