#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "user_common.h"

#define BAT_VAD_GPIO_CLK              RCC_APB2Periph_GPIOA
#define BAT_VAD_GPIO_PORT             GPIOA
#define BAT_VAD_PIN                   GPIO_Pin_0

#define BAT_IAD_GPIO_CLK              RCC_APB2Periph_GPIOA
#define BAT_IAD_GPIO_PORT             GPIOA
#define BAT_IAD_PIN                   GPIO_Pin_1

#define CAP_VAD_GPIO_CLK              RCC_APB2Periph_GPIOA
#define CAP_VAD_GPIO_PORT             GPIOA
#define CAP_VAD_PIN                   GPIO_Pin_2

#define BOOST_VAD_GPIO_CLK              RCC_APB2Periph_GPIOA
#define BOOST_VAD_GPIO_PORT             GPIOA
#define BOOST_VAD_PIN                   GPIO_Pin_4

#define ADC_NUMOF_CH     4

/* ��������ֵ */
#define BAT_VOL_SERIES_RES      20000.0f
#define BAT_VOL_PARALLEL_RES    2000.0f
#define BAT_VOL_RATIO           ((BAT_VOL_SERIES_RES + BAT_VOL_PARALLEL_RES)/BAT_VOL_PARALLEL_RES)
#define GET_BAT_VOL(x)          (x*BAT_VOL_RATIO)

#define CURR_SENSOR_SUPPLY      5.0f        /* 5V �����ѹ */
#define CURR_SENSOR_RANGE       40.0f       /* +-20A ������Χ��+-20A��40A�� */
#define BAT_CURR_SERIES_RES     2000.0f
#define BAT_CURR_PARALLEL_RES   3000.0f
#define BAT_CURR_RATIO          (((BAT_CURR_SERIES_RES + BAT_CURR_PARALLEL_RES)/BAT_CURR_PARALLEL_RES))
#define GET_BAT_CURR(x)         ((x*BAT_CURR_RATIO - 2.5f)*8.0f)

//#define BAT_CURR_OFFSET         0.343f         /* ����ϵͳ���ص���... ��λA */
#define BAT_CURR_OFFSET         0.0f         /* ����ϵͳ���ص���... ��λA */

#define CAP_VOL_SERIES_RES      20000.0f
#define CAP_VOL_PARALLEL_RES    2000.0f
#define CAP_VOL_RATIO           ((CAP_VOL_SERIES_RES + CAP_VOL_PARALLEL_RES)/CAP_VOL_PARALLEL_RES)
#define GET_CAP_VOL(x)          (x*CAP_VOL_RATIO)

#define BOOST_VOL_SERIES_RES      18200.0f
#define BOOST_VOL_PARALLEL_RES    1000.0f
#define BOOST_VOL_RATIO           ((BOOST_VOL_SERIES_RES + BOOST_VOL_PARALLEL_RES)/BOOST_VOL_PARALLEL_RES)
#define GET_BOOST_VOL(x)          (x*BOOST_VOL_RATIO)

#define BAT_VOL_LPFATTFACTOR    0.8f
#define BAT_CURR_LPFATTFACTOR   0.5f
#define CAP_VOL_LPFATTFACTOR    0.8f
#define BOOST_VOL_LPFATTFACTOR    0.8f

#define CAP_FULL_VOL            21.0f
#define CAP_LOW_VOL             9.0f

typedef enum{
  CAP_STAT_LOW,
  CAP_STAT_MID,
  CAP_STAT_FULL,
}cap_status_t;

typedef struct{
  uint16_t ADC_Value[ADC_NUMOF_CH];
  /* �˲������� */
  float bat_voltage;  /* ��ص�ѹ����λV */
  float bat_current;  /* ��ص�������λA */
  float cap_voltage;  /* ���ݵ�ѹ����λV */
  float boost_voltage;  /* ��ѹ���ѹ����λV */
  
  /* ԭʼ���� */
  float bat_voltage_RAW;
  float bat_current_RAW;
  float cap_voltage_RAW;
  float boost_voltage_RAW;
  
  /* �����ϵͳ����� */
  float bat_voltage_offset_k;  
  float bat_current_offset_k;
  float cap_voltage_offset_k;
  float boost_voltage_offset_k;
  float bat_voltage_offset_b;
  float bat_current_offset_b;
  float cap_voltage_offset_b;
  float boost_voltage_offset_b;
  
  cap_status_t cap_status;
  uint8_t cap_usable;    /* ���ݿ��Խ������ */
  int8_t cap_level;    /* ����ʣ����� */
}measurement_t;

extern measurement_t measurement;

void Measurement_Init(void);
void Measurement_update(void);


#endif /* __MEASUREMENT_H */
