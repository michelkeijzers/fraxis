#pragma once

#include "Joystick.hpp"
#include "Led.hpp"
#include "SystemButton.hpp"
#include "../../DomainModel.hpp"
#include "../../../M00_System/DeviceSettings.hpp"
#include "../../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <memory>
#include <array>

class Joystick;
class SystemButton;

namespace M50::I2c
{
    class IMcp23017DeviceModel;
}

class IoPins : public DomainModel
{
public:
    IoPins(
        M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel,
        M50::IDeviceModel& deviceModel,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    IoPins(
        const IoPins &) = delete;

    IoPins &operator=(const IoPins &) = delete;

    IoPins(
        IoPins &&) = delete;

    IoPins &operator=(IoPins &&) = delete;

    Joystick& GetJoystick(
        Types::EJoystickId joystickId);
    
    Led& GetLedById(
        Types::ELedId ledId);
    
    SystemButton& GetSystemButton();

    void UpdateInputs();

    M50::I2c::IMcp23017DeviceModel& GetMcp23017DeviceModel();

private:
    std::array<Joystick, DeviceSettings::MCP23017_NUMBER_OF_JOYSTICKS> _joysticks;
    
    std::array<std::unique_ptr<Led>, DeviceSettings::MCP23017_NUMBER_OF_LEDS> _leds;
    
    SystemButton _systemButton;
        
    M50::I2c::IMcp23017DeviceModel& _mcp23017DeviceModel;
};
