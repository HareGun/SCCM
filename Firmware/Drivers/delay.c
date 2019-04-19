/**
  ******************************************************************************
  * @file     delay.c
  * @author   Hare
  * @version  V1.4
  * @date     2019-04-01
  * @brief    延时应用函数接口，OS可用，利用DWT实现延时
  * @Note     1.如果启用OS，则Systick中断服务函数建议写成如下形式（以FreeRTOS为例）
  *             在任务开始调度后再调用系统的SystickHandle
  *             否则如果在系统开始调度前如果进入了中断会使程序卡在中断里
  *             void SysTick_Handler(void)
  *             {
	*               if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
  *               {
  *                 xPortSysTickHandler();	
  *               }
  *             }
  *           2.记得在main中初始化Systick
  *             SysTick_Config(SystemCoreClock/1000);
  *           3.因Systick计数原因，当tStart在71990附近会出现卡在while循环，
  *             现改用DWT实现，记得初始化dwt才可正常使用delay
  ******************************************************************************
  */
  
  
#include "delay.h"

/* DWT 寄存器地址 */
#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
#define  DWT_CR      *(volatile unsigned int *)0xE0001000
#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004

#define  DEM_CR_TRCENA               (1 << 24)
#define  DWT_CR_CYCCNTENA            (1 <<  0)


void delay_init(void)
{
	DEM_CR         |= (unsigned int)DEM_CR_TRCENA;   /* Enable Cortex-M4's DWT CYCCNT reg.  */
	DWT_CYCCNT      = (unsigned int)0u;
	DWT_CR         |= (unsigned int)DWT_CR_CYCCNTENA;
}

///**
//  * @brief  微秒级延时,参考安富莱DWT，延时数值较小时会有0.25us左右误差
//  * @Note 	两个32位无符号数相减，获取的结果再赋值给32位无符号数依然可以正确的获取差值。
//  *			假如A,B,C都是32位无符号数。
//  *              如果A > B  那么A - B = C，这个很好理解，完全没有问题
//  *              如果A < B  那么A - B = C， C的数值就是0xFFFFFFFF - B + A + 1。
//  * @param  _us 延时微秒数，32位计数器计满是2^32/SystemCoreClock秒
//  * @retval None
//  */
void delay_us(uint32_t _us)
{
  uint32_t tCnt, tDelayCnt;
	uint32_t tStart;
		
	tStart = DWT_CYCCNT;                                     /* 刚进入时的计数器值 */
	tCnt = 0;
	tDelayCnt = _us * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */ 		      

	while(tCnt < tDelayCnt)
	{
		tCnt = DWT_CYCCNT - tStart; /* 求减过程中，如果发生第一次32位计数器重新计数，依然可以正确计算 */	
	}
}

/**
  * @brief  毫秒级延时
  * @param  _ms 延时毫秒数
  * @retval None
  */
void delay_ms(uint32_t _ms)
{
	uint32_t i;
	for(i=0;i<_ms;i++){
		delay_us(1000);
	}
}

/* 因F1使用systick实现会出问题，此代码作废 */
///**
//  * @brief  微秒级延时,参考安富莱DWT，延时数值较小时会有0.25us左右误差
//  * @Note 	两个32位无符号数相减，获取的结果再赋值给32位无符号数依然可以正确的获取差值。
//  *			假如A,B,C都是32位无符号数。
//  *              如果A > B  那么A - B = C，这个很好理解，完全没有问题
//  *              如果A < B  那么A - B = C， C的数值就是0xFFFFFFFF - B + A + 1。
//  * @param  _us 延时微秒数，32位计数器计满是2^32/SystemCoreClock秒
//  * @retval None
//  */
//void delay_us(uint32_t _us)
//{
//	uint32_t tCnt, tDelayCnt;
//	uint32_t tStart;
//	
//	tStart = SysTick->VAL;
//	tCnt = 0;
//	tDelayCnt = _us * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */ 
//	
//	while(tCnt < tDelayCnt)
//	{
//		tCnt = tStart - SysTick->VAL; /* 求减过程中，如果发生第一次32位计数器重新计数，依然可以正确计算 */	
//	}
//	
//}




