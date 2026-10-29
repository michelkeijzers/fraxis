#include "BuzzerDeviceDriver.hpp"
#include "../../../M90_Utilities/Assert/Assert.hpp"
#include "../../../M80_Services/Pwm/Pwm.hpp"
#include "../../../M30_Messages/Types.hpp"

BuzzerDeviceDriver::BuzzerDeviceDriver()
: _pwmPin(0),
  _frequency(0),
  _pwm(nullptr),
  _rtosTask(nullptr)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
BuzzerDeviceDriver::~BuzzerDeviceDriver() = default;

bool BuzzerDeviceDriver::IsInitialized() const
{
    return _pwm != nullptr;
}

void BuzzerDeviceDriver::Initialize()
{
    //_pwm = new Pwm(_pwmPin, _rtosTask);  // NOSONAR TODO
}

Pwm& BuzzerDeviceDriver::GetPwm()
{
    return *_pwm;
}

void BuzzerDeviceDriver::SetPwm(
    Pwm& pwm)
{
    _pwm = &pwm;
}

void BuzzerDeviceDriver::SetConfiguration(
    uint8_t pwmPin)
{
    _pwmPin = pwmPin;
}

void BuzzerDeviceDriver::SetRtosTask(
    RtosTask& rtosTask)
{
    _rtosTask = &rtosTask;
}

void BuzzerDeviceDriver::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
    if (IsInitialized())
    {
        GetPwm().SetFrequency(frequency);
    }
}

void BuzzerDeviceDriver::Start()
{
    if (_frequency > 0)
    {
        GetPwm().SetFrequency(_frequency);
        GetPwm().Start();
    }
}

void BuzzerDeviceDriver::Stop()
{
    GetPwm().Stop();
}
