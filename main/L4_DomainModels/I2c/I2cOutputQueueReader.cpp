#include "I2cOutputQueueReader.hpp"
#include "Displays/Displays.hpp"
#include "IoPins/IoPins.hpp"
#include "Displays/Lcd2004/Lcd2004.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"

I2cOutputQueueReader::I2cOutputQueueReader(I2cOutputQueue& i2cOutputQueue, IoPins& ioPins,Displays& displays)
: _i2cOutputQueue(i2cOutputQueue), _ioPins(ioPins), _displays(displays)
{
}

I2cOutputQueueReader::~I2cOutputQueueReader() 
{
}

bool I2cOutputQueueReader::HandleMessage() 
{
    bool handled = false;

    I2cOutputQueue::OutputMessage outputMessage;
    if (_i2cOutputQueue.GetRtosQueue().Receive(&outputMessage, 0))
    {
        switch (outputMessage.type)
        {
            case I2cOutputQueue::OutputMessage::EType::Led:
                _ioPins.GetLed(outputMessage.ledId).SetState(outputMessage.state);
                break;

            case I2cOutputQueue::OutputMessage::EType::Lcd2004Line:
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
