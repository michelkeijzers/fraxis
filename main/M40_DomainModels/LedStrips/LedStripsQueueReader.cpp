#include "LedStripsQueueReader.hpp"
#include "LedStrips.hpp"
#include "../../M30_Messages/LedStripsQueue.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

LedStripsQueueReader::LedStripsQueueReader(
    LedStripsQueue& ledStripsQueue, 
    LedStrips& ledStrips)
: _ledStrips(ledStrips)
{
    SetQueue(ledStripsQueue);
}

LedStripsQueue& LedStripsQueueReader::GetLedStripsQueue() 
{
    return static_cast<LedStripsQueue&>(GetQueue());
}

bool LedStripsQueueReader::HandleMessage() 
{
    bool handled = false;

    LedStripsQueue::Message ledStripsMessage;
    if (GetLedStripsQueue().GetRtosQueue().Receive(&ledStripsMessage, 0))
    {
        Position position;
        Color color;

        switch (ledStripsMessage.type)
        {
            case LedStripsQueue::Message::EType::Pixel:
                if (_ledStrips.GetOrientation() == Types::ELedStripsOrientation::Horizontal)
                {
                    Assert::IsBetween(Types::ETaskId::LedStripsTask, ledStripsMessage.pixel.x,
                        0, LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP, "Hor x");
                    Assert::IsBetween(Types::ETaskId::LedStripsTask, ledStripsMessage.pixel.y,
                        0, LedStrips::NUMBER_OF_LED_STRIPS, "Hor y");
                }
                else
                {
                    Assert::IsBetween(Types::ETaskId::LedStripsTask, ledStripsMessage.pixel.x,
                        0, LedStrips::NUMBER_OF_LED_STRIPS, "Ver x");
                    Assert::IsBetween(Types::ETaskId::LedStripsTask, ledStripsMessage.pixel.y,
                        0, LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP, "Ver y");

                }
                position.Set(ledStripsMessage.pixel.x, ledStripsMessage.pixel.y);
                color.Set(
                    ledStripsMessage.pixel.red, 
                    ledStripsMessage.pixel.green, 
                    ledStripsMessage.pixel.blue);
                _ledStrips.SetPixel(position, color);
                break;

            case LedStripsQueue::Message::EType::FrameReady:
                _ledStrips.SetFrameReady();
                break;

            default:
                Assert::Fail(Types::ETaskId::LedStripsTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
