#include "JoystickState.hpp"

JoystickState::JoystickState() 
: _direction(EDirection::Centered), _buttonState(false) 
{
}

JoystickState::EDirection JoystickState::GetDirection() const
{
    return _direction; 
}

void JoystickState::SetDirection(EDirection direction)
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
