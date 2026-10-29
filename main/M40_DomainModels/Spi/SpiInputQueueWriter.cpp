#include "SpiInputQueueWriter.hpp"
#include "MicroSdCard/MicroSdCard.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"   
#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"
#include "../../M90_Utilities/Log/Log.hpp" 

SpiInputQueueWriter::SpiInputQueueWriter(
    SpiInputQueue& spiInputQueue, 
    MicroSdCard& microSdCard)
:  
    _microSdCard(microSdCard)
{
    SetQueue(spiInputQueue);
}

SpiInputQueue& SpiInputQueueWriter::GetSpiInputQueue()
{
    return static_cast<SpiInputQueue&>(GetQueue());
}

void SpiInputQueueWriter::SendWrite()
{
    // NOSONAR TODO SPI
    //     if (joystick.GetButtonStateDirty().IsDirty())
    //     {
    //         I2cInputQueue::Message message;
    //         message.type = I2cInputQueue::Message::EType::JoystickButton;
    //         message.joystickButton.id = joystick.GetId();
    //         message.joystickButton.pressed = joystick.GetButtonState();
    //         GetI2cInputQueue().GetRtosQueue().Send(&message, 0);
    //         Log::Text(Types::ETaskId::I2cTask, "JS Button sent");
    //         joystick.GetButtonStateDirty().ClearDirty();
    //     }

    if (_microSdCard.GetDirty().IsDirty())
    {
        // NOSONAR TODO SPI
        //SpiInputQueue::Message message;
        //message.type = SpiInputQueue::Message::EType::MicroSdCardRead; // NOSONAR TODO SPI
        //GetSpiInputQueue().GetRtosQueue().Send(&message, 0);
        //Log::Text(Types::ETaskId::SpiTask, "SPI messages sent");
        //_microSdCard.GetDirty().ClearDirty();
    }
}

