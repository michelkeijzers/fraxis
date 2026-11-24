#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

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
        
        virtual void SendToDisplay() = 0;
    };
}
