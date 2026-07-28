#pragma once

#include "../../L3_Messages/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class I2cInputQueue;
class IoPins;
class Joystick;
class SystemButton;

class I2cInputQueueWriter
{
public:
    I2cInputQueueWriter(I2cInputQueue& i2cInputQueue, IoPins& ioPins);
    ~I2cInputQueueWriter();

    void SendMessages();

private:
    I2cInputQueue& _i2cInputQueue;
    IoPins& _ioPins;

    void SendJoystickMessages(Joystick& joystick);
    void SendSystemButtonMessage(SystemButton& systemButton);
};
