#pragma once

#include "../../../L3_Messages/Types.hpp"

class IoPins;

class Joystick
{
public:
    Joystick(IoPins& ioPins, Types::EJoystickId joystickId);
    ~Joystick();

    Types::EJoystickDirection GetDirection();
    bool GetButtonState();

private:
    IoPins& _ioPins;
    Types::EJoystickId _id;
    Types::EJoystickDirection _direction;
    bool _buttonState;
};
