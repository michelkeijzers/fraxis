#include "I2cInputQueueReader.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

I2cInputQueueReader::I2cInputQueueReader(
    I2cInputQueue& i2cInputQueue, 
    ApplicationsManager& applicationsManager)
: _applicationsManager(applicationsManager) 
{
    SetQueue(i2cInputQueue);
}

I2cInputQueue& I2cInputQueueReader::GetI2cInputQueue()
{
    return static_cast<I2cInputQueue&>(GetQueue());
}

bool I2cInputQueueReader::HandleMessage() 
{
    bool handled = false;

    if (I2cInputQueue::Message message{}; GetI2cInputQueue().GetRtosQueue().Receive(&message, 0))
    {
        switch (message.type)
        {
            case I2cInputQueue::Message::EType::JoystickDirection:
                _applicationsManager.OnJoystickDirectionChanged(
                    message.joystickDirection.id, message.joystickDirection.direction);
                break;

            case I2cInputQueue::Message::EType::JoystickButton:
                _applicationsManager.OnJoystickButtonChanged(
                    message.joystickButton.id, message.joystickButton.pressed);
                break;

            case I2cInputQueue::Message::EType::SystemButton:
                _applicationsManager.OnSystemButtonChanged(message.systemButton.pressed);
                break;

            default:
                Assert::Fail("Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
