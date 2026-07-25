#include "JoystickState.hpp"

JoystickState::JoystickState() 
: _direction(Joystick::EDirection::Centered), _buttonState(false) 
{
}

Joystick::EDirection JoystickState::GetDirection() const
{
    return _direction; 
}

void JoystickState::SetDirection(Joystick::EDirection direction)
{
    _direction = direction; 
}

bool JoystickState::GetButtonState() const
{
    return _buttonState; 
}

void JoystickState::SetButtonState(bool state)
{
    _buttonState = state; 
}
