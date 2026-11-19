/// @brief This file is the implementation of the Windows MCP23017 InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "Mcp23017InterruptHandler.hpp"

namespace M60::I2c
{
    [[maybe_unused]]
    void Mcp23017InterruptHandler(
        void* /* arg */) // NOSONAR: ESP32 expects void*
    {
        Mcp23017DeviceDriver::SetInterruptTriggered();
    }
}
