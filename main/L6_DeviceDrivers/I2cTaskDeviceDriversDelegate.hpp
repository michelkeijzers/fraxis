#pragma once

#include <cstdint>

class Context;

class I2cTaskDeviceDriversDelegate
{
public:
    const uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz
    const uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

    I2cTaskDeviceDriversDelegate(Context& context);
    ~I2cTaskDeviceDriversDelegate();

    void Run();

private:
    Context& _context;

    uint64_t _lastMcpWriteUs = 0;
    uint64_t _lastLcdWriteUs = 0;    
};
