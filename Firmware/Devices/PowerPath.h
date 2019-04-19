#ifndef __POWERPATH_H
#define __POWERPATH_H

#include "user_common.h"


#define POWERPATH_GPIO_CLK          RCC_APB2Periph_GPIOA
#define POWERPATH_GPIO_PORT         GPIOA
#define POWERPATH_PIN               GPIO_Pin_3

#define POWERPATH_CAP_OUTPUT(isOn) 	GPIO_WriteBit(POWERPATH_GPIO_PORT,POWERPATH_PIN, (BitAction)isOn)


void PowerPath_Init(void);

#endif /* __POWERPATH_H */
