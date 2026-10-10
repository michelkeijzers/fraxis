#include "AudioDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M80_Services/I2s/I2s.hpp"
#include "../../M30_Messages/Types.hpp"

AudioDeviceDriver::AudioDeviceDriver()
: _port(0),
  _bclkPin(0),
  _wsPin(0),
  _dinPin(0),
  _doutPin(0),
  _sampleRate(16000),
  _bitsPerSample(16),
  _channels(1),
  _i2s(nullptr),
  _rtosTask(nullptr)
{
}

void AudioDeviceDriver::SetConfiguration(
    uint8_t port,
    uint8_t bclkPin,
    uint8_t wsPin,
    uint8_t dinPin,
    uint8_t doutPin,
    uint32_t sampleRate,
    uint16_t bitsPerSample,
    uint8_t channels)
{
    _port = port;
    _bclkPin = bclkPin;
    _wsPin = wsPin;
    _dinPin = dinPin;
    _doutPin = doutPin;
    _sampleRate = sampleRate;
    _bitsPerSample = bitsPerSample;
    _channels = channels;
}

I2s& AudioDeviceDriver::GetI2s()
{
    return *_i2s;
}

void AudioDeviceDriver::SetI2s(
    I2s& i2s)
{
    _i2s = &i2s;
}

void AudioDeviceDriver::SetRtosTask(
    RtosTask& rtosTask)
{
    _rtosTask = &rtosTask;
}

void AudioDeviceDriver::Initialize()
{
    Assert::IsTrue(
        Types::ETaskId::AudioTask,
        GetI2s().ParamConfig(_port, _bclkPin, _wsPin, _dinPin, _doutPin, _sampleRate, _bitsPerSample, _channels),
        "Failed to param config");
    Assert::IsTrue(
        Types::ETaskId::AudioTask,
        GetI2s().DriverInstall(_port),
        "Failed to install I2S driver");
    MarkInitialized();
}

size_t AudioDeviceDriver::Read(
    void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    Assert::IsTrue(Types::ETaskId::AudioTask, IsInitialized());
    return GetI2s().Read(_port, buffer, length, timeoutInMs);
}

size_t AudioDeviceDriver::Write(
    const void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    Assert::IsTrue(Types::ETaskId::AudioTask, IsInitialized());
    return GetI2s().Write(_port, buffer, length, timeoutInMs);
}

bool AudioDeviceDriver::Start()
{
    return GetI2s().Start(_port);
}

bool AudioDeviceDriver::Stop()
{
    return GetI2s().Stop(_port);
}
