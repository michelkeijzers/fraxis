#pragma once

namespace M50::Ws28xx
{
    class IWs28xxDeviceModel;
}

namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver
    {
    public:
        virtual ~IWs28xxDeviceDriver() = default;

        virtual void SetWs28xxDeviceModel(
            M50::Ws28xx::IWs28xxDeviceModel& ws28xxDeviceModel) = 0;

        virtual M50::Ws28xx::IWs28xxDeviceModel& GetWs28xxDeviceModel() = 0;

        virtual void WriteToLedStrip() = 0;
    };
}
