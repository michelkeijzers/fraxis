#pragma once

#include "I2s.hpp"
#include <cstdint>
#include <vector>

class WindowsI2s : public I2s
{
public:
    WindowsI2s();
    ~WindowsI2s() = default;

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

    void SetInputData(
        const std::vector<int16_t>& data);

private:
    uint8_t _port;
    uint32_t _sampleRate;
    uint16_t _bitsPerSample;
    uint8_t _channels;
    std::vector<int16_t> _inputData;
    size_t _inputPosition;
    bool _started;
};
