#pragma once

#include "../L4_DomainModels/I2c/I2cInputQueueWriter.hpp"

#include <cstdint>

class Context;

class I2cTaskDeviceDriversDelegate
{
public:
    const uint32_t MCP23017_WRITE_GPIOS_FREQUENCY  = 100; // Hz
    const uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY =   5; // Hz
    const uint32_t TM1637_WRITE_DISPLAY_FREQUENCY  =  20; // Hz

    I2cTaskDeviceDriversDelegate(Context& context);
    ~I2cTaskDeviceDriversDelegate();

    void Initialize();

    void Run();

private:
    Context& _context;

    uint64_t _lastMcpWriteUs = 0;
    uint64_t _lastLcdWriteUs = 0;    

    I2cInputQueueWriter _i2cInputQueueWriter;
};
