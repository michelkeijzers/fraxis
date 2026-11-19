#ifdef ESP_PLATFORM

/// @brief This file is the implementation of the ESP MCP23017 InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"
#include "esp_attr.h"

namespace M60::I2c
{
    void IRAM_ATTR Mcp23017InterruptHandler(void* arg)
    {
        Mcp23017DeviceDriver::SetInterruptTriggered();
    }
}

#endif // ESP_PLATFORM
