#include "SpiOutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/SpiOutputQueue.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"

SpiOutputQueueWriter::SpiOutputQueueWriter(
    SpiOutputQueue& spiOutputQueue, 
    ApplicationsManager& applicationsManager) 
:   _applicationsManager(applicationsManager)
{
    SetQueue(spiOutputQueue);
}

SpiOutputQueue& SpiOutputQueueWriter::GetSpiOutputQueue() 
{
    return static_cast<SpiOutputQueue&>(GetQueue()); 
}

//TODOSPI
// void I2cOutputQueueWriter::SendLed(
//     Types::ELedId ledId, 
//     bool state)
// {
//     I2cOutputQueue::Message message;
//     message.type = I2cOutputQueue::Message::EType::Led;
//     message.led.id = ledId;
//     message.led.state = state;
//     GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
// }
