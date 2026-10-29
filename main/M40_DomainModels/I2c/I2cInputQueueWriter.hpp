#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class I2cInputQueue;
class IoPins;
class Joystick;
class SystemButton;

class I2cInputQueueWriter : public QueueProcessor
{
public:

    I2cInputQueueWriter(
        I2cInputQueue& i2cInputQueue, 
        IoPins& ioPins);

    I2cInputQueueWriter(const I2cInputQueueWriter&) = delete;
    I2cInputQueueWriter& operator=(const I2cInputQueueWriter&) = delete;
    I2cInputQueueWriter(I2cInputQueueWriter&&) = delete;
    I2cInputQueueWriter& operator=(I2cInputQueueWriter&&) = delete;

    ~I2cInputQueueWriter() override = default;

    void SendMessages();

private:
    I2cInputQueue& GetI2cInputQueue();

    void SendJoystickMessages(
        Joystick& joystick);
    void SendSystemButtonMessage(
        SystemButton& systemButton);

    IoPins& _ioPins;
};
