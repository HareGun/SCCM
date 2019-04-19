#ifndef __I2C_HW_H
#define __I2C_HW_H

#include "user_common.h"

//#define I2Cx_HW						I2C2
//#define I2Cx_HW_CLK					RCC_APB1Periph_I2C2
//#define I2Cx_HW_CLKCMD				RCC_APB1PeriphClockCmd

/*配置SDA,SCL端口和引脚*/
#define I2C2_HW_SCL_GPIO_CLK        RCC_AHB1Periph_GPIOH
#define I2C2_HW_SCL_GPIO_PORT       GPIOH
#define I2C2_HW_SCL_Pin           	GPIO_Pin_4
#define I2C2_HW_SCL_PINSOURCE		GPIO_PinSource4

#define I2C2_HW_SDA_GPIO_CLK        RCC_AHB1Periph_GPIOH
#define I2C2_HW_SDA_GPIO_PORT       GPIOH
#define I2C2_HW_SDA_Pin           	GPIO_Pin_5
#define I2C2_HW_SDA_PINSOURCE		GPIO_PinSource5

/* STM32 I2C 快速模式 */
#define I2C2_Speed              400000

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2C2_OWN_ADDRESS7		0X0A  

/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))


void I2C2_HW_Init(void);

uint8_t I2C_CheckDevice(uint8_t D_Address);

uint8_t I2C_WriteBuff(uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf);
uint8_t I2C_ReadBuff(uint8_t D_Address, uint8_t R_Address, uint16_t len, uint8_t *data_buf);

// Write 8-bit to register
uint8_t I2C_writeRegister8(uint8_t D_Address, uint8_t R_Address, uint8_t data);
// Write 16-bit to register
uint8_t I2C_writeRegister16(uint8_t D_Address, uint8_t R_Address, int16_t value);
// Read 8-bit from register
uint8_t I2C_readRegister8(uint8_t D_Address, uint8_t R_Address);
// Read 16-bit from register
int16_t I2C_readRegister16(uint8_t D_Address, uint8_t R_Address);

// Read register bit
bool I2C_readRegisterBit(uint8_t D_Address, uint8_t R_Address, uint8_t pos);
// Write register bit
uint8_t I2C_writeRegisterBit(uint8_t D_Address, uint8_t R_Address, uint8_t pos, bool state);


/*===========================MPU DMP 接口================================*/
int Sensors_I2C_ReadRegister(unsigned char slave_addr,
                                       unsigned char reg_addr,
                                       unsigned short len,
                                       unsigned char *data_ptr);
int Sensors_I2C_WriteRegister(unsigned char slave_addr,
                                        unsigned char reg_addr,
                                        unsigned short len,
                                        const unsigned char *data_ptr);

#endif /* __I2C_SW_H */
