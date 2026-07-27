#include "IoPins.hpp"
#include "../../../L3_Messages/Types.hpp"
#include <cstdint>

IoPins::IoPins()
{
}

IoPins::~IoPins()
{
}

Joystick& IoPins::GetJoystick(Types::EJoystickId joystickId)
{
    return _joysticks[static_cast<uint8_t>(joystickId)];
}

Led& IoPins::GetLed(Types::ELedId ledId)
{
    return _leds[ledId];
}

SystemButton& IoPins::GetSystemButton()
{
    return _systemButton;
}
