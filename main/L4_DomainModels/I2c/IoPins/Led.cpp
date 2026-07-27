#include "Led.hpp"

Led::Led() 
{
}

Led::~Led() 
{
}

void Led::SetState(bool state) 
{
    _state = state;
}

bool Led::GetState() 
{
    return _state;
}
