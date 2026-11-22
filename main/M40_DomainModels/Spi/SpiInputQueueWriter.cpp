#include "SpiInputQueueWriter.hpp"
#include "MicroSdCard/MicroSdCard.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"   
#include "../../M90_Utilities/Log/Log.hpp" 

SpiInputQueueWriter::SpiInputQueueWriter(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    SpiInputQueue& spiInputQueue, 
    MicroSdCard& microSdCard)
:  
    QueueProcessor(assert, log, stringUtilities),
    _microSdCard(microSdCard),
    _log(log)
{
    SetQueue(spiInputQueue);
}

SpiInputQueue& SpiInputQueueWriter::GetSpiInputQueue()
{
    return static_cast<SpiInputQueue&>(GetQueue());
}

void SpiInputQueueWriter::SendWrite()
{
    /* NOSONAR TODO SPI
     if (joystick.GetButtonStateDirty().IsDirty())
     {
         I2cInputQueue::Message message;
         message.type = I2cInputQueue::Message::EType::JoystickButton;
         message.joystickButton.id = joystick.GetId();
         message.joystickButton.pressed = joystick.GetButtonState();
         GetI2cInputQueue().GetRtosQueue().Send(&message, 0);
         Log::Text(Types::ETaskId::I2cTask, "JS Button sent");
         joystick.GetButtonStateDirty().ClearDirty();
     }
     */

    if (_microSdCard.GetDirty().IsDirty())
    {
        // NOSONAR TODO SPI
        SpiInputQueue::Message message {};
        message.type = SpiInputQueue::Message::EType::MicroSdCardRead; // NOSONAR TODO
        GetSpiInputQueue().GetRtosQueue().Send(&message, 0);
        _log.Text(Types::ETaskId::SpiTask, "SPI messages sent");
        _microSdCard.GetDirty().ClearDirty();
    }
}

