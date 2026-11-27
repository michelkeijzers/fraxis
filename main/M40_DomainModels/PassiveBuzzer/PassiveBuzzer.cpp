#include "PassiveBuzzer.hpp"
#include "../../M50_DeviceModels/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"

PassiveBuzzer::PassiveBuzzer(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:
    DomainModel(assert, log),
    _passiveBuzzerDeviceModel(nullptr),
    _frequency(0),
    _isPlaying(false)
{
}

void PassiveBuzzer::SetDeviceModel(
    M50::IDeviceModel& deviceModel)
{
    _passiveBuzzerDeviceModel = 
        static_cast<M50::PassiveBuzzer::PassiveBuzzerDeviceModel*>(&deviceModel);
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

M50::PassiveBuzzer::PassiveBuzzerDeviceModel& PassiveBuzzer::GetPassiveBuzzerDeviceModel()
{
    return *_passiveBuzzerDeviceModel;
}
