#ifdef ESP_PLATFORM

/// @brief This file is the implementation of the platform independent InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"
#include "esp_attr.h"

void IRAM_ATTR InterruptHandler(void* arg)
{
    Mcp23017DeviceDriver::SetInterruptTriggered();
}

#endif // ESP_PLATFORM
