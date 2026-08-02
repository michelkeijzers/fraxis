#pragma once

#include "ButtonState.hpp"
#include "JoystickState.hpp"
#include "../../L3_Messages/Types.hpp"

class IoStates
{
public:
    IoStates();
    ~IoStates();

    JoystickState& GetJoystickState(
        Types::EJoystickId joystickId);
    ButtonState& GetSystemButtonState();

private:
    ButtonState _systemButtonState;
    JoystickState _joystickStates[2];
};
