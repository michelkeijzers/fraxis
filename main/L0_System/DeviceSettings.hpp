#pragma once

#include "driver/i2c.h"
#include <cstdint>

class DeviceSettings
{
public:
    static const uint8_t  PIN_I2C_SDA;
    static const uint8_t  PIN_I2C_SCL;
    static const uint8_t  PIN_MCP23017_INTERRUPT;
    static const uint8_t  PIN_TM1637_CLOCK;
    static const uint8_t  PIN_TM1637_CENTRAL_PANEL_DATA;
    static const uint8_t  PIN_TM1637_PLAYER_1_DATA;
    static const uint8_t  PIN_TM1637_PLAYER_2_DATA;
    static const uint8_t  PIN_WS2812_DATA;

    // I2C
    static const uint8_t  I2C_PORT;
    static const uint32_t I2C_FREQUENCY;
    static const uint8_t  I2C_ADDRESS_MCP23017;
    static const uint8_t  I2C_ADDRESS_LCD2004;

    // MCP23017 PORTS AND PINS
    static const uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_UP;
    static const uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN;
    static const uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT;
    static const uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT;
    static const uint8_t  MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON;
    static const uint8_t  MCP23017_BIT_PLAYER_1_LED;

    static const uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_UP;
    static const uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN;
    static const uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT;
    static const uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT;
    static const uint8_t  MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON;
    static const uint8_t  MCP23017_BIT_PLAYER_2_LED;

    static const uint8_t  MCP23017_BIT_SYSTEM_BUTTON;
    static const uint8_t  MCP23017_BIT_PAUSE_LED;
    static const uint8_t  MCP23017_BIT_SELECT_LED;
    static const uint8_t  MCP23017_BIT_SETUP_LED;

    static const uint16_t MAX_LED_STRIPS_CURRENT_CONSUMPION_IN_MA;
};
