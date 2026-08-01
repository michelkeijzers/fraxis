#include "I2cOutputQueueReader.hpp"
#include "Displays/Displays.hpp"
#include "IoPins/IoPins.hpp"
#include "Displays/Lcd2004/Lcd2004.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

I2cOutputQueueReader::I2cOutputQueueReader(I2cOutputQueue& i2cOutputQueue, IoPins& ioPins, Displays& displays)
:  _ioPins(ioPins), _displays(displays)
{
    SetQueue(i2cOutputQueue);
}

I2cOutputQueueReader::~I2cOutputQueueReader() 
{
}

I2cOutputQueue& I2cOutputQueueReader::GetI2cOutputQueue()
{
    return static_cast<I2cOutputQueue&>(GetQueue());
}

bool I2cOutputQueueReader::HandleMessage() 
{
    bool handled = false;

    I2cOutputQueue::OutputMessage outputMessage = {};
    auto& queue = GetI2cOutputQueue();
    RtosQueue& rtosQueue = queue.GetRtosQueue();
    if (rtosQueue.Receive(&outputMessage, 0))
    {
        switch (outputMessage.type)
        {
            case I2cOutputQueue::OutputMessage::EType::Led:
                _ioPins.GetLed(outputMessage.ledId).SetState(outputMessage.state);
                break;

            case I2cOutputQueue::OutputMessage::EType::Lcd2004Line:
                _displays.GetLcd2004().SetLine(
                    outputMessage.lcd2004Line.lineNumber, outputMessage.lcd2004Line.lineContent);
                break;

            default:
                Assert::Fail("Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
