#include "Send.hpp"
#include "../Queues/QueueWriters.hpp"
#include "../Queues/I2cOutputQueueWriter.hpp"
#include "../Queues/LedStripsQueueWriter.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Send::Send(QueueWriters& queueWriters) 
: _queueWriters(queueWriters)
{
}

Send::~Send()
{
}

void Send::Led(Types::ELedId ledId, bool state)
{
    _queueWriters.GetI2cOutputQueueWriter().SendLed(ledId, state);
}

void Send::Line(uint8_t lineNumber, std::string_view line)
{
    Assert::Equals(line.length(), Lcd2004::LINE_WIDTH);

    _queueWriters.GetI2cOutputQueueWriter().SendLcd2004Line(lineNumber, line);
}

void Send::Value(Types::ETm1637Id tm1637Id, uint32_t value)
{
    _queueWriters.GetI2cOutputQueueWriter().SendTm1637Value(tm1637Id, value);
}

void Send::Time(Types::ETm1637Id tm1637Id, uint8_t first, uint8_t second)
{
    _queueWriters.GetI2cOutputQueueWriter().SendTm1637Time(tm1637Id, first, second);
}
