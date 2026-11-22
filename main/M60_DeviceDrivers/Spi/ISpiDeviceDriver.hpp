#pragma once

#include <cstdint>

namespace M80::Spi
{
    class ISpi;
}

namespace M60::Spi
{
    class ISpiDeviceDriver
    {
    public:
        virtual ~ISpiDeviceDriver() = default;

        virtual M80::Spi::ISpi& GetSpi() = 0;

        virtual void Initialize() = 0;
    };
}
