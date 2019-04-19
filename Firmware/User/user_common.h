#ifndef __USER_COMMON_H
#define __USER_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/***---FreeRTOS_BEGIN---***/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
/***---FreeRTOS_END---***/


#include "stm32f10x.h"


#include "binary.h"
#include "UserMath.h"
#include "typedefs.h"

/***---Drivers_Begin---***/
#include "delay.h"
#include "NVIC.h"
#include "GPIO.h"
#include "USART.h"
//#include "I2C_SW.h"
//#include "SPI_HW.h"
#include "CAN.h"
#include "Flash.h"
#include "TIM.h"
//#include "bsp_dwt.h"
/***---Drivers_End---***/

/***---Devices_Begin---***/

/***---Devices_End---***/

/***---Apps_Begin---***/

/***---Apps_End---***/

/***---Tasks_Begin---***/

/***---Tasks_End---***/


#endif /*__USER_COMMON_H */
