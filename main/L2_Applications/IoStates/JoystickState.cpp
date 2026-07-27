#include "JoystickState.hpp"
#include "../../L3_Messages/Types.hpp"

JoystickState::JoystickState() 
: _direction(Types::EJoystickDirection::Centered), _buttonState(false) 
{
}

Types::EJoystickDirection JoystickState::GetDirection() const
{
    return _direction; 
}

void JoystickState::SetDirection(Types::EJoystickDirection direction)
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
