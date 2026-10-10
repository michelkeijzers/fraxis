#include "WindowsPwm.hpp"

WindowsPwm::WindowsPwm()
: _pin(0),
  _frequency(0),
  _dutyCycle(0.0f),
  _started(false)
{
}

bool WindowsPwm::Config(
    uint8_t pin,
    uint32_t frequency,
    float dutyCycle)
{
    _pin = pin;
    _frequency = frequency;
    _dutyCycle = dutyCycle;
    return true;
}

bool WindowsPwm::Start()
{
    _started = true;
    return true;
}

bool WindowsPwm::Stop()
{
    _started = false;
    return true;
}

bool WindowsPwm::SetFrequency(
    uint32_t frequency)
{
    _frequency = frequency;
    return true;
}

bool WindowsPwm::SetDutyCycle(
    float dutyCycle)
{
    _dutyCycle = dutyCycle;
    return true;
}
