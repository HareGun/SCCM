/**
  ******************************************************************************
  * @file    DMA.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   DMA应用函数接口
  ******************************************************************************
  */
  
  
#include "DMA.h"


///**
//  * @brief  DMA2外设到内存模式快速初始化
//  * @param  DMAy_Streamx		DMA数据流，y可以是1或2，x可以为0-7
//  *								数据流对应外设详见F4参考手册P206，表36
//  *			DMA_Channel			DMA通道号，通道对应外设详见F4参考手册P206，表36
//  *			PeripheralBaseAddr	外设基地址
//  *			Memory0BaseAddr		存储基地址
//  *			BufferSize			单次传输数据大小
//  * @retval 无
//  */
//void DMA2_QuickPeriphToMemory(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Channel, uint32_t PeripheralBaseAddr, uint32_t Memory0BaseAddr, uint32_t BufferSize)
//{
//  DMA_InitTypeDef DMA_InitStructure;

//  /*开启DMA2时钟*/
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//  
//  /* 复位初始化DMA数据流 */
//  DMA_DeInit(DMAy_Streamx);

//  /* 确保DMA数据流复位完成 */
//  while (DMA_GetCmdStatus(DMAy_Streamx) != DISABLE)  {
//  }

//  /*配置DMA通道*/	
//  DMA_InitStructure.DMA_Channel = DMA_Channel;  
//  /*设置DMA源地址*/
//  DMA_InitStructure.DMA_PeripheralBaseAddr = PeripheralBaseAddr;	 
//  /*内存地址(要传输的变量的指针)*/
//  DMA_InitStructure.DMA_Memory0BaseAddr = Memory0BaseAddr;
//  /*方向：从内存到外设*/		
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;	
//  /*传输大小DMA_BufferSize=BufferSize*/	
//  DMA_InitStructure.DMA_BufferSize = BufferSize;
//  /*外设地址不增*/	    
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//  /*内存地址自增*/
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
//  /*外设数据单位*/	
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  /*内存数据单位 8bit*/
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
//  /*DMA模式：不断循环*/
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
//  /*优先级：中*/	
//  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
//  /*禁用FIFO*/
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
//  /*存储器突发传输 16个节拍*/
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
//  /*外设突发传输 1个节拍*/
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
//  /*配置DMA2的数据流*/		   
//  DMA_Init(DMAy_Streamx, &DMA_InitStructure);
//  
//  /*使能DMA*/
//  DMA_Cmd(DMAy_Streamx, ENABLE);
//  
//  /* 等待DMA数据流有效*/
//  while(DMA_GetCmdStatus(DMAy_Streamx) != ENABLE)
//  {
//  }   
//}


