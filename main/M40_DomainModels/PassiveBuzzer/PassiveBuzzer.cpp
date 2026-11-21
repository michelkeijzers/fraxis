#include "PassiveBuzzer.hpp"
#include "../../M50_DeviceModels/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"

PassiveBuzzer::PassiveBuzzer()
:
    _passiveBuzzerDeviceModel(nullptr),
    _frequency(0),
    _isPlaying(false)
{
}

void PassiveBuzzer::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _passiveBuzzerDeviceModel = static_cast<PassiveBuzzerDeviceModel*>(&deviceModel);
}

void PassiveBuzzer::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
}

uint32_t PassiveBuzzer::GetFrequency() const
{
    return _frequency;
}

void PassiveBuzzer::Start()
{
    _isPlaying = true;
}

void PassiveBuzzer::Stop()
{
    _isPlaying = false;
}

bool PassiveBuzzer::IsPlaying() const
{
    return _isPlaying;
}

PassiveBuzzerDeviceModel& PassiveBuzzer::GetPassiveBuzzerDeviceModel()
{
    return *_passiveBuzzerDeviceModel;
}
