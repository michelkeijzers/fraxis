#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M60::I2s
{
    class I2sTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        explicit I2sTaskDeviceDriversDelegate(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log);

        I2sTaskDeviceDriversDelegate(
            const I2sTaskDeviceDriversDelegate&) = delete;

        I2sTaskDeviceDriversDelegate& operator=(
            const I2sTaskDeviceDriversDelegate&) = delete;
        
        I2sTaskDeviceDriversDelegate(
            I2sTaskDeviceDriversDelegate&&) = delete;
        
        I2sTaskDeviceDriversDelegate& operator=(
            I2sTaskDeviceDriversDelegate&&) = delete;

        ~I2sTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();
    };
}
