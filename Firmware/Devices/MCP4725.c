/**
  ******************************************************************************
  * @file    MCP4725.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   MCP4725 12bit DAC 驱动函数接口
  ******************************************************************************
  */

#include "MCP4725.h"
#include "I2C_HW.h"

uint8_t MCP4725_I2C_bus_write(uint8_t reg_addr, uint8_t *reg_data, uint8_t len)
{
  return I2C_HW_writeBuff(I2C1, MCP4725_I2C_ADDR_DEFAULT, reg_addr, len, reg_data);

}
 
/**************************************************************************/
/*! 
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4725's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
*/
/**************************************************************************/

/**
  * @brief  Sets the output voltage to a fraction of source vref.  (Value
  *         can be 0..4095)
  * @param  output
  * @retval None
  */
void MCP4725_setVoltage(float voltage)
{
  uint16_t output = MCP4726_VOLTAGE_TO_VALUE(voltage);
  uint8_t data[2];
  data[0] = output / 16;          // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  data[1] = (output % 16) << 4;   // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  
  MCP4725_I2C_bus_write(MCP4726_CMD_WRITEDAC, data, 2);

}

/**
  * @brief  The 12-bit value representing the relationship between
  *         the DAC's input voltage and its output voltage.
  * @param  output   'output' will also be written
  *                   to the MCP4725's internal non-volatile memory, meaning
  *                   that the DAC will retain the current voltage output
  *                   after power-down or reset.
  * @retval None
  */
void MCP4725_saveVoltageToEEPROM(float voltage)
{
  uint16_t output = MCP4726_VOLTAGE_TO_VALUE(voltage);
  uint8_t data[2];
  data[0] = output / 16;          // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  data[1] = (output % 16) << 4;   // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  
  MCP4725_I2C_bus_write(MCP4726_CMD_WRITEDACEEPROM, data, 2);
}

void MCP4725_Init(void)
{
  I2C1_HW_Init();
  MCP4725_setVoltage(0.0f);
}
