#include "ButtonState.hpp"

ButtonState::ButtonState() 
: _state(false) 
{
}

bool ButtonState::GetState() const
{
    return _state; 
}

void ButtonState::SetState(bool state)
{
    _state = state; 
}
