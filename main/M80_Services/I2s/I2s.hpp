#pragma once

#include <cstdint>
#include <cstddef>

class I2s
{
public:
    I2s() = default;
    virtual ~I2s() = default;

    virtual bool ParamConfig(
        uint8_t port,
        uint8_t bclkPin,
        uint8_t wsPin,
        uint8_t dinPin,
        uint8_t doutPin,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint8_t channels) = 0;

    virtual bool DriverInstall(
        uint8_t port) = 0;

    virtual bool Start(
        uint8_t port) = 0;

    virtual bool Stop(
        uint8_t port) = 0;

    virtual size_t Read(
        uint8_t port,
        void* buffer,
        size_t length,
        uint32_t timeoutInMs) = 0;

    virtual size_t Write(
        uint8_t port,
        const void* buffer,
        size_t length,
        uint32_t timeoutInMs) = 0;

    virtual bool SetClock(
        uint8_t port,
        uint32_t sampleRate) = 0;
};
