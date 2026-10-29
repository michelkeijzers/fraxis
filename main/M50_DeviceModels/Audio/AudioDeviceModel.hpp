#pragma once

#include "../../M60_DeviceDrivers/Audio/AudioDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

class AudioDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    AudioDeviceModel();

    AudioDeviceModel(const AudioDeviceModel&) = delete;
    AudioDeviceModel& operator=(const AudioDeviceModel&) = delete;
    AudioDeviceModel(AudioDeviceModel&&) = delete;
    AudioDeviceModel& operator=(AudioDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~AudioDeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetBclkPin() const;
    void SetBclkPin(
        uint8_t bclkPin);

    [[nodiscard]] uint8_t GetWsPin() const;
    void SetWsPin(
        uint8_t wsPin);

    [[nodiscard]] uint8_t GetDinPin() const;
    void SetDinPin(
        uint8_t dinPin);

    [[nodiscard]] uint8_t GetDoutPin() const;
    void SetDoutPin(
        uint8_t doutPin);

    [[nodiscard]] uint32_t GetSampleRate() const;
    void SetSampleRate(
        uint32_t sampleRate);

    [[nodiscard]] uint16_t GetBitsPerSample() const;
    void SetBitsPerSample(
        uint16_t bitsPerSample);

    [[nodiscard]] uint8_t GetChannels() const;
    void SetChannels(
        uint8_t channels);

    [[nodiscard]] uint8_t GetPort() const;
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
