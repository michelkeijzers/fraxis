#pragma once

//TODO: Make sure this file is not read by windows
#include "driver/i2c.h"
#include <cstdint>

class DeviceSettings
{
public:
    // TODO: Check all pins
    static const uint8_t  PIN_I2C_SDA         = 21;
    static const uint8_t  PIN_I2C_SCL         = 22;
    static const uint8_t  PIN_LED_STRIP_DATA  = 23;
    
    // I2C
    static const uint8_t  I2C_PORT             = I2C_NUM_0;
    static const uint32_t I2C_FREQUENCY        = 100000; // 100000
    static const uint8_t  I2C_ADDRESS_MCP23017 = 0x20;
    static const uint8_t  I2C_ADDRESS_LCD2004  = 0x27;
};