#pragma once

#include "IoStates/IoStates.hpp"
#include "IoStates/JoystickState.hpp"
#include "../L3_Messages/Types.hpp"

class IEventListener
{
public:
    virtual void OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction) = 0;
    virtual void OnJoystickButtonChanged(Types::EJoystickId id, bool state) = 0;
    virtual void OnSystemButtonChanged(bool state) = 0;
};
