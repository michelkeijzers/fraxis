#include "PassiveBuzzerOutputQueueReader.hpp"
#include "../../M30_Messages/PassiveBuzzer/PassiveBuzzerOutputQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

PassiveBuzzerOutputQueueReader::PassiveBuzzerOutputQueueReader(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities,
    PassiveBuzzerOutputQueue& passiveBuzzerOutputQueue,
    PassiveBuzzer& passiveBuzzer)
:
    QueueProcessor(assert, stringUtilities),
    _passiveBuzzer(passiveBuzzer)
{
    SetQueue(passiveBuzzerOutputQueue);
}

bool PassiveBuzzerOutputQueueReader::HandleMessage()
{
    PassiveBuzzerOutputQueue::Message message;
    if (!GetPassiveBuzzerOutputQueue().GetRtosQueue().Receive(&message, 0))
    {
        return false;
    }

    switch (message.type)
    {
        case PassiveBuzzerOutputQueue::Message::EType::Play:
        {
            _passiveBuzzer.Start();
            break;
        }
        case PassiveBuzzerOutputQueue::Message::EType::Stop:
        {
            _passiveBuzzer.Stop();
            break;
        }
        case PassiveBuzzerOutputQueue::Message::EType::SetFrequency:
        {
            _passiveBuzzer.SetFrequency(message.setFrequency.frequency);
            break;
        }
        default:
            break;
    }

    return true;
}

PassiveBuzzerOutputQueue& PassiveBuzzerOutputQueueReader::GetPassiveBuzzerOutputQueue()
{
    return static_cast<PassiveBuzzerOutputQueue&>(GetQueue());
}
