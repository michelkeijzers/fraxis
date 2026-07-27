#pragma once

#include "Joystick.hpp"
#include "Led.hpp"
#include "SystemButton.hpp"
#include "../../../L3_Messages/OutputQueue.hpp"
#include "../../../L3_Messages/Types.hpp"

class Joystick;
class Led;
class SystemButton;

class IoPins
{
public:
    IoPins();
    ~IoPins();

    Joystick& GetJoystick(Types::EJoystickId joystickId);
    Led& GetLed(Types::ELedId ledId);
    SystemButton& GetSystemButton();

private:
    Joystick _joysticks[2];
    Led _leds[5];
    SystemButton _systemButton;
};
