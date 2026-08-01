#include "I2cOutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"

I2cOutputQueueWriter::I2cOutputQueueWriter(I2cOutputQueue& i2cOutputQueue, ApplicationsManager& applicationsManager) 
: _applicationsManager(applicationsManager)
{
    SetQueue(i2cOutputQueue);
}

I2cOutputQueueWriter::~I2cOutputQueueWriter()
{
}

I2cOutputQueue& I2cOutputQueueWriter::GetI2cOutputQueue() 
{
    return static_cast<I2cOutputQueue&>(GetQueue()); 
}

void I2cOutputQueueWriter::SendLed(Types::ELedId ledId, bool state)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Led;
    message.ledId = ledId;
    message.state = state;
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendLcd2004Line(uint8_t lineNumber, std::string_view line)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Lcd2004Line;
    message.lcd2004Line.lineNumber = lineNumber;
    StringUtilities::CopyToBuffer(line, message.lcd2004Line.lineContent, Lcd2004::LINE_WIDTH);
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendTm1637Value(Types::ETm1637Id tm1637Id, uint32_t value)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Tm1637Value;
    message.tm1637Value.tm1637Id = tm1637Id;
    message.tm1637Value.value = value;
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}


void I2cOutputQueueWriter::SendTm1637Time(Types::ETm1637Id tm1637Id, uint8_t first, uint8_t second)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Tm1637Time;
    message.tm1637Time.tm1637Id = tm1637Id;
    message.tm1637Time.first = first;
    message.tm1637Time.second = second;
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}
