#pragma once

#include "ButtonState.hpp"
#include "JoystickState.hpp"

class IoStates
{
public:
    IoStates();
    ~IoStates();

    enum class EJoystickId
    {
        Player1 = 0,
        Player2 = 1
    };

    JoystickState& GetJoystickState(EJoystickId joystickId);
    ButtonState& GetSystemButtonState();

private:
    ButtonState _systemButtonState;
    JoystickState _joystickStates[2];
};
