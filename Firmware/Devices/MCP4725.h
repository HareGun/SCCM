#ifndef __MCP4725_H
#define __MCP4725_H

#include "user_common.h"

/* MCP4725 I2C Address */
#define MCP4725_I2C_ADDR1                 (0x62)
#define MCP4725_I2C_ADDR2                 (0x63)

#define MCP4725_I2C_ADDR_DEFAULT          MCP4725_I2C_ADDR1

#define MCP4726_CMD_WRITEDAC              (0x40)  // Writes data to the DAC
#define MCP4726_CMD_WRITEDACEEPROM        (0x60)  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

#define MCP4726_SUPPLY_VOLTAGE            3.3f
#define MCP4726_VOLTAGE_TO_VALUE(x)       (4095.0f/MCP4726_SUPPLY_VOLTAGE * x)

void MCP4725_Init(void);
void MCP4725_setVoltage(float voltage);
void MCP4725_saveVoltageToEEPROM(float voltage);

#endif /* __MCP4725_H */
