#pragma once

#include "../../L4_DomainModels/I2c/IoPins/Joystick.hpp"

class JoystickState
{
public:
    JoystickState();
    
    Joystick::EDirection GetDirection() const;
    void SetDirection(Joystick::EDirection direction);

    bool GetButtonState() const;
    void SetButtonState(bool state);

private:
    Joystick::EDirection _direction;
    bool _buttonState;
};
