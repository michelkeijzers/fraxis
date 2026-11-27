#include "I2sDeviceModel.hpp"

namespace M50::I2s
{
    I2sDeviceModel::I2sDeviceModel(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities)
        :
        DeviceModel(assert, log, stringUtilities),
        _port(0),
        _bclkPin(0),
        _wsPin(0),
        _dinPin(0),
        _doutPin(0),
        _sampleRate(16000),
        _bitsPerSample(16),
        _channels(1)
    {
        // No functionality required
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    I2sDeviceModel::~I2sDeviceModel() = default;

    void I2sDeviceModel::Initialize()
    {
        // No functionality rerquired.
    }

    uint8_t I2sDeviceModel::GetBclkPin() const
    {
        return _bclkPin;
    }

    void I2sDeviceModel::SetBclkPin(
        uint8_t bclkPin)
    {
        _bclkPin = bclkPin;
    }

    uint8_t I2sDeviceModel::GetWsPin() const
    {
        return _wsPin;
    }

    void I2sDeviceModel::SetWsPin(
        uint8_t wsPin)
    {
        _wsPin = wsPin;
    }

    uint8_t I2sDeviceModel::GetDinPin() const
    {
        return _dinPin;
    }

    void I2sDeviceModel::SetDinPin(
        uint8_t dinPin)
    {
        _dinPin = dinPin;
    }

    uint8_t I2sDeviceModel::GetDoutPin() const
    {
        return _doutPin;
    }

    void I2sDeviceModel::SetDoutPin(
        uint8_t doutPin)
    {
        _doutPin = doutPin;
    }

    uint32_t I2sDeviceModel::GetSampleRate() const
    {
        return _sampleRate;
    }

    void I2sDeviceModel::SetSampleRate(
        uint32_t sampleRate)
    {
        _sampleRate = sampleRate;
    }

    uint16_t I2sDeviceModel::GetBitsPerSample() const
    {
        return _bitsPerSample;
    }

    void I2sDeviceModel::SetBitsPerSample(
        uint16_t bitsPerSample)
    {
        _bitsPerSample = bitsPerSample;
    }

    uint8_t I2sDeviceModel::GetChannels() const
    {
        return _channels;
    }

    void I2sDeviceModel::SetChannels(
        uint8_t channels)
    {
        _channels = channels;
    }

    uint8_t I2sDeviceModel::GetPort() const
    {
        return _port;
    }

    void I2sDeviceModel::SetPort(
        uint8_t port)
    {
        _port = port;
    }
}
