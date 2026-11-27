#pragma once

#include "IWs28xxDeviceDriver.hpp"
#include "../DeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
#include <cstdint>
#include <memory>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M50::Ws28xx
{
    class IWs28xxDeviceModel;
}

namespace M60::Ws28xx
{
    class IWs2812Rmt;

    class Ws28xxDeviceDriver : public DeviceDriver, public IWs28xxDeviceDriver
    {
    public:
        Ws28xxDeviceDriver(
            uint16_t numberOfLeds,
            IWs2812Rmt& ws2812rmt,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        Ws28xxDeviceDriver(
            const Ws28xxDeviceDriver&) = delete;
        
        Ws28xxDeviceDriver& operator=(
            const Ws28xxDeviceDriver&) = delete;
        
        Ws28xxDeviceDriver(
            Ws28xxDeviceDriver&&) = delete;
        
        Ws28xxDeviceDriver& operator=(
            Ws28xxDeviceDriver&&) = delete;

        ~Ws28xxDeviceDriver() override;

        void Initialize() override;

        void WriteToLedStrip() override;

        void SetWs28xxDeviceModel(
            M50::Ws28xx::IWs28xxDeviceModel& ws28xxDeviceModel);

        M50::Ws28xx::IWs28xxDeviceModel& GetWs28xxDeviceModel();

    private:
        M50::Ws28xx::IWs28xxDeviceModel* _ws28xxDeviceModel;

        uint16_t _numberOfLeds;

        IWs2812Rmt& _ws2812Rmt;
    };
}
