#pragma once

#ifdef ESP_PLATFORM
#include "driver/i2c.h"
#endif // ESP_PLATFORM

#include <cstdint>

/// @brief Device settings for ESP S3.
/// @todo Later: Use good values for pin numbers.
class DeviceSettings
{
public:
    static constexpr uint8_t  PIN_I2C_SDA                               =  38;
    static constexpr uint8_t  PIN_I2C_SCL                               =  39;
    static constexpr uint8_t  PIN_MCP23017_INTERRUPT                    =  40;
    static constexpr uint8_t  PIN_TM1637_CLOCK                          =  41;
    static constexpr uint8_t  PIN_TM1637_CENTRAL_PANEL_DATA             =  15;
    static constexpr uint8_t  PIN_TM1637_PLAYER_1_DATA                  =  16;
    static constexpr uint8_t  PIN_TM1637_PLAYER_2_DATA                  =  17;
    static constexpr uint8_t  PIN_WS2812_DATA                           =  18;

    // I2C
    #ifdef ESP_PLATFORM
        static const uint8_t  I2C_PORT                                  = I2C_NUM_0;
    #else
        static const uint8_t  I2C_PORT                                  = 0;
    #endif
    static constexpr uint32_t I2C_FREQUENCY                             = 100'000;
    static constexpr uint8_t  I2C_ADDRESS_MCP23017                      = 0x20;
    static constexpr uint8_t  I2C_ADDRESS_LCD2004                       = 0x27;

    // MCP23017 PORTS AND PINS
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_UP         =   8;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN       =   9;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT       =  11;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT      =  14;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON     =  10;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_1_LED                 =   4;

    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_UP         =  12;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN       =   2;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT       =   1;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT      =   0;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON     =  15;
    static constexpr uint8_t  MCP23017_BIT_PLAYER_2_LED                 =   3;

    static constexpr uint8_t  MCP23017_BIT_SYSTEM_BUTTON                =   7;
    static constexpr uint8_t  MCP23017_BIT_PAUSE_LED                    =   6;
    static constexpr uint8_t  MCP23017_BIT_SELECT_LED                   =   5;
    static constexpr uint8_t  MCP23017_BIT_SETUP_LED                    =  13;

    static constexpr uint16_t MAX_LED_STRIPS_CURRENT_CONSUMPTION_IN_MA  = 5000; // mA
};
