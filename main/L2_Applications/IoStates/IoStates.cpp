#include "IoStates.hpp"
#include <cstdint>

IoStates::IoStates()
{
}

IoStates::~IoStates()
{
}

JoystickState& IoStates::GetJoystickState(IoStates::EJoystickId joystickId)
{
    return _joystickStates[static_cast<uint8_t>(joystickId)];
}

ButtonState& IoStates::GetSystemButtonState()
{
    return _systemButtonState;
}
