#include "OutputQueueReader.hpp"
#include "../../L3_Messages/OutputQueue.hpp"
#include "Displays/Displays.hpp"
#include "Displays/Lcd2004/Lcd2004.hpp"


OutputQueueReader::OutputQueueReader(OutputQueue& outputQueue, IoPins& ioPins,Displays& displays)
: _outputQueue(outputQueue), _ioPins(ioPins), _displays(displays)
{
}

OutputQueueReader::~OutputQueueReader() 
{
}

bool OutputQueueReader::HandleMessage() 
{
    bool handled = false;

    OutputQueue::OutputMessage outputMessage;
    if (_outputQueue.GetRtosQueue().Receive(&outputMessage, 0))
    {
        switch (outputMessage.type)
        {
            case OutputQueue::OutputMessage::EType::Lcd2004Line:
                _displays.GetLcd2004().WriteLine(
                    outputMessage.lcd2004Line.lineNumber, outputMessage.lcd2004Line.lineContent);
                break;

            default:
                // TODO: unknown message type
                break;
        }
        handled = true;
    }
    return handled;
}
