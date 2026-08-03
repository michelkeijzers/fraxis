#include "Joystick.hpp"
#include "../IoPins/IoPins.hpp"
#include "../../../L0_System/DeviceSettings.hpp"
#include "../../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"

Joystick::Joystick(
    IoPins& ioPins, 
    Types::EJoystickId joystickId)
:   _ioPins(ioPins), 
    _id(joystickId),
    _buttonState(false),
    _direction(Types::EJoystickDirection::Centered)
{
}

Joystick::~Joystick()
{
}

Types::EJoystickId Joystick::GetId() const
{
    return _id;
}

/// @brief Updates button state and direction from device model. The method is called after an MCP23017 interrupt
/// by L6 DeviceDrivers layer, I2c Task delegate.
/// All inputs are reversed, because a button has default active low.
void Joystick::UpdateInputs()
{
    UpdateButtonState();
    UpdateDirection();
}

void Joystick::UpdateButtonState()
{
    bool isPlayer1 = (_id == Types::EJoystickId::Player1);
    uint8_t buttonBit = isPlayer1   ? DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON 
                                    : DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON;

    auto& mcp23017DeviceModel = _ioPins.GetDeviceModel();
    const bool newButtonState   = !(mcp23017DeviceModel.GetInputBit(buttonBit));
    if (newButtonState != _buttonState)
    {
        _buttonState = newButtonState;
        _buttonStateDirty.MarkDirty();
    }
}

void Joystick::UpdateDirection()
{
    bool isPlayer1 = (_id == Types::EJoystickId::Player1);
    uint8_t upBit    = isPlayer1    ? DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_UP
                                    : DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_UP;
    uint8_t rightBit = isPlayer1    ? DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT
                                    : DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT;
    uint8_t downBit  = isPlayer1    ? DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN
                                    : DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN;
    uint8_t leftBit  = isPlayer1    ? DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT
                                    : DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT;

    auto& mcp23017DeviceModel = _ioPins.GetDeviceModel();
    const bool up               = !(mcp23017DeviceModel.GetInputBit(upBit));
    const bool right            = !(mcp23017DeviceModel.GetInputBit(rightBit));
    const bool down             = !(mcp23017DeviceModel.GetInputBit(downBit));
    const bool left             = !(mcp23017DeviceModel.GetInputBit(leftBit));

    auto newDirection = Types::EJoystickDirection::Centered;
    if (up)
    {
        if (left)       newDirection = Types::EJoystickDirection::UpLeft;
        else if (right) newDirection = Types::EJoystickDirection::UpRight;
        else            newDirection = Types::EJoystickDirection::Up;
    }
    else if (down)
    {
        if (left)       newDirection = Types::EJoystickDirection::DownLeft;
        else if (right) newDirection = Types::EJoystickDirection::DownRight;
        else            newDirection = Types::EJoystickDirection::Down;
    }
    else
    {
        if (left)       newDirection = Types::EJoystickDirection::Left;
        else if (right) newDirection = Types::EJoystickDirection::Right;  
    }

    if (newDirection != _direction)
    {
        _direction = newDirection;
        _directionDirty.MarkDirty();
    }
}

Types::EJoystickDirection Joystick::GetDirection() const
{
    return _direction;
}

bool Joystick::GetButtonState() const
{
    return _buttonState;
}

Dirty Joystick::GetButtonStateDirty() 
{
    return _buttonStateDirty;
}

Dirty Joystick::GetDirectionDirty() 
{
    return _directionDirty;
}
