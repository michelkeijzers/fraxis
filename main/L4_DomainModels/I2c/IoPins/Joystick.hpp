#pragma once

#include "../../../L3_Messages/Types.hpp"

class Joystick
{
public:
    Joystick();
    ~Joystick();

    Types::EJoystickDirection GetDirection();
    bool GetButtonState();

private:
    Types::EJoystickDirection _direction;
    bool _buttonState;
};
