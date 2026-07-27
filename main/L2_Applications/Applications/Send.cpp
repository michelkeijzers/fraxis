#include "Send.hpp"
#include "../Queues/QueueWriters.hpp"
#include "../Queues/OutputQueueWriter.hpp"
#include "../Queues/LedStripsQueueWriter.hpp"
#include "../../L3_Messages/Types.hpp"

Send::Send(QueueWriters& queueWriters) 
: _queueWriters(queueWriters)
{
}

Send::~Send()
{
}

void Send::Led(Types::ELedId ledId, bool state)
{
    _queueWriters.GetOutputQueueWriter().SendLed(ledId, state);
}

void Send::Line(uint8_t lineNumber, std::string line)
{
    _queueWriters.GetOutputQueueWriter().SendLcd2004Line(lineNumber, line);
}