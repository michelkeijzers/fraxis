#include "Buzzer.hpp"
#include "../../../M50_DeviceModels/Audio/Buzzer/BuzzerDeviceModel.hpp"

Buzzer::Buzzer()
: _buzzerDeviceModel(nullptr),
  _frequency(0),
  _isPlaying(false)
{
}

void Buzzer::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _buzzerDeviceModel = static_cast<BuzzerDeviceModel*>(&deviceModel);
}

void Buzzer::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
}

uint32_t Buzzer::GetFrequency() const
{
    return _frequency;
}

void Buzzer::Start()
{
    _isPlaying = true;
}

void Buzzer::Stop()
{
    _isPlaying = false;
}

bool Buzzer::IsPlaying() const
{
    return _isPlaying;
}

BuzzerDeviceModel& Buzzer::GetBuzzerDeviceModel()
{
    return *_buzzerDeviceModel;
}
