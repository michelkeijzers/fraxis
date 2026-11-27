#include "IoPins.hpp"
#include "../../../M30_Messages/Types.hpp"
#include "../../../M50_DeviceModels/I2c/Mcp23017/Mcp23017DeviceModel.hpp"
#include <cstdint>
#include <memory>

IoPins::IoPins(
    M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel,
    M50::IDeviceModel& deviceModel,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:   
    DomainModel(deviceModel, assert, log),
    _joysticks{ Joystick(*this, Types::EJoystickId::Player1), 
                Joystick(*this, Types::EJoystickId::Player2) },
    _leds{  std::make_unique<Led>(assert, *this, Types::ELedId::Player1), 
            std::make_unique<Led>(assert, *this, Types::ELedId::Player2),
            std::make_unique<Led>(assert, *this, Types::ELedId::PlayPause), 
            std::make_unique<Led>(assert, *this, Types::ELedId::Select), 
            std::make_unique<Led>(assert, *this, Types::ELedId::Setup) },
    _systemButton(*this),
    _mcp23017DeviceModel(mcp23017DeviceModel)
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
    return *_leds[static_cast<uint8_t>(ledId)];
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

M50::I2c::Mcp23017DeviceModel& IoPins::GetDeviceModel()
{
    return *_mcp23017DeviceModel;
}

void IoPins::SetDeviceModel(
    M50::IDeviceModel& deviceModel)
{
    _mcp23017DeviceModel = static_cast<M50::I2c::Mcp23017DeviceModel*>(&deviceModel);
}
