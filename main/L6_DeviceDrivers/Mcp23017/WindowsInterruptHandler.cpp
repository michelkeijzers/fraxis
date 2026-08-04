/// @brief This file is the implementation of the Windows InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"

[[maybe_unused]]
void InterruptHandler(
    void* arg) // NOSONAR: ESP32 expects void*
{
    Mcp23017DeviceDriver::SetInterruptTriggered();
}
