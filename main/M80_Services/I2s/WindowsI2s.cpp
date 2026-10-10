#include "WindowsI2s.hpp"

WindowsI2s::WindowsI2s()
: _port(0),
  _sampleRate(16000),
  _bitsPerSample(16),
  _channels(1),
  _inputPosition(0),
  _started(false)
{
}

bool WindowsI2s::ParamConfig(
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
    _sampleRate = sampleRate;
    _bitsPerSample = bitsPerSample;
    _channels = channels;
    return true;
}

bool WindowsI2s::DriverInstall(
    uint8_t port)
{
    return true;
}

bool WindowsI2s::Start(
    uint8_t port)
{
    _started = true;
    _inputPosition = 0;
    return true;
}

bool WindowsI2s::Stop(
    uint8_t port)
{
    _started = false;
    return true;
}

size_t WindowsI2s::Read(
    uint8_t port,
    void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    if (!_started || _inputData.empty())
    {
        return 0;
    }

    size_t bytesToRead = length;
    size_t samplesAvailable = _inputData.size() - _inputPosition;
    size_t samplesToRead = bytesToRead / sizeof(int16_t);

    if (samplesToRead > samplesAvailable)
    {
        samplesToRead = samplesAvailable;
        bytesToRead = samplesToRead * sizeof(int16_t);
    }

    if (bytesToRead == 0)
    {
        return 0;
    }

    memcpy(buffer, &_inputData[_inputPosition], bytesToRead);
    _inputPosition += samplesToRead;

    if (_inputPosition >= _inputData.size())
    {
        _inputPosition = 0;
    }

    return bytesToRead;
}

size_t WindowsI2s::Write(
    uint8_t port,
    const void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    return length;
}

bool WindowsI2s::SetClock(
    uint8_t port,
    uint32_t sampleRate)
{
    _sampleRate = sampleRate;
    return true;
}

void WindowsI2s::SetInputData(
    const std::vector<int16_t>& data)
{
    _inputData = data;
    _inputPosition = 0;
}
