#ifndef __HW_SPI_H
#define __HW_SPI_H

#include "user_common.h"

//#define Open_SPI1
//#define Open_SPI2
#define Open_SPI5

#ifdef Open_SPI1

#define Using_SPI							SPI1

/*SPI Clock*/
#define      SPI_APBxClock_Cmd      		RCC_APB2PeriphClockCmd
#define      SPI_CLK                		RCC_APB2Periph_SPI1

//CS	PA4
//#define      SPI_CS_CLK             		RCC_AHB1Periph_GPIOA    
//#define      SPI_CS_PORT           		GPIOA
//#define      SPI_CS_PIN         	  		GPIO_Pin_4

//SCK	PA5
#define      SPI_SCK_CLK            		RCC_AHB1Periph_GPIOA
#define      SPI_SCK_PORT          			GPIOA
#define      SPI_SCK_PIN           			GPIO_Pin_5
#define      SPI_SCK_PINSOURCE				GPIO_PinSource5
#define		 SPI_SCK_AF						GPIO_AF_SPI1

//MISO	PA6	
#define      SPI_MISO_CLK					RCC_AHB1Periph_GPIOA
#define      SPI_MISO_PORT					GPIOA
#define      SPI_MISO_PIN					GPIO_Pin_6
#define      SPI_MISO_PINSOURCE				GPIO_PinSource6
#define		 SPI_MISO_AF					GPIO_AF_SPI1

//MOSI	PA7
#define      SPI_MOSI_CLK					RCC_AHB1Periph_GPIOA
#define      SPI_MOSI_PORT					GPIOA
#define      SPI_MOSI_PIN					GPIO_Pin_7
#define      SPI_MOSI_PINSOURCE				GPIO_PinSource7
#define		 SPI_MOSI_AF					GPIO_AF_SPI1

#endif

/*************************************************************************************/

#ifdef Open_SPI2

#define Using_SPI						SPI2

/*SPI Clock*/
#define      SPI_APBxClock_Cmd      		RCC_APB1PeriphClockCmd
#define      SPI_CLK                		RCC_APB1Periph_SPI2

//CS	PB12
//#define      SPI_CS_CLK             		RCC_APB2Periph_GPIOB    
//#define      SPI_CS_PORT           		 	GPIOB
//#define      SPI_CS_PIN         	  		GPIO_Pin_12

//SCK	PB13
#define      SPI_SCK_CLK            		RCC_APB2Periph_GPIOB   
#define      SPI_SCK_PORT          			GPIOB   
#define      SPI_SCK_PIN           			GPIO_Pin_13

//MISO	PB14
#define      SPI_MISO_CLK                RCC_APB2Periph_GPIOB    
#define      SPI_MISO_PORT               GPIOB 
#define      SPI_MISO_PIN                GPIO_Pin_14

//MOSI	PB15
#define      SPI_MOSI_CLK                RCC_APB2Periph_GPIOB    
#define      SPI_MOSI_PORT               GPIOB 
#define      SPI_MOSI_PIN                GPIO_Pin_15

#endif

#ifdef Open_SPI5

#define Using_SPI							SPI5

/*SPI Clock*/
#define      SPI_APBxClock_Cmd      		RCC_APB2PeriphClockCmd
#define      SPI_CLK                		RCC_APB2Periph_SPI5

//CS	PA4
//#define      SPI_CS_CLK             		RCC_AHB1Periph_GPIOF    
//#define      SPI_CS_PORT           		GPIOF
//#define      SPI_CS_PIN         	  		GPIO_Pin_6

//SCK	PA5
#define      SPI_SCK_CLK            		RCC_AHB1Periph_GPIOF
#define      SPI_SCK_PORT          			GPIOF
#define      SPI_SCK_PIN           			GPIO_Pin_7
#define      SPI_SCK_PINSOURCE				GPIO_PinSource7
#define		 SPI_SCK_AF						GPIO_AF_SPI5

//MISO	PA6	
#define      SPI_MISO_CLK					RCC_AHB1Periph_GPIOF
#define      SPI_MISO_PORT					GPIOF
#define      SPI_MISO_PIN					GPIO_Pin_8
#define      SPI_MISO_PINSOURCE				GPIO_PinSource8
#define		 SPI_MISO_AF					GPIO_AF_SPI5

//MOSI	PA7
#define      SPI_MOSI_CLK					RCC_AHB1Periph_GPIOF
#define      SPI_MOSI_PORT					GPIOF
#define      SPI_MOSI_PIN					GPIO_Pin_9
#define      SPI_MOSI_PINSOURCE				GPIO_PinSource9
#define		 SPI_MOSI_AF					GPIO_AF_SPI5

#endif


#define Dummy_Byte                0xFF

#define SPI_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPI_LONG_TIMEOUT         ((uint32_t)(10 * SPI_FLAG_TIMEOUT))


void SPIx_Init(void);
uint8_t SPI_SendByte(uint8_t TXbyte, uint8_t *RXbyte);
uint8_t SPI_SendHalfWord(uint16_t TXdata, uint16_t *RXdata);

uint8_t SPI_ReadByte(void);
uint8_t SPI_ReadByteBuff(uint8_t *RXdata, uint16_t len);


#endif  /*__HW_SPI_H*/
