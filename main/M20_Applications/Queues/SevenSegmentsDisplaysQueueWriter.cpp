#include "SevenSegmentsDisplaysQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/SevenSegmentsDisplays/SevenSegmentsDisplaysQueue.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"

SevenSegmentsDisplaysQueueWriter::SevenSegmentsDisplaysQueueWriter(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities,
    SevenSegmentsDisplaysQueue& SevenSegmentsDisplaysQueue,
    ApplicationsManager& applicationsManager) 
:   
    QueueProcessor(assert, stringUtilities),
    _applicationsManager(applicationsManager)
{
    SetQueue(SevenSegmentsDisplaysQueue);
}

SevenSegmentsDisplaysQueue& 
    SevenSegmentsDisplaysQueueWriter::GetSevenSegmentsDisplaysQueue()
{
    return static_cast<SevenSegmentsDisplaysQueue&>(GetQueue());
}

void SevenSegmentsDisplaysQueueWriter::SendTm1637Enable(
    Types::ETm1637Id tm1637Id,
    bool on)
{
    SevenSegmentsDisplaysQueue::Message message = {};
    message.type = SevenSegmentsDisplaysQueue::Message::EType::Tm1637Enable;
    message.tm1637Enable.id = tm1637Id;
    message.tm1637Enable.on = on;
    GetSevenSegmentsDisplaysQueue().GetRtosQueue().Send(&message, 0);
}

void SevenSegmentsDisplaysQueueWriter::SendTm1637Brightness(
    Types::ETm1637Id tm1637Id, 
    uint8_t brightness)
{
    SevenSegmentsDisplaysQueue::Message message = {};
    message.type = SevenSegmentsDisplaysQueue::Message::EType::Tm1637Brightness;
    message.tm1637Brightness.id = tm1637Id;
    message.tm1637Brightness.brightness = brightness;
    GetSevenSegmentsDisplaysQueue().GetRtosQueue().Send(&message, 0);
}

void SevenSegmentsDisplaysQueueWriter::SendTm1637Value(
    Types::ETm1637Id tm1637Id, 
    uint32_t value)
{
    SevenSegmentsDisplaysQueue::Message message = {};
    message.type = SevenSegmentsDisplaysQueue::Message::EType::Tm1637Value;
    message.tm1637Value.id = tm1637Id;
    message.tm1637Value.value = value;
    GetSevenSegmentsDisplaysQueue().GetRtosQueue().Send(&message, 0);
}

void SevenSegmentsDisplaysQueueWriter::SendTm1637Time(
    Types::ETm1637Id tm1637Id, 
    uint8_t first, 
    uint8_t second)
{
    SevenSegmentsDisplaysQueue::Message message = {};
    message.type = SevenSegmentsDisplaysQueue::Message::EType::Tm1637Time;
    message.tm1637Time.id = tm1637Id;
    message.tm1637Time.first = first;
    message.tm1637Time.second = second;
    GetSevenSegmentsDisplaysQueue().GetRtosQueue().Send(&message, 0);
}
