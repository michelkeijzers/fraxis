#include "SpiOutputQueueReader.hpp"
#include "MicroSdCard/MicroSdCard.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M30_Messages/Spi/SpiOutputQueue.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

SpiOutputQueueReader::SpiOutputQueueReader(
    SpiOutputQueue& spiOutputQueue, 
    MicroSdCard& microSdCard)
:  
    _microSdCard(microSdCard)
{
    SetQueue(spiOutputQueue);
}

SpiOutputQueue& SpiOutputQueueReader::GetSpiOutputQueue()
{
    return static_cast<SpiOutputQueue&>(GetQueue());
}

bool SpiOutputQueueReader::HandleMessage() 
{
    bool handled = false;

    SpiOutputQueue::Message message = {};
    auto& queue = GetSpiOutputQueue();
    if (auto& rtosQueue = queue.GetRtosQueue(); rtosQueue.Receive(&message, 0))
    {
        switch (message.type) // NOSONAR S1301: only one case (yet)
        {
        case SpiOutputQueue::Message::EType::MicroSdCardWrite:
            //_microSdCard.Write(); // NOSONAR TODO SPI
            break;

        default:
            Assert::Fail(Types::ETaskId::SpiTask, "Unknown message type");
            break;
        }
        handled = true;
    }
    return handled;
}
