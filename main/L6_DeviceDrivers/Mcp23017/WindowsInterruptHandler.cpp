/// @brief This file is the implementation of the Windows InterruptHandler.

#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"

void InterruptHandler(void* arg)
{
    Mcp23017DeviceDriver::SetInterruptTriggered();
}
