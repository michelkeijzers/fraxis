#pragma once

#include "../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"
#include "../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

class SpiTaskDeviceDriversDelegate
{
public:
    explicit SpiTaskDeviceDriversDelegate(
        Context& context);
        
    SpiTaskDeviceDriversDelegate(const SpiTaskDeviceDriversDelegate&) = delete;
    SpiTaskDeviceDriversDelegate& operator=(const SpiTaskDeviceDriversDelegate&) = delete;
    SpiTaskDeviceDriversDelegate(SpiTaskDeviceDriversDelegate&&) = delete;
    SpiTaskDeviceDriversDelegate& operator=(SpiTaskDeviceDriversDelegate&&) = delete;

    ~SpiTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
    SpiInputQueueWriter _spiInputQueueWriter;

    //std::chrono::milliseconds _lastWriteUs;
    //std::chrono::milliseconds _lastLcdWriteUs;    
    //std::chrono::milliseconds _lastTm1637WriteUs;
    //Types::ETm1637Id _nextTm1637IdToUpdate;
};
