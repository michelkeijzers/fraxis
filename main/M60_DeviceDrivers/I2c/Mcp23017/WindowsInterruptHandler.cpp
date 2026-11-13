/// @brief This file is the implementation of the Windows InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"

namespace M60::Mcp23017
{
    [[maybe_unused]]
    void InterruptHandler(
        void* /* arg */) // NOSONAR: ESP32 expects void*
    {
        Mcp23017DeviceDriver::SetInterruptTriggered();
    }
}
