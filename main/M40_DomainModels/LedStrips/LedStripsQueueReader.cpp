#include "LedStripsQueueReader.hpp"
#include "LedStrips.hpp"
#include "../../M30_Messages/LedStrips/LedStripsQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
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

    if (LedStripsQueue::Message ledStripsMessage; 
        GetLedStripsQueue().GetRtosQueue().Receive(&ledStripsMessage, 0))
    {
        Position position;
        Color color;

        using enum LedStripsQueue::Message::EType;
        switch (ledStripsMessage.type)
        {
            case Brightness:
                _ledStrips.SetBrightness(ledStripsMessage.brightness.percentage);
                break;

            case Pixel:
                if (_ledStrips.GetOrientation() == Types::ELedStripsOrientation::Horizontal)
                {
                    M90::Assert::Assert::IsBetween(
                        Types::ETaskId::LedStripsTask, 
                        ledStripsMessage.pixel.xPosition,
                        0, 
                        LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP, 
                        "Hor x");
                    M90::Assert::Assert::IsBetween(
                        Types::ETaskId::LedStripsTask, 
                        ledStripsMessage.pixel.yPosition,
                        0, 
                        LedStrips::NUMBER_OF_LED_STRIPS, 
                        "Hor y");
                }
                else
                {
                    M90::Assert::Assert::IsBetween(
                        Types::ETaskId::LedStripsTask, 
                        ledStripsMessage.pixel.xPosition,
                        0, 
                        LedStrips::NUMBER_OF_LED_STRIPS, 
                        "Ver x");
                    M90::Assert::Assert::IsBetween(
                        Types::ETaskId::LedStripsTask, 
                        ledStripsMessage.pixel.yPosition,
                        0, 
                        LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP, 
                        "Ver y");

                }
                position.Set(ledStripsMessage.pixel.xPosition, ledStripsMessage.pixel.yPosition);
                color.Set(
                    ledStripsMessage.pixel.red, 
                    ledStripsMessage.pixel.green, 
                    ledStripsMessage.pixel.blue);
                _ledStrips.SetPixel(position, color);
                break;

            case FrameReady:
                _ledStrips.SetFrameReady();
                break;

            default:
                M90::Assert::Assert::Fail(Types::ETaskId::LedStripsTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
