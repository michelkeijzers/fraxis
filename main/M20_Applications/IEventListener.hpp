#pragma once

#include "IoStates/IoStates.hpp"
#include "IoStates/JoystickState.hpp"
#include "../M30_Messages/Types.hpp"

class IEventListener
{
public:
    IEventListener() = default;

    IEventListener(const IEventListener&) = delete;
    IEventListener& operator=(const IEventListener&) = delete;
    IEventListener(IEventListener&&) = delete;
    IEventListener& operator=(IEventListener&&) = delete;

    virtual ~IEventListener() = default;

    virtual void OnJoystickDirectionChanged(
        Types::EJoystickId joystickId, 
        Types::EJoystickDirection direction) = 0;
    
    virtual void OnJoystickButtonChanged(
        Types::EJoystickId joystickId, 
        bool state) = 0;
    
        virtual void OnSystemButtonChanged(
        bool state) = 0;

    virtual void OnSdCardRead();
};
