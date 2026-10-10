#include "BuzzerDeviceModel.hpp"

BuzzerDeviceModel::BuzzerDeviceModel()
: _pwmPin(0),
  _frequency(0),
  _isPlaying(false)
{
}

void BuzzerDeviceModel::Initialize()
{
}

uint8_t BuzzerDeviceModel::GetPwmPin() const
{
    return _pwmPin;
}

void BuzzerDeviceModel::SetPwmPin(
    uint8_t pwmPin)
{
    _pwmPin = pwmPin;
}

uint32_t BuzzerDeviceModel::GetFrequency() const
{
    return _frequency;
}

void BuzzerDeviceModel::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
}

bool BuzzerDeviceModel::IsPlaying() const
{
    return _isPlaying;
}

void BuzzerDeviceModel::SetPlaying(
    bool playing)
{
    _isPlaying = playing;
}
