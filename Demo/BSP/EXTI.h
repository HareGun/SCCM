#ifndef __EXTI_H
#define __EXTI_H

#include "user_common.h"

void EXTI_Config(uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTI_Trigger, FunctionalState EXTI_LineCmd);


#endif /* __EXTI_H */
