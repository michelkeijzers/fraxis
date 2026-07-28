#include "Joystick.hpp"

Joystick::Joystick(IoPins& ioPins, Types::EJoystickId joystickId)
: _ioPins(ioPins), _id(joystickId), _direction(Types::EJoystickDirection::Centered), _buttonState(false)
{
}

Joystick::~Joystick()
{
}

Types::EJoystickDirection Joystick::GetDirection()
{
    return _direction;
}

bool Joystick::GetButtonState()
{
    return _buttonState;
}
