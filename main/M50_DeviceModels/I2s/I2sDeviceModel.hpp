#pragma once

#include "../../M60_DeviceDrivers/I2s/I2sDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

class I2sDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    I2sDeviceModel(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    I2sDeviceModel(
        const I2sDeviceModel&) = delete;
    
    I2sDeviceModel& operator=(
        const I2sDeviceModel&) = delete;
    
    I2sDeviceModel(
        I2sDeviceModel&&) = delete;
    
    I2sDeviceModel& operator=(
        I2sDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~I2sDeviceModel() override;

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
