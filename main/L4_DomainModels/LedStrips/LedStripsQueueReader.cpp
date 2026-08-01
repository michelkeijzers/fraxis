#include "LedStripsQueueReader.hpp"
#include "LedStrips.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

LedStripsQueueReader::LedStripsQueueReader(LedStripsQueue& ledStripsQueue, LedStrips& ledStrips)
: _ledStrips(ledStrips)
{
    SetQueue(ledStripsQueue);
}

LedStripsQueueReader::~LedStripsQueueReader() 
{
}

LedStripsQueue& LedStripsQueueReader::GetLedStripsQueue() 
{
    return static_cast<LedStripsQueue&>(GetQueue());
}

bool LedStripsQueueReader::HandleMessage() 
{
    bool handled = false;

    LedStripsQueue::LedStripsMessage ledStripsMessage;
    if (GetLedStripsQueue().GetRtosQueue().Receive(&ledStripsMessage, 0))
    {
        Position position;
        Color color;

        switch (ledStripsMessage.type)
        {
            case LedStripsQueue::LedStripsMessage::EType::Pixel:
                position.Set(ledStripsMessage.pixel.x, ledStripsMessage.pixel.y);
                color.Set(ledStripsMessage.pixel.red, ledStripsMessage.pixel.green, ledStripsMessage.pixel.blue);
                _ledStrips.SetPixel(position, color);
                break;

            default:
                Assert::Fail("Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
