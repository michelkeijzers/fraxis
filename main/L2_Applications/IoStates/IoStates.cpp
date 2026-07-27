#include "IoStates.hpp"
#include <cstdint>

#include "../../L3_Messages/Types.hpp"
IoStates::IoStates()
{
}

IoStates::~IoStates()
{
}

JoystickState& IoStates::GetJoystickState(Types::EJoystickId joystickId)
{
    return _joystickStates[static_cast<uint8_t>(joystickId)];
}

ButtonState& IoStates::GetSystemButtonState()
{
    return _systemButtonState;
}
