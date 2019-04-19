#ifndef __USER_COMMON_H
#define __USER_COMMON_H

/* --- STD Libraries --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arm_math.h>
#include "stm32f4xx.h"

/* --- User Public Header --- */
#include "binary.h"
#include "UserMath.h"
#include "typedefs.h"

/* --- FreeRTOS --- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"


/* --- BSP --- */
#include "delay.h"
#include "NVIC.h"
#include "USART.h"
#include "I2C_SW.h"
#include "SPI_HW.h"
#include "CAN.h"
#include "TIM.h"

/* --- External Devices Driver --- */
#include "LED.h"
#include "key.h"
#include "DR16_Receiver.h"



/* --- Apps --- */
#include "Filter.h"
#include "PID.h"

#include "DevicesMonitor.h"
#include "Ramp.h"

/* --- Tasks --- */
#include "SystemInit_Tasks.h"
#include "DevicesMonitor_Tasks.h"
#include "Chassis_Task.h"



#endif /*__USER_COMMON_H */
