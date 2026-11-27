#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

namespace M50::SevenSegmentsDisplays
{
    class ITm1637DeviceModel;
}

namespace M80::Gpio
{
    class IGpio;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M60::SevenSegmentsDisplays
{
    class ITm1637DeviceDriver
    {
    public:
        virtual ~ITm1637DeviceDriver() = default;
        
        virtual void SetTm1637DeviceModel(
            M50::SevenSegmentsDisplays::ITm1637DeviceModel& tm1637DeviceModel) = 0;

        virtual M50::SevenSegmentsDisplays::ITm1637DeviceModel& GetTm1637DeviceModel() = 0;

        virtual void SendToDisplay() = 0;
    };
}
