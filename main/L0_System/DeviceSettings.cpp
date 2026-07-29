#include "DeviceSettings.hpp"

const uint8_t DeviceSettings::PIN_I2C_SDA = 21;
const uint8_t DeviceSettings::PIN_I2C_SCL = 22;
const uint8_t DeviceSettings::PIN_MCP23017_INTERRUPT = 66;
const uint8_t DeviceSettings::PIN_TM1637_CLOCK = 70;
const uint8_t DeviceSettings::PIN_TM1637_CENTRAL_PANEL = 67;
const uint8_t DeviceSettings::PIN_TM1637_PLAYER_1 = 68;
const uint8_t DeviceSettings::PIN_TM1637_PLAYER_2 = 69;
const uint8_t DeviceSettings::PIN_LED_STRIP_DATA = 23;

#if defined(_WIN32) || defined(_WIN64)    
    const uint8_t DeviceSettings::I2C_PORT = 0;
#else
    const uint8_t DeviceSettings::I2C_PORT = I2C_NUM_0;
#endif

const uint32_t DeviceSettings::I2C_FREQUENCY = 100'000;
const uint8_t DeviceSettings::I2C_ADDRESS_MCP23017 = 0x20;
const uint8_t DeviceSettings::I2C_ADDRESS_LCD2004 = 0x27;

const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_UP = 8;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN = 9;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT = 11;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT = 14;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON = 10;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_1_LED = 4;

const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_UP = 12;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN = 2;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT = 1;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT = 0;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON = 15;
const uint8_t DeviceSettings::MCP23017_BIT_PLAYER_2_LED = 3;

const uint8_t DeviceSettings::MCP23017_BIT_SYSTEM_BUTTON = 7;
const uint8_t DeviceSettings::MCP23017_BIT_PAUSE_LED = 6;
const uint8_t DeviceSettings::MCP23017_BIT_SELECT_LED = 5;
const uint8_t DeviceSettings::MCP23017_BIT_SETUP_LED = 13;
