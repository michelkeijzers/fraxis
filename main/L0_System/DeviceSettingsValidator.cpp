#include "DeviceSettingsValidator.hpp"

#ifdef ASSERTS_ENABLED

#include "DeviceSettings.hpp"
#include <cstdint>

#ifdef ESP_PLATFORM
    #include "driver/i2c.h"
#endif // ESP_PLATFORM

/* static */ void DeviceSettingsValidator::Validate()
{
    ValidatePins();
    ValidateI2c();
    ValidateMcp23017();
}

/* static */ void DeviceSettingsValidator::ValidatePins()
{
    std::list<uint8_t> pins = {
        DeviceSettings::PIN_I2C_SDA,
        DeviceSettings::PIN_I2C_SCL,
        DeviceSettings::PIN_MCP23017_INTERRUPT,
        DeviceSettings::PIN_TM1637_CLOCK,
        DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA,
        DeviceSettings::PIN_TM1637_PLAYER_1_DATA,
        DeviceSettings::PIN_TM1637_PLAYER_2_DATA,
        DeviceSettings::PIN_WS2812_DATA
    };

    Assert::AreUnique(pins, "Device settings pins are not unique");
    for (uint8_t pin: pins)
    {
        Assert::IsEsp32Pin(pin, "Not all device settings pins are ESP32 pins");
    }
}

/* static */ void DeviceSettingsValidator::ValidateI2c()
{
    #ifdef ESP_PLATFORM
        static_assert((DeviceSettings::I2C_PORT == I2C_NUM_0) || 
                      (DeviceSettings::I2C_PORT == I2C_NUM_1), 
            "I2C port is not I2C_NUM_0 or I2C_NUM_1");
    #else
        static_assert((DeviceSettings::I2C_PORT == 0) || 
                      (DeviceSettings::I2C_PORT == 1), 
            "I2C port is not 0 or 1");
    #endif // ESP_PLATFORM
    
    static_assert((DeviceSettings::I2C_FREQUENCY == 100'000) || 
                  (DeviceSettings::I2C_FREQUENCY == 400'000), 
        "I2C frequency is not 100 or 400 KHz");
    static_assert((DeviceSettings::I2C_ADDRESS_MCP23017 > 0x00) && 
                  (DeviceSettings::I2C_ADDRESS_MCP23017 <= 0x7F),
        "MCP23017 I2C address is not between 0x00 and 0x7F");
    static_assert((DeviceSettings::I2C_ADDRESS_LCD2004 > 0x00) && 
                  (DeviceSettings::I2C_ADDRESS_LCD2004 <= 0x7F),
        "LCD2004 I2C address is not between 0x00 and 0x7F");
}

/* static */ void DeviceSettingsValidator::ValidateMcp23017()
{
    std::list<uint8_t> bits = {
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON,
        DeviceSettings::MCP23017_BIT_PLAYER_1_LED,

        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON,
        DeviceSettings::MCP23017_BIT_PLAYER_2_LED,

        DeviceSettings::MCP23017_BIT_SYSTEM_BUTTON,
        DeviceSettings::MCP23017_BIT_PAUSE_LED,
        DeviceSettings::MCP23017_BIT_SELECT_LED,
        DeviceSettings::MCP23017_BIT_SETUP_LED
    };

    Assert::AreUnique(bits, "MCP23017 Device Settings bits are not unique");
    for (uint8_t bit: bits)
    {
        Assert::IsBetween(bit, 0, 16, "MCP23017 Device Settings bits are out of range");
    }
}

#endif // ASSERTS_ENABLED
