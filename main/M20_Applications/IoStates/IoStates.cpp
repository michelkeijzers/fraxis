#include "IoStates.hpp"
#include <cstdint>

#include "../../M30_Messages/Types.hpp"

JoystickState& IoStates::GetJoystickState(
    Types::EJoystickId joystickId)
{
    return _joystickStates[static_cast<uint8_t>(joystickId)];
}

ButtonState& IoStates::GetSystemButtonState()
{
    return _systemButtonState;
}
