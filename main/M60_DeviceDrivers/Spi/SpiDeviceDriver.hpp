#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

class Spi;

class SpiDeviceDriver : public DeviceDriver
{
public:
    SpiDeviceDriver();
    ~SpiDeviceDriver() = default;

    Spi& GetSpi();
    void SetSpi(
        Spi& spi);
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

    Spi* _spi;
};
