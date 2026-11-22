#pragma once

#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"

class Context;

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M60::Spi
{
    class SpiTaskDeviceDriversDelegate
    {
    public:
        explicit SpiTaskDeviceDriversDelegate(
            Context& context,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::String::IStringUtilities& stringUtilities);

        SpiTaskDeviceDriversDelegate(
            const SpiTaskDeviceDriversDelegate&) = delete;
        
        SpiTaskDeviceDriversDelegate& operator=(
            const SpiTaskDeviceDriversDelegate&) = delete;
        
        SpiTaskDeviceDriversDelegate(
            SpiTaskDeviceDriversDelegate&&) = delete;
        
        SpiTaskDeviceDriversDelegate& operator=(
            SpiTaskDeviceDriversDelegate&&) = delete;

        ~SpiTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Context& _context;

        SpiInputQueueWriter _spiInputQueueWriter;

        // NOSONAR TODO SPI
        //std::chrono::milliseconds _lastWriteUs;
        
        //std::chrono::milliseconds _lastLcdWriteUs;    
        
        //std::chrono::milliseconds _lastTm1637WriteUs;
        
        //Types::ETm1637Id _nextTm1637IdToUpdate;
    };
}
