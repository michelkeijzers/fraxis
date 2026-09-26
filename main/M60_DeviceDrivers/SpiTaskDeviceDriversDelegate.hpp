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
    ~SpiTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
    SpiInputQueueWriter _spiInputQueueWriter;

    //uint64_t _lastWriteUs;
    //uint64_t _lastLcdWriteUs;    
    //uint64_t _lastTm1637WriteUs;
    //Types::ETm1637Id _nextTm1637IdToUpdate;
};
