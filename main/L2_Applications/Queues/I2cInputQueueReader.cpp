#include "I2cInputQueueReader.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

I2cInputQueueReader::I2cInputQueueReader(I2cInputQueue& i2cInputQueue, ApplicationsManager& applicationsManager)
: _applicationsManager(applicationsManager) 
{
    SetQueue(i2cInputQueue);
}

I2cInputQueueReader::~I2cInputQueueReader() 
{
}

I2cInputQueue& I2cInputQueueReader::GetI2cInputQueue()
{
    return static_cast<I2cInputQueue&>(GetQueue());
}

bool I2cInputQueueReader::HandleMessage() 
{
    bool handled = false;

    I2cInputQueue::InputMessage inputMessage;
    if (GetI2cInputQueue().GetRtosQueue().Receive(&inputMessage, 0))
    {
        switch (inputMessage.type)
        {
            case I2cInputQueue::InputMessage::EType::JoystickDirection:
                _applicationsManager.OnJoystickDirectionChanged(
                    inputMessage.joystickDirection.id, inputMessage.joystickDirection.direction);
                break;

            case I2cInputQueue::InputMessage::EType::JoystickButton:
                _applicationsManager.OnJoystickButtonChanged(
                    inputMessage.joystickButton.id, inputMessage.joystickButton.pressed);
                break;

            case I2cInputQueue::InputMessage::EType::SystemButton:
                _applicationsManager.OnSystemButtonChanged(inputMessage.systemButton.pressed);
                break;

            default:
                Assert::Fail("Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
