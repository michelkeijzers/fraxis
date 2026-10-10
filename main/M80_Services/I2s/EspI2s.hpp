#ifdef ESP_PLATFORM

#pragma once

#include "I2s.hpp"
#include "driver/i2s.h"

class EspI2s : public I2s
{
public:
    EspI2s();
    ~EspI2s();

    bool ParamConfig(
        uint8_t port,
        uint8_t bclkPin,
        uint8_t wsPin,
        uint8_t dinPin,
        uint8_t doutPin,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint8_t channels) override;

    bool DriverInstall(
        uint8_t port) override;

    bool Start(
        uint8_t port) override;

    bool Stop(
        uint8_t port) override;

    size_t Read(
        uint8_t port,
        void* buffer,
        size_t length,
        uint32_t timeoutInMs) override;

    size_t Write(
        uint8_t port,
        const void* buffer,
        size_t length,
        uint32_t timeoutInMs) override;

    bool SetClock(
        uint8_t port,
        uint32_t sampleRate) override;

private:
    i2s_config_t _config;
    i2s_pin_config_t _pinConfig;
};

#endif // ESP_PLATFORM
