#pragma once

#include "../../M60_DeviceDrivers/Audio/AudioDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

class AudioDeviceModel : public DeviceModel
{
public:
    AudioDeviceModel();
    ~AudioDeviceModel() = default;

    void Initialize() override;

    uint8_t GetBclkPin() const;
    void SetBclkPin(
        uint8_t bclkPin);

    uint8_t GetWsPin() const;
    void SetWsPin(
        uint8_t wsPin);

    uint8_t GetDinPin() const;
    void SetDinPin(
        uint8_t dinPin);

    uint8_t GetDoutPin() const;
    void SetDoutPin(
        uint8_t doutPin);

    uint32_t GetSampleRate() const;
    void SetSampleRate(
        uint32_t sampleRate);

    uint16_t GetBitsPerSample() const;
    void SetBitsPerSample(
        uint16_t bitsPerSample);

    uint8_t GetChannels() const;
    void SetChannels(
        uint8_t channels);

    uint8_t GetPort() const;
    void SetPort(
        uint8_t port);

private:
    uint8_t _port;
    uint8_t _bclkPin;
    uint8_t _wsPin;
    uint8_t _dinPin;
    uint8_t _doutPin;
    uint32_t _sampleRate;
    uint16_t _bitsPerSample;
    uint8_t _channels;
};
