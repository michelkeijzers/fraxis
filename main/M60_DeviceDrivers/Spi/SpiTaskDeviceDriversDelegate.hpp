#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"

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
        // TODO  SpiInputQueueWriter& _spiInputQueueWriter;
    };
}
