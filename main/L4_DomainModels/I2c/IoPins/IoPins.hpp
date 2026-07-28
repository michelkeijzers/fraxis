#pragma once

#include "Joystick.hpp"
#include "Led.hpp"
#include "SystemButton.hpp"
#include "../../DomainModel.hpp"
#include "../../../L3_Messages/I2cOutputQueue.hpp"
#include "../../../L3_Messages/Types.hpp"

class Joystick;
class Led;
class SystemButton;
class Mcp23017DeviceModel;

class Mcp23017DeviceModel;

class IoPins : public IDomainModel
{
public:
    IoPins();
    ~IoPins();

    Joystick& GetJoystick(Types::EJoystickId joystickId);
    Led& GetLed(Types::ELedId ledId);
    SystemButton& GetSystemButton();

    void UpdateInputs();

    Mcp23017DeviceModel& GetDeviceModel();
    void SetDeviceModel(IDeviceModel& deviceModel) override;

private:
    Joystick _joysticks[2];
    Led _leds[5];
    SystemButton _systemButton;
        
    Mcp23017DeviceModel* _mcp23017DeviceModel;
};
