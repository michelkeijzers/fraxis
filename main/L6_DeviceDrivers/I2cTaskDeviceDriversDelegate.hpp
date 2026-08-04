#pragma once

#include "../L4_DomainModels/I2c/I2cInputQueueWriter.hpp"
#include "../L3_Messages/Types.hpp"

#include <cstdint>

class Context;

class I2cTaskDeviceDriversDelegate
{
public:
    static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY  = 100; // Hz
    static constexpr  uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY =   5; // Hz
    
    /// @brief The TM1637 displays are updated in alternating loops, meaning the actual maximum frequency 
    /// is 180 / 3 = 60 Hz
    static constexpr uint32_t TM1637_WRITE_DISPLAY_FREQUENCY  = 180; // Hz

    explicit I2cTaskDeviceDriversDelegate(
        Context& context);
    ~I2cTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
    I2cInputQueueWriter _i2cInputQueueWriter;

    uint64_t _lastMcpWriteUs;
    uint64_t _lastLcdWriteUs;    
    uint64_t _lastTm1637WriteUs;
    Types::ETm1637Id _nextTm1637IdToUpdate;
};
