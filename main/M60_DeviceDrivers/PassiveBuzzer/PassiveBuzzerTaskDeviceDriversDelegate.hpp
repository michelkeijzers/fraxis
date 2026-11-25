#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::LOg
{
    class ILog;
}

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        explicit PassiveBuzzerTaskDeviceDriversDelegate(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log);

        PassiveBuzzerTaskDeviceDriversDelegate(
            const PassiveBuzzerTaskDeviceDriversDelegate&) = delete;

        PassiveBuzzerTaskDeviceDriversDelegate& operator=(
            const PassiveBuzzerTaskDeviceDriversDelegate&) = delete;
        
        PassiveBuzzerTaskDeviceDriversDelegate(
            PassiveBuzzerTaskDeviceDriversDelegate&&) = delete;
        
        PassiveBuzzerTaskDeviceDriversDelegate& operator=(
            PassiveBuzzerTaskDeviceDriversDelegate&&) = delete;

        ~PassiveBuzzerTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();
    };
}
