#pragma once

#include "Ws2812Rmt.hpp"
#include <cstdint>
#include <memory>

class Ws28xxDeviceModel;

namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver
    {
    public:
        virtual ~IWs28xxDeviceDriver() = default;

        virtual void SetRmt(
            M80::Rmt::IRmt& rmt) = 0;

        virtual void SetDataPin(
            uint8_t dataPin) = 0;
        
        [[nodiscard]] virtual uint8_t GetDataPin() const = 0;

        virtual void WriteToLedStrip() = 0;
    };
}
