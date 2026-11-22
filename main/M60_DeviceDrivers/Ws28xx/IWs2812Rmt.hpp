#pragma once

#include <cstdint>

namespace M60::Ws28xx
{
    class IWs2812Rmt
    {
    public:
        virtual ~IWs2812Rmt() = default;

        virtual void Initialize() = 0;

        virtual void Send(
            const uint8_t* grb_data) = 0;
    };
}
