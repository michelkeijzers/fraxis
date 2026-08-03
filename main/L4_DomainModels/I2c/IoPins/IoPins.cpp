#include "IoPins.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"

#include <cstdint>

IoPins::IoPins()
:   _joysticks{ Joystick(*this, Types::EJoystickId::Player1), 
                Joystick(*this, Types::EJoystickId::Player2) },
    _leds{  Led(*this, Types::ELedId::Player1), 
            Led(*this, Types::ELedId::Player2),
            Led(*this, Types::ELedId::PlayPause), 
            Led(*this, Types::ELedId::Select), 
            Led(*this, Types::ELedId::Setup) },
_systemButton(*this),
_mcp23017DeviceModel(nullptr)
{
}

IoPins::~IoPins()
{
}

Joystick& IoPins::GetJoystick(
    Types::EJoystickId joystickId)
{
    return _joysticks[static_cast<uint8_t>(joystickId)];
}

Led& IoPins::GetLedById(
    Types::ELedId ledId)
{
    return _leds[static_cast<uint8_t>(ledId)];
}

SystemButton& IoPins::GetSystemButton()
{
    return _systemButton;
}

void IoPins::UpdateInputs()
{
    _systemButton.UpdateInput();
    _joysticks[0].UpdateInputs();
    _joysticks[1].UpdateInputs();
}

Mcp23017DeviceModel& IoPins::GetDeviceModel()
{
    return *_mcp23017DeviceModel;
}

void IoPins::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _mcp23017DeviceModel = static_cast<Mcp23017DeviceModel*>(&deviceModel);
}
