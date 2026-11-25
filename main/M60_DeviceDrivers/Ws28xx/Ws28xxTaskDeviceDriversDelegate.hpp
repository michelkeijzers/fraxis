#pragma once

#include "../TaskDeviceDriversDelegate.hpp"

namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::ILog
{
    class ILog;
}

namespace M60::Ws28xx
{
    class Ws28xxTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        explicit Ws28xxTaskDeviceDriversDelegate(
            M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log);

        Ws28xxTaskDeviceDriversDelegate(
            const Ws28xxTaskDeviceDriversDelegate&) = delete;

        Ws28xxTaskDeviceDriversDelegate& operator=(
            const Ws28xxTaskDeviceDriversDelegate&) = delete;

        Ws28xxTaskDeviceDriversDelegate(
            Ws28xxTaskDeviceDriversDelegate&&) = delete;

        Ws28xxTaskDeviceDriversDelegate& operator=(
            Ws28xxTaskDeviceDriversDelegate&&) = delete;

        ~Ws28xxTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        M60::Ws28xx::IWs28xxDeviceDriver& _ws28xxDeviceDriver;
    };
}
