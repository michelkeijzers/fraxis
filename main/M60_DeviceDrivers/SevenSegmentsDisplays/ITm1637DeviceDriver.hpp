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

        virtual void SetGpio(
            M80::Gpio::IGpio& gpio) = 0;
        
        virtual void SetPinsConfiguration(
            uint8_t clockPin, 
            uint8_t dataPin) = 0;
        
        virtual void SendToDisplay() = 0;
    };
}
