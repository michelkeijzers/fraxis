#pragma once

#include "Joystick.hpp"
#include "Led.hpp"
#include "SystemButton.hpp"
#include "../../DomainModel.hpp"
#include "../../../M00_System/DeviceSettings.hpp"
#include "../../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../../M30_Messages/Types.hpp"

class Joystick;
class Led;
class SystemButton;
class Mcp23017DeviceModel;
class Mcp23017DeviceModel;

class IoPins : public IDomainModel
{
public:
    IoPins();

    IoPins(const IoPins&) = delete;
    IoPins& operator=(const IoPins&) = delete;
    IoPins(IoPins&&) = delete;
    IoPins& operator=(IoPins&&) = delete;

    ~IoPins() override = default;

    Joystick& GetJoystick(
        Types::EJoystickId joystickId);
    Led& GetLedById(
        Types::ELedId ledId);
    SystemButton& GetSystemButton();

    void UpdateInputs();

    Mcp23017DeviceModel& GetDeviceModel();
    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

private:
    std::array<Joystick, DeviceSettings::MCP23017_NR_OF_JOYSTICKS> _joysticks;
    std::array<Led, DeviceSettings::MCP23017_NR_OF_LEDS> _leds;
    SystemButton _systemButton;
        
    Mcp23017DeviceModel* _mcp23017DeviceModel;
};
