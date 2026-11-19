#pragma once

namespace M60::I2c
{
    /// @brief Interrupt handler for the MCP23017 which is implemented in platform specific versions 
    /// due to the need for the ESP specific IRAM_ATTR attribute.
    /// @param arg 
    void Mcp23017InterruptHandler(void* arg);
}
