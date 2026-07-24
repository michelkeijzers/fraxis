#pragma once

#include "IoStates/IoStates.hpp"
#include "IoStates/JoystickState.hpp"

class IEventListener
{
public:
    virtual void OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction) = 0;
    virtual void OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) = 0;
    virtual void OnSystemButtonChanged(bool state) = 0;
};
