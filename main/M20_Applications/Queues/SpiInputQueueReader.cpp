#include "SpiInputQueueReader.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
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

bool SpiInputQueueReader::HandleMessage() // NOSONAR // TODOSPI  : 16404 bytes of stack
{
    bool handled = false;

    if (SpiInputQueue::Message message{}; GetSpiInputQueue().GetRtosQueue().Receive(&message, 0))
    {
        //switch (message.type) // NOSONAR: S125 Remove commented out code
        //{
        //    case SpiInputQueue::Message::EType::JoystickDirection:
        //         _applicationsManager.OnJoystickDirectionChanged(
        //             message.joystickDirection.id, message.joystickDirection.direction);
        //         break;
        //    default:
        //        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown message type");
        //        break;
        //}
        //handled = true;
    }
    return handled;
}
