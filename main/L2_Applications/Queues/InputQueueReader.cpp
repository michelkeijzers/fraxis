#include "InputQueueReader.hpp"
#include "../../L3_Messages/InputQueue.hpp"
#include "../ApplicationsManager.hpp"

InputQueueReader::InputQueueReader(InputQueue& inputQueue, ApplicationsManager& applicationsManager)
: _inputQueue(inputQueue), _applicationsManager(applicationsManager) 
{
}

InputQueueReader::~InputQueueReader() 
{
}

bool InputQueueReader::HandleMessage() 
{
    bool handled = false;

    InputQueue::InputMessage inputMessage;
    if (_inputQueue.GetRtosQueue().Receive(&inputMessage, 0))
    {
        switch (inputMessage.type)
        {
            case InputQueue::InputMessage::EType::JoystickDirection:
                _applicationsManager.OnJoystickDirectionChanged(
                    inputMessage.joystickDirection.joystickId, inputMessage.joystickDirection.direction);
                break;

            case InputQueue::InputMessage::EType::JoystickButton:
                _applicationsManager.OnJoystickButtonChanged(
                    inputMessage.joystickButton.id, inputMessage.joystickButton.pressed);
                break;

            case InputQueue::InputMessage::EType::SystemButton:
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
