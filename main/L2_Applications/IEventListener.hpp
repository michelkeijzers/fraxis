#pragma once

#include "IoStates/IoStates.hpp"
#include "IoStates/JoystickState.hpp"
#include "../L4_DomainModels/I2c/IoPins/Joystick.hpp"

class IEventListener
{
public:
    virtual void OnJoystickDirectionChanged(IoStates::EJoystickId id, Joystick::EDirection direction) = 0;
    virtual void OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) = 0;
    virtual void OnSystemButtonChanged(bool state) = 0;
};
