/**
  ******************************************************************************
  * @file    I2C_SW.c
  * @author  Hare
  * @version V1.1
  * @date    
  * @brief   Ӳ��I2CӦ�ú����ӿ�
  ******************************************************************************
  */

#include "I2C_HW.h"
#include <stdio.h>
#include <string.h>
#include "GPIO.h"

#define I2C_WR_ADDR		0		/* д��ַ��ԭ7λ��ַ<<1|WR��*/
#define I2C_RD_ADDR		1		/* д��ַ��ԭ7λ��ַ<<1|RD��*/

/* �ȴ���ʱʱ�� */
#define I2C_HW_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_HW_LONG_TIMEOUT         ((uint32_t)(10 * I2C_HW_FLAG_TIMEOUT))

static __IO uint32_t  I2CTimeout = I2C_HW_LONG_TIMEOUT;   

static void I2C1_HW_BusyUnlock(void);
static uint32_t I2C_TIMEOUT_UserCallback(I2C_TypeDef* I2Cx, uint8_t errorCode);

/**
  * @brief  ����ģ��I2C����ʱ���źŵ���ʱ
  *	@details 	�����߼������ǲ���I2CͨѶʱ��Ƶ��
  *				����������CPU��Ƶ72MHz ��MDK���뻷����0���Ż�
  *       ѭ������    SCLƵ��
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
  * @brief  I2C I/O����
  * @param  ��
  * @retval ��
  */
static void I2C1_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C �йص�ʱ�� */
	I2C1_APBxClock_CMD(I2C1_CLK, ENABLE);
	I2C1_GPIO_APBxClock_CMD(I2C1_GPIO_CLK, ENABLE);
	
    
  /* I2C_SCL��I2C_SDA */
  GPIO_InitStructure.GPIO_Pin = I2C1_HW_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       /* ��©��� */
  GPIO_Init(I2C1_HW_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = I2C1_HW_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       /* ��©��� */
  GPIO_Init(I2C1_HW_SDA_PORT, &GPIO_InitStructure);	
  
}


/**
  * @brief  I2C ����ģʽ����
  * @param  ��
  * @retval ��
  */
static void I2C1_Mode_Config(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2C1_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	 
	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* ͨ������ */
  I2C_InitStructure.I2C_ClockSpeed = I2C1_Speed;
  
	/* I2C ��ʼ�� */
  I2C_Init(I2C1, &I2C_InitStructure);
  
	/* ʹ�� I2C */
  I2C_Cmd(I2C1, ENABLE);   
}


/**
  * @brief  I2C ����(EEPROM)��ʼ��
  * @param  ��
  * @retval ��
  */
void I2C1_HW_Init(void)
{
  I2C1_GPIO_Config(); 
  I2C1_Mode_Config();
}


/**
  * @brief  ��I2C�豸���������
  * @param  I2Cx      I2Cx
  *         D_Address �豸��ַ
  *			    R_Address	�豸�Ĵ�����ַ
  *			    len 		  ���ݳ���
  *		    	data_buf 	��������
  * @retval �ɹ�����1��ʧ�ܷ���0
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
  * @brief  ��I2C�豸���������
  * @param  D_Address 	�豸��ַ
  *		    	R_Address	�豸�Ĵ�����ַ
  *		    	len 		  ���ݳ���
  *		    	data_buf 	��������
  * @retval �ɹ�����1��ʧ�ܷ���0
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
  * @brief  ����豸�Ƿ����
  * @param  D_Address 	�豸��ַ
  * @retval ����1��ʾ�豸����������0��ʾ�Ҳ����豸
  */
uint8_t I2C_HW_checkDevice(I2C_TypeDef* I2Cx, uint8_t D_Address)
{

	//I2C_GenerateSTOP(I2Cx, ENABLE); /*����ֹͣ�źţ���λ����I2C�豸*/
	  
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

	I2C_GenerateSTOP(I2Cx, ENABLE); /* ���ͽ����ź�  */

	return 1;
}


/**
  * @brief  ���ڽ��I2C BUSY
  * @param  I2Cx
  * @retval None
  */
static void I2C1_HW_BusyUnlock(void)
{
  GPIO_QuickInit(I2C1_GPIO_CLK, I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN, GPIO_Mode_Out_OD);    /* ͨ�ÿ�©��� */
  GPIO_SetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);          /* I2C SCL = 1 */

  I2CTimeout = I2C_HW_LONG_TIMEOUT;
  /* ���I2C SDAΪ�ߵ�ƽ */
  while((!GPIO_ReadOutputDataBit(I2C1_HW_SDA_PORT, I2C1_HW_SDA_PIN)) && (I2CTimeout != 0)) {
      GPIO_ResetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);     /* I2C SCL = 0 */
      I2C_Delay();        
      GPIO_SetBits(I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN);       /* I2C SCL = 1 */
      I2C_Delay();      
      /* �޸����߳�ʱ���� */
      if((--I2CTimeout) == 0) {
          I2C_TIMEOUT_UserCallback(I2C1, 66);
      }
  }
  GPIO_ResetBits(I2C1_HW_SDA_PORT, I2C1_HW_SDA_PIN);         /* I2C SDA = 0 */
  GPIO_QuickInit(I2C1_GPIO_CLK, I2C1_HW_SCL_PORT, I2C1_HW_SCL_PIN, GPIO_Mode_AF_OD);    /* ���ÿ�©��� */
  I2C_SoftwareResetCmd(I2C1, ENABLE);
  I2C_SoftwareResetCmd(I2C1, DISABLE);
}


/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾIIC��ȡʧ��.
  */
static uint32_t I2C_TIMEOUT_UserCallback(I2C_TypeDef* I2Cx, uint8_t errorCode)
{
  I2C_GenerateSTOP(I2Cx, ENABLE); /*����ֹͣ�źţ���λ����I2C�豸*/
  /* Block communication and all processes */
	printf("I2C HW Timeout ErrorCode = %d\r\n",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/

