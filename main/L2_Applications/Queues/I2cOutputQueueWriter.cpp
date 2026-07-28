#include "I2cOutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"

I2cOutputQueueWriter::I2cOutputQueueWriter(I2cOutputQueue& i2cOutputQueue, ApplicationsManager& applicationsManager) 
: _i2cOutputQueue(i2cOutputQueue), _applicationsManager(applicationsManager)
{
}

I2cOutputQueueWriter::~I2cOutputQueueWriter()
{
}

void I2cOutputQueueWriter::SendLed(Types::ELedId ledId, bool state)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Led;
    message.ledId = ledId;
    message.state = state;
    _i2cOutputQueue.GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendLcd2004Line(uint8_t lineNumber, std::string line)
{
    I2cOutputQueue::OutputMessage message;
    message.type = I2cOutputQueue::OutputMessage::EType::Lcd2004Line;
    message.lcd2004Line.lineNumber = lineNumber;
    StringUtilities::CopyToBuffer(line, message.lcd2004Line.lineContent, Lcd2004::LINE_WIDTH);
    _i2cOutputQueue.GetRtosQueue().Send(&message, 0);
}
