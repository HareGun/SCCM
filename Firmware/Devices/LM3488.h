#ifndef __LM3488_H
#define __LM3488_H

#include "user_common.h"


#define LM3488_EN_GPIO_CLK          RCC_APB2Periph_GPIOB
#define LM3488_EN_GPIO_PORT         GPIOB
#define LM3488_EN_PIN               GPIO_Pin_14

#define LM3488_EN(isOn) 				    GPIO_WriteBit(LM3488_EN_GPIO_PORT,LM3488_EN_PIN, (BitAction)isOn)


void LM3488_Init(void);

#endif /* __LM3488_H */
