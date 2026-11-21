#include "PassiveBuzzerDeviceModel.hpp"

PassiveBuzzerDeviceModel::PassiveBuzzerDeviceModel(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
: 
    DeviceModel(assert, stringUtilities),
    _pwmPin(0),
    _frequency(0),
    _isPlaying(false)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
PassiveBuzzerDeviceModel::~PassiveBuzzerDeviceModel() = default;

void PassiveBuzzerDeviceModel::Initialize()
{
}

uint8_t PassiveBuzzerDeviceModel::GetPwmPin() const
{
    return _pwmPin;
}

void PassiveBuzzerDeviceModel::SetPwmPin(
    uint8_t pwmPin)
{
    _pwmPin = pwmPin;
}

uint32_t PassiveBuzzerDeviceModel::GetFrequency() const
{
    return _frequency;
}

void PassiveBuzzerDeviceModel::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
}

bool PassiveBuzzerDeviceModel::IsPlaying() const
{
    return _isPlaying;
}

void PassiveBuzzerDeviceModel::SetPlaying(
    bool playing)
{
    _isPlaying = playing;
}
