#include "AudioDeviceModel.hpp"

AudioDeviceModel::AudioDeviceModel()
: _port(0),
  _bclkPin(0),
  _wsPin(0),
  _dinPin(0),
  _doutPin(0),
  _sampleRate(16000),
  _bitsPerSample(16),
  _channels(1)
{
}

void AudioDeviceModel::Initialize()
{
}

uint8_t AudioDeviceModel::GetBclkPin() const
{
    return _bclkPin;
}

void AudioDeviceModel::SetBclkPin(
    uint8_t bclkPin)
{
    _bclkPin = bclkPin;
}

uint8_t AudioDeviceModel::GetWsPin() const
{
    return _wsPin;
}

void AudioDeviceModel::SetWsPin(
    uint8_t wsPin)
{
    _wsPin = wsPin;
}

uint8_t AudioDeviceModel::GetDinPin() const
{
    return _dinPin;
}

void AudioDeviceModel::SetDinPin(
    uint8_t dinPin)
{
    _dinPin = dinPin;
}

uint8_t AudioDeviceModel::GetDoutPin() const
{
    return _doutPin;
}

void AudioDeviceModel::SetDoutPin(
    uint8_t doutPin)
{
    _doutPin = doutPin;
}

uint32_t AudioDeviceModel::GetSampleRate() const
{
    return _sampleRate;
}

void AudioDeviceModel::SetSampleRate(
    uint32_t sampleRate)
{
    _sampleRate = sampleRate;
}

uint16_t AudioDeviceModel::GetBitsPerSample() const
{
    return _bitsPerSample;
}

void AudioDeviceModel::SetBitsPerSample(
    uint16_t bitsPerSample)
{
    _bitsPerSample = bitsPerSample;
}

uint8_t AudioDeviceModel::GetChannels() const
{
    return _channels;
}

void AudioDeviceModel::SetChannels(
    uint8_t channels)
{
    _channels = channels;
}

uint8_t AudioDeviceModel::GetPort() const
{
    return _port;
}

void AudioDeviceModel::SetPort(
    uint8_t port)
{
    _port = port;
}
