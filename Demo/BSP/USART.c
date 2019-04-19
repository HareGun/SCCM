/**
  ******************************************************************************
  * @file    USART.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   USART应用函数接口
  ******************************************************************************
  */
  
  
#include "USART.h"

static USART_TypeDef* Using_USART = USART2;

char USART2_buff[USART2_BUFFLEN];
uint8_t USART2_Pointer = 0;



/**
  * @brief  USART快速初始化
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于接收DR16接收机Dbus数据
  */
void USART1_QuickInit(uint32_t USART_BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK | USART1_RX_GPIO_CLK,ENABLE);

	/* 使能 USART1 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;  
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART1, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART1_IRQn, USART1_MAIN_PRIORITY, USART1_SUB_PRIORITY);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  USART2快速初始化
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于pc端发送，接收调试信息
  */
void USART2_QuickInit(uint32_t USART_BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);

	/* 使能 USART2 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART2, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART2_IRQn, USART2_MAIN_PRIORITY, USART2_SUB_PRIORITY);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  USART3快速初始化
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于pc端发送，接收调试信息
  */
void USART3_QuickInit(uint32_t USART_BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK | USART3_RX_GPIO_CLK,ENABLE);

	/* 使能 USART3 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;  
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART3, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART3_IRQn, USART3_MAIN_PRIORITY, USART3_SUB_PRIORITY);
  
	/* 使能串口接收中断 */
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  UART4快速初始化
  * @param  UART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于pc端发送，接收调试信息
  */
void UART4_QuickInit(uint32_t UART_BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(UART4_TX_GPIO_CLK | UART4_RX_GPIO_CLK,ENABLE);

	/* 使能 UART4 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = UART4_TX_Pin;  
	GPIO_Init(UART4_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = UART4_RX_Pin;
	GPIO_Init(UART4_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(UART4_TX_GPIO_PORT, UART4_TX_PINSOURCE, GPIO_AF_UART4);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(UART4_RX_GPIO_PORT, UART4_RX_PINSOURCE, GPIO_AF_UART4);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = UART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(UART4, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(UART4_IRQn, UART4_MAIN_PRIORITY, UART4_SUB_PRIORITY);
  
	/* 使能串口接收中断 */
//	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(UART4, ENABLE);
}


/**
  * @brief  USART快速初始化
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于接收裁判系统数据
  */
void USART6_QuickInit(uint32_t USART_BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK | USART6_RX_GPIO_CLK,ENABLE);

	/* 使能 USART6 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;  
	GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;
	GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART6, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART6_IRQn, USART6_MAIN_PRIORITY, USART6_SUB_PRIORITY);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART6, ENABLE);
}


/**
  * @brief  USART1 RX DMA 配置，外设到内存(USART1->DR)
  * @param  USART1_DMABuff_addr		DMA目标存储地址
  * @retval 无
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA2时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART1_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE){
	}

	/*usart1 rx对应dma2，通道4，数据流2*/	
	DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE){
	}
  
	//使能DMA接收  
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
  
}

/**
  * @brief  USART2 RX DMA 配置，外设到内存(USART2->DR)
  * @param  USART2_DMABuff_addr		DMA目标存储地址
  * @retval 无
  */
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA1时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART2_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != DISABLE){
	}

	/*usart2 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = USART2_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART2_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != ENABLE){
	}
  
	//使能DMA接收  
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
  
}

/**
  * @brief  USART3 RX DMA 配置，外设到内存(USART3->DR)
  * @param  USART3_DMABuff_addr		DMA目标存储地址
  * @retval 无
  */
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA1时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART3_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != DISABLE){
	}

	/*USART3 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = USART3_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART3_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != ENABLE){
	}
  
	//使能DMA接收  
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 
  
}

/**
  * @brief  USART6 RX DMA 配置，外设到内存(USART6->DR)
  * @param  USART6_DMABuff_addr		DMA目标存储地址
  * @retval 无
  */
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA2时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART6_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != DISABLE){
	}

	/*usart6 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = USART6_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART6_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART6_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != ENABLE){
	}
  
	//使能DMA接收  
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE); 
  
}


/**
  * @brief  USART使用printf，scanf端口设置
  * @param  USARTx 	USART外设
  * @retval None
  */
void USART_setPort(USART_TypeDef* USARTx){
	Using_USART = USARTx;
}


/**
  * @brief  USART发送一个字符
  * @param  USARTx 	USART外设
  *			ch 		字符
  * @retval None
  */
void USART_sendChar(USART_TypeDef* USARTx, char ch){
	/* 发送一个字节数据到串口 */
	USART_SendData(USARTx, (uint8_t) ch);
	
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(Using_USART, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(Using_USART);
}
