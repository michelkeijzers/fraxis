#pragma once

/// @brief Interrupt handler for the MCP23017 which is implemented in platform specific versions due to the need for
/// the ESP specific IRAM_ATTR attribute.
/// @param arg 
void InterruptHandler(void *arg);
