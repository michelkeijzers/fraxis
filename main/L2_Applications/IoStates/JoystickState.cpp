#include "JoystickState.hpp"

JoystickState::JoystickState() 
: _direction(EDirection::Centered), _buttonState(false) 
{
}

bool JoystickState::GetButtonState() const
{
    return _buttonState; 
}

void JoystickState::SetButtonState(bool state)
{
    _buttonState = state; 
}
