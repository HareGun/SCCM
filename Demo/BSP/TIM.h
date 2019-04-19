#ifndef _TIM_H
#define _TIM_H

#include "user_common.h"

/********TIM1_Pin_define********/
#define TIM1_CH1_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define TIM1_CH1_GPIO_PORT         	GPIOA
#define TIM1_CH1_Pin          	 	GPIO_Pin_8
#define TIM1_CH1_PINSOURCE			GPIO_PinSource8
#define TIM1_CH1_ENABLE				1

#define TIM1_CH2_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define TIM1_CH2_GPIO_PORT         	GPIOA
#define TIM1_CH2_Pin          	 	GPIO_Pin_9
#define TIM1_CH2_PINSOURCE			GPIO_PinSource9
#define TIM1_CH2_ENABLE				0

#define TIM1_CH3_GPIO_CLK          	RCC_AHB1Periph_GPIOE
#define TIM1_CH3_GPIO_PORT         	GPIOE
#define TIM1_CH3_Pin          	 	GPIO_Pin_13
#define TIM1_CH3_PINSOURCE			GPIO_PinSource13
#define TIM1_CH3_ENABLE				0

#define TIM1_CH4_GPIO_CLK          	RCC_AHB1Periph_GPIOE
#define TIM1_CH4_GPIO_PORT         	GPIOE
#define TIM1_CH4_Pin          	 	GPIO_Pin_14
#define TIM1_CH4_PINSOURCE			GPIO_PinSource14
#define TIM1_CH4_ENABLE				1
/********TIM1_Pin_define_END********/

/********TIM8_Pin_define********/
#define TIM8_CH1_GPIO_CLK          	RCC_AHB1Periph_GPIOC
#define TIM8_CH1_GPIO_PORT         	GPIOC
#define TIM8_CH1_Pin          	 	GPIO_Pin_6
#define TIM8_CH1_PINSOURCE			GPIO_PinSource6
#define TIM8_CH1_ENABLE				1

#define TIM8_CH2_GPIO_CLK          	RCC_AHB1Periph_GPIOC
#define TIM8_CH2_GPIO_PORT         	GPIOC
#define TIM8_CH2_Pin          	 	GPIO_Pin_7
#define TIM8_CH2_PINSOURCE			GPIO_PinSource7
#define TIM8_CH2_ENABLE				1

#define TIM8_CH3_GPIO_CLK          	RCC_AHB1Periph_GPIOC
#define TIM8_CH3_GPIO_PORT         	GPIOC
#define TIM8_CH3_Pin          	 	GPIO_Pin_8
#define TIM8_CH3_PINSOURCE			GPIO_PinSource8
#define TIM8_CH3_ENABLE				1

#define TIM8_CH4_GPIO_CLK          	RCC_AHB1Periph_GPIOC
#define TIM8_CH4_GPIO_PORT         	GPIOC
#define TIM8_CH4_Pin          	 	GPIO_Pin_9
#define TIM8_CH4_PINSOURCE			GPIO_PinSource9
#define TIM8_CH4_ENABLE				1
/********TIM8_Pin_define_END********/

/********TIM12_Pin_define********/
#define TIM12_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define TIM12_CH1_GPIO_PORT         GPIOB
#define TIM12_CH1_Pin          	 	GPIO_Pin_14
#define TIM12_CH1_PINSOURCE			GPIO_PinSource14
#define TIM12_CH1_ENABLE			1

#define TIM12_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define TIM12_CH2_GPIO_PORT         GPIOB
#define TIM12_CH2_Pin          	 	GPIO_Pin_15
#define TIM12_CH2_PINSOURCE			GPIO_PinSource15
#define TIM12_CH2_ENABLE			0
/********TIM12_Pin_define_END********/

typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);

extern TIM_SetComparex_f *const TIM_SetComparex[4];

void TIM1_PWMOutput(u16 prescaler, u16 period, u16 Pulse);
void TIM8_PWMOutput(u16 prescaler, u16 period, u16 Pulse);

void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse);

void TIM2_EncoderMode(u16 prescaler, u16 period);

void TIMxGeneral_EncoderMode(uint32_t RCC_APB1Periph_TIMx, TIM_TypeDef* TIMx, u16 prescaler, u16 period);
int Encoder_Read(TIM_TypeDef* TIMx);

void TIM6_CounterMode(u16 prescaler, u16 period);
void TIM7_CounterMode(u16 prescaler, u16 period);



#endif
