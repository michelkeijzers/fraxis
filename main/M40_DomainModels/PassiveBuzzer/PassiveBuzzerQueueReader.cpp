#include "PassiveBuzzerQueueReader.hpp"
#include "../../M30_Messages/PassiveBuzzer/PassiveBuzzerQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

PassiveBuzzerQueueReader::PassiveBuzzerQueueReader(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    PassiveBuzzerQueue& passiveBuzzerQueue,
    PassiveBuzzer& passiveBuzzer)
:
    QueueProcessor(assert, log, stringUtilities),
    _passiveBuzzer(passiveBuzzer)
{
    SetQueue(passiveBuzzerQueue);
}

bool PassiveBuzzerQueueReader::HandleMessage()
{
    PassiveBuzzerQueue::Message message;
    if (!GetPassiveBuzzerQueue().GetRtosQueue().Receive(&message, 0))
    {
        return false;
    }

    switch (message.type)
    {
        case PassiveBuzzerQueue::Message::EType::Play:
        {
            _passiveBuzzer.Start();
            break;
        }
        case PassiveBuzzerQueue::Message::EType::Stop:
        {
            _passiveBuzzer.Stop();
            break;
        }
        case PassiveBuzzerQueue::Message::EType::SetFrequency:
        {
            _passiveBuzzer.SetFrequency(message.setFrequency.frequency);
            break;
        }
        default:
            break;
    }

    return true;
}

PassiveBuzzerQueue& PassiveBuzzerQueueReader::GetPassiveBuzzerQueue()
{
    return static_cast<PassiveBuzzerQueue&>(GetQueue());
}
