#pragma once

#include "ISpiDeviceDriver.hpp"
#include "../DeviceDriver.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M60::Spi
{
    class SpiDeviceDriver : public DeviceDriver, public ISpiDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        SpiDeviceDriver(
            uint8_t port,
            uint8_t mosiPin,
            uint8_t misoPin,
            uint8_t sclkPin,
            uint32_t frequency,
            M80::Spi::ISpi& spi,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        SpiDeviceDriver(
            const SpiDeviceDriver&) = delete;
        
        SpiDeviceDriver& operator=(
            const SpiDeviceDriver&) = delete;
        
        SpiDeviceDriver(
            SpiDeviceDriver&&) = delete;
        
        SpiDeviceDriver& operator=(
            SpiDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~SpiDeviceDriver() override;

        M80::Spi::ISpi& GetSpi() override;
        
        void Initialize() override;

    private:
        void AssertValidPort(
            uint8_t port);

        uint8_t _port;
        
        uint8_t _mosiPin;
        
        uint8_t _misoPin;
        
        uint8_t _sclkPin;
        
        uint32_t _frequency;

        M80::Spi::ISpi& _spi;
    };
}
