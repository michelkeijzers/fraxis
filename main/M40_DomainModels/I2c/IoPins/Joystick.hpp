#pragma once

#include "../../../M30_Messages/Types.hpp"
#include "../../../M90_Utilities/Dirty/Dirty.hpp"

class IoPins;

class Joystick
{
public:
    Joystick(
        IoPins& ioPins, 
        Types::EJoystickId joystickId);
    ~Joystick();

    Types::EJoystickId GetId() const; 

    void UpdateInputs();
    Types::EJoystickDirection GetDirection() const;
    bool GetButtonState() const;

    Dirty& GetButtonStateDirty();
    Dirty& GetDirectionDirty();

private:
    IoPins& _ioPins;
    Types::EJoystickId _id;
    bool _buttonState;
    Dirty _buttonStateDirty;
    Types::EJoystickDirection _direction;
    Dirty _directionDirty;

    void UpdateButtonState();
    void UpdateDirection();
};
