#include "OutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L3_Messages/OutputQueue.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utils/String/StringUtils.hpp"

OutputQueueWriter::OutputQueueWriter(OutputQueue& outputQueue, ApplicationsManager& applicationsManager) 
: _outputQueue(outputQueue), _applicationsManager(applicationsManager)
{
}

OutputQueueWriter::~OutputQueueWriter()
{
}

void OutputQueueWriter::SendLcd2004Line(uint8_t lineNumber, std::string line)
{
    OutputQueue::OutputMessage message;
    message.type = OutputQueue::OutputMessage::EType::Lcd2004Line;
    message.lcd2004Line.lineNumber = lineNumber;
    StringUtils::CopyToBuffer(line, message.lcd2004Line.lineContent, Lcd2004::LINE_WIDTH);
    _outputQueue.GetRtosQueue().Send(&message, 0);
}
