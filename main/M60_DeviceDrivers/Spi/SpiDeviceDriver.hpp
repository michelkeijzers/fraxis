#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

namespace M80::Spi
{
    class Spi;
}

class SpiDeviceDriver : public DeviceDriver
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    SpiDeviceDriver();

    SpiDeviceDriver(const SpiDeviceDriver&) = delete;
    SpiDeviceDriver& operator=(const SpiDeviceDriver&) = delete;
    SpiDeviceDriver(SpiDeviceDriver&&) = delete;
    SpiDeviceDriver& operator=(SpiDeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~SpiDeviceDriver() override;

    M80::Spi::Spi& GetSpi();
    void SetSpi(
        M80::Spi::Spi& spi);
    void SetConfiguration(
        uint8_t port,
        uint8_t mosiPin,
        uint8_t misoPin,
        uint8_t sclkPin,
        uint32_t frequency);
    void Initialize() override;

private:
    void AssertValidPort(
        uint8_t port);

    uint8_t _port;
    uint8_t _mosiPin;
    uint8_t _misoPin;
    uint8_t _sclkPin;
    uint32_t _frequency;

    M80::Spi::Spi* _spi;
};
