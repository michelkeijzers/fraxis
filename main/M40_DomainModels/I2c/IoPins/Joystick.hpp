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

    Joystick(const Joystick&) = delete;
    Joystick& operator=(const Joystick&) = delete;
    Joystick(Joystick&&) = delete;
    Joystick& operator=(Joystick&&) = delete;

    [[nodiscard]] Types::EJoystickId GetId() const; 

    void UpdateInputs();
    
    [[nodiscard]] Types::EJoystickDirection GetDirection() const;
    
    [[nodiscard]] bool GetButtonState() const;

    [[nodiscard]] Dirty& GetButtonStateDirty();

    [[nodiscard]] Dirty& GetDirectionDirty();

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
