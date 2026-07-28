#include "SystemButton.hpp"

SystemButton::SystemButton(IoPins& ioPins) 
: _ioPins(ioPins), _state(false)
{
}

SystemButton::~SystemButton() 
{
}

void SystemButton::SetState(bool state) 
{
    _state = state;
}

bool SystemButton::GetState() 
{
    return _state;
}
