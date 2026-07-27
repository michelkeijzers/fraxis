#pragma once

#include "../../L3_Messages/Types.hpp"

class JoystickState
{
public:
    JoystickState();
    
    Types::EJoystickDirection GetDirection() const;
    void SetDirection(Types::EJoystickDirection direction);

    bool GetButtonState() const;
    void SetButtonState(bool state);

private:
    Types::EJoystickDirection _direction;
    bool _buttonState;
};
