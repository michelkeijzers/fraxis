#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"

class Context;
class SpiInputQueueWriter;

namespace M60::Spi
{
    class SpiTaskDeviceDriversDelegate;
}

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
    class SpiTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        explicit SpiTaskDeviceDriversDelegate(
            SpiInputQueueWriter& spiInputQueueWriter,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log);

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
        SpiInputQueueWriter& _spiInputQueueWriter;

        // NOSONAR TODO SPI
        //std::chrono::milliseconds _lastWriteUs;
        
        //std::chrono::milliseconds _lastLcdWriteUs;    
        
        //std::chrono::milliseconds _lastTm1637WriteUs;
        
        //Types::ETm1637Id _nextTm1637IdToUpdate;
    };
}
