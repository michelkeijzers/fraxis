#pragma once

#include "../../M60_DeviceDrivers/DeviceDriver.hpp"
#include <cstdint>

class I2s;
class RtosTask;

class AudioDeviceDriver : public DeviceDriver
{
public:
    AudioDeviceDriver();
    ~AudioDeviceDriver() = default;

    I2s& GetI2s();
    void SetI2s(
        I2s& i2s);

    void SetConfiguration(
        uint8_t port,
        uint8_t bclkPin,
        uint8_t wsPin,
        uint8_t dinPin,
        uint8_t doutPin,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint8_t channels);

    void SetRtosTask(
        RtosTask& rtosTask);

    void Initialize() override;

    size_t Read(
        void* buffer,
        size_t length,
        uint32_t timeoutInMs);

    size_t Write(
        const void* buffer,
        size_t length,
        uint32_t timeoutInMs);

    bool Start();
    bool Stop();

private:
    uint8_t _port;
    uint8_t _bclkPin;
    uint8_t _wsPin;
    uint8_t _dinPin;
    uint8_t _doutPin;
    uint32_t _sampleRate;
    uint16_t _bitsPerSample;
    uint8_t _channels;

    I2s* _i2s;
    RtosTask* _rtosTask;
};
