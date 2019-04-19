#ifndef __I2C_HW_H
#define	__I2C_HW_H


#include "stm32f10x.h"


#define I2C1_APBxClock_CMD                RCC_APB1PeriphClockCmd
#define I2C1_CLK                          RCC_APB1Periph_I2C1
#define I2C1_Speed                        400000     /* STM32 I2C 快速模式 */

#define I2C1_OWN_ADDRESS7                 0X0A       /* 这个地址只要与外挂的I2C器件地址不一样即可 */

#define I2C1_GPIO_APBxClock_CMD            RCC_APB2PeriphClockCmd
#define I2C1_GPIO_CLK                      RCC_APB2Periph_GPIOB   

#define I2C1_HW_SCL_PORT                   GPIOB   
#define I2C1_HW_SCL_PIN                    GPIO_Pin_6

#define I2C1_HW_SDA_PORT                   GPIOB 
#define I2C1_HW_SDA_PIN                    GPIO_Pin_7







void I2C1_HW_Init(void);
uint8_t I2C_HW_checkDevice(I2C_TypeDef* I2Cx, uint8_t D_Address);
uint8_t I2C_HW_readBuff(I2C_TypeDef* I2Cx, uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf);
uint8_t I2C_HW_writeBuff(I2C_TypeDef* I2Cx, uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf);


#endif /* __I2C_HW_H */
