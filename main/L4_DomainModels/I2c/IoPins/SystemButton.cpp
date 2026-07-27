#include "SystemButton.hpp"

SystemButton::SystemButton() 
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
