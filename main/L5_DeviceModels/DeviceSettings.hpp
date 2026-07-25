#pragma once

#include <cstdint>

class DeviceSettings
{
public:
    // TODO: Check all pins
    static const int8_t PIN_I2C_SDA         = 21;
    static const int8_t PIN_I2C_SCL         = 22;
    static const int8_t PIN_LED_STRIP_DATA  = 23;

    // I2c Addresses
    static const int8_t I2C_ADDRESS_MCP23017 = 0x20;
    static const int8_t I2C_ADDRESS_LCD2004  = 0x27;
};