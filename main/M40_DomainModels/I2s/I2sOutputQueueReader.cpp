#include "I2sOutputQueueReader.hpp"
#include "../../M30_Messages/I2s/I2sOutputQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

I2sOutputQueueReader::I2sOutputQueueReader(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities,
    I2sOutputQueue& i2sOutputQueue,
    I2sDac& i2sDac,
    PassiveBuzzer& passiveBuzzer)
:
    QueueProcessor(assert, stringUtilities),
    _i2sDac(i2sDac),
    _passiveBuzzer(passiveBuzzer)
{
    SetQueue(i2sOutputQueue);
}

bool I2sOutputQueueReader::HandleMessage()
{
    I2sOutputQueue::Message message;
    if (!GetI2sOutputQueue().GetRtosQueue().Receive(&message, 0))
    {
        return false;
    }

    switch (message.type)
    {
        case I2sOutputQueue::Message::EType::PlaySamples:
        {
            _i2sDac.WriteSamples(message.playSamples.buffer, message.playSamples.length);
            break;
        }

        case I2sOutputQueue::Message::EType::PlayWavFile:
        {
            break;
        }

        default:
            break;
    }

    return true;
}

I2sOutputQueue& I2sOutputQueueReader::GetI2sOutputQueue()
{
    return static_cast<I2sOutputQueue&>(GetQueue());
}
