#ifndef __BQ24640_H
#define __BQ24640_H

#include "user_common.h"


#define BQ_STAT_GPIO_CLK              RCC_APB2Periph_GPIOB
#define BQ_STAT_GPIO_PORT           	GPIOB
#define BQ_STAT_PIN                   GPIO_Pin_5

#define BQ_PG_GPIO_CLK                RCC_APB2Periph_GPIOB
#define BQ_PG_GPIO_PORT               GPIOB
#define BQ_PG_PIN                     GPIO_Pin_3

#define BQ_EN_GPIO_CLK                RCC_APB2Periph_GPIOB
#define BQ_EN_GPIO_PORT               GPIOB
#define BQ_EN_PIN                     GPIO_Pin_4

#define BQ_EN(isOn) 				          GPIO_WriteBit(BQ_EN_GPIO_PORT,BQ_EN_PIN, (BitAction)isOn)

#define BQ_GET_STAT_PIN()             !GPIO_ReadInputDataBit(BQ_STAT_GPIO_PORT, BQ_STAT_PIN)
#define BQ_GET_PG_PIN()               !GPIO_ReadInputDataBit(BQ_PG_GPIO_PORT, BQ_PG_PIN)

#define BQ_ISET_RATIO                 (2.0f/10.0f)
#define BQ_CHARGE_CURRENT_MAX         (8.0f)


typedef enum{
  BQ_STAT_CE_HIGH,        /* CE high */
  BQ_STAT_SLEEP_MODE,     /* Sleep mode */
  BQ_STAT_BLINKING,       /* Charge Suspend (TS), Input or Output Overvoltage, CE low */
}BQ_STAT_e;


typedef struct{
  BQ_STAT_e charge_state;
  uint8_t isPowerGood;
}BQ24640_t;

void BQ24640_Init(void);
void BQ_setChargeCurrent(float current);

#endif /* __BQ24640_H */
