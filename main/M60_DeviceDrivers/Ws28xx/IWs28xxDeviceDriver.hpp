#pragma once

namespace M50::Ws28xx
{
    class Ws28xxDeviceModel;
}

namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver
    {
    public:
        virtual ~IWs28xxDeviceDriver() = default;

        virtual void WriteToLedStrip() = 0;
    };
}
