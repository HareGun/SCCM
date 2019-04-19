/**
  ******************************************************************************
  * @file    Measurement.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   电压电流测量应用函数接口
  ******************************************************************************
  */
  
  
#include "Measurement.h"
#include "Filter.h"

measurement_t measurement;

/**
  * @brief  GPIO初始化
  * @param  None
  * @retval None
  */
static void Measurement_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = BAT_VAD_PIN | BAT_IAD_PIN |
                                CAP_VAD_PIN;
	GPIO_Init(BAT_VAD_GPIO_PORT, &GPIO_InitStructure);
  
}

/**
  * @brief  ADC初始化
  * @param  None
  * @retval None
  */
static void Measurement_ADC_Config(void){
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//配置ADC初始化结构体
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = ADC_NUMOF_CH;
	
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//配置ADC时钟分频	RCC_PCLK2_Div2/4/6/8分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//配置规则序列ADC通道，转换顺序和采样时间
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);

	//使能ADC
	ADC_Cmd(ADC1, ENABLE);
	
	//复位校准ADC
	ADC_ResetCalibration(ADC1);
	//等待复位完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	//校准ADC
	ADC_StartCalibration(ADC1);
	//等待校准完成
	while(ADC_GetCalibrationStatus(ADC1));
	
	
}


/**
  * @brief  DMA初始化
  * @param  None
  * @retval None
  */
static void Measurement_DMA_Config(void){
	DMA_InitTypeDef DMA_InitStructure;
	//开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//复位ADC通道的DMA
	DMA_DeInit(DMA1_Channel1);
	//设定外设（源）的地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
	//设定目标变量的地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)measurement.ADC_Value;
	//设置传输方向，外设做源
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//设置要传输的数据个数
	DMA_InitStructure.DMA_BufferSize = ADC_NUMOF_CH;
	//设置外设地址是否自增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//设置变量地址是否自增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	//设置外设数据宽度
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//设置变量数据宽度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//配置DMA传输模式，单次或循环
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	//配置通道优先级
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//配置是否开启存储器到存储器模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//初始化结构体
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  NVIC_Config(DMA1_Channel1_IRQn, 2, 0);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	//使能DMA
	DMA_Cmd(DMA1_Channel1 , ENABLE);
  
  
	
	// 使能DMA 请求
	ADC_DMACmd(ADC1, ENABLE);
	//启用软件触发ADC转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
}

/**
  * @brief  测量初始化
  * @param  None
  * @retval None
  */
void Measurement_Init(void){
	Measurement_GPIO_Init();
  Measurement_ADC_Config();
  Measurement_DMA_Config();
  
}

/**
  * @brief  测量数据更新
  * @param  None
  * @retval None
  */
void Measurement_update(void){
	measurement.bat_voltage_RAW = GET_BAT_VOL( (float)measurement.ADC_Value[0]/4096.0f*3.3f );
  measurement.bat_current_RAW = GET_BAT_CURR( (float)measurement.ADC_Value[1]/4096.0f*3.3f ) + BAT_CURR_OFFSET;
  measurement.cap_voltage_RAW = GET_CAP_VOL( (float)measurement.ADC_Value[2]/4096.0f*3.3f );
  
  Filter_IIRLPF(&measurement.bat_voltage_RAW,&measurement.bat_voltage, BAT_VOL_LPFATTFACTOR);
  Filter_IIRLPF(&measurement.bat_current_RAW,&measurement.bat_current, BAT_CURR_LPFATTFACTOR);
  Filter_IIRLPF(&measurement.cap_voltage_RAW,&measurement.cap_voltage, CAP_VOL_LPFATTFACTOR);
  
  if(measurement.cap_voltage < 10.0f){
    measurement.cap_status = CAP_STAT_LOW;
    measurement.cap_usable = 0;
  }
  else if(measurement.cap_voltage > 12.0f && measurement.cap_voltage < 18.0f){
    measurement.cap_status = CAP_STAT_MID;
    measurement.cap_usable = 1;
  }
  else if(measurement.cap_voltage > 20.0f){
    measurement.cap_status = CAP_STAT_FULL;
    measurement.cap_usable = 1;
  }
}


