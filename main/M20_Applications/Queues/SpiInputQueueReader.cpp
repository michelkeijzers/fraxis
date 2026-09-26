#include "SpiInputQueueReader.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/SpiInputQueue.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

SpiInputQueueReader::SpiInputQueueReader(
    SpiInputQueue& spiInputQueue, 
    ApplicationsManager& applicationsManager)
: _applicationsManager(applicationsManager) 
{
    SetQueue(spiInputQueue);
}

SpiInputQueue& SpiInputQueueReader::GetSpiInputQueue()
{
    return static_cast<SpiInputQueue&>(GetQueue());
}

bool SpiInputQueueReader::HandleMessage() 
{
    bool handled = false;

    if (SpiInputQueue::Message message{}; GetSpiInputQueue().GetRtosQueue().Receive(&message, 0))
    {
        switch (message.type)
        {
            //TODOSPI
            // case SpiInputQueue::Message::EType::JoystickDirection:
            //     _applicationsManager.OnJoystickDirectionChanged(
            //         message.joystickDirection.id, message.joystickDirection.direction);
            //     break;

            default:
                Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
