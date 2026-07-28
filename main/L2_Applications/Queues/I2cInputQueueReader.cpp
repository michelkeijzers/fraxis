#include "I2cInputQueueReader.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"
#include "../ApplicationsManager.hpp"

I2cInputQueueReader::I2cInputQueueReader(I2cInputQueue& i2cInputQueue, ApplicationsManager& applicationsManager)
: _i2cInputQueue(i2cInputQueue), _applicationsManager(applicationsManager) 
{
}

I2cInputQueueReader::~I2cInputQueueReader() 
{
}

bool I2cInputQueueReader::HandleMessage() 
{
    bool handled = false;

    I2cInputQueue::InputMessage inputMessage;
    if (_i2cInputQueue.GetRtosQueue().Receive(&inputMessage, 0))
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
                // TODO: unknown message type
                break;
        }
        handled = true;
    }
    return handled;
}
