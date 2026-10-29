#include "LedStripsQueueWriter.hpp"
#include "../../M30_Messages/LedStrips/LedStripsQueue.hpp"
#include "../ApplicationsManager.hpp"

LedStripsQueueWriter::LedStripsQueueWriter(
    LedStripsQueue& ledStripsQueue, 
    ApplicationsManager& applicationsManager) 
:   
    _applicationsManager(applicationsManager)
{
    SetQueue(ledStripsQueue);
}

LedStripsQueue& LedStripsQueueWriter::GetLedStripsQueue()
{
    return static_cast<LedStripsQueue&>(GetQueue());
}

void LedStripsQueueWriter::SendLedStripsBrightness(
    uint8_t brightness)
{
    LedStripsQueue::Message message {};
    message.type = LedStripsQueue::Message::EType::Brightness;
    message.brightness.percentage = brightness;
    GetLedStripsQueue().GetRtosQueue().Send(&message, 0);
}

void LedStripsQueueWriter::SendPixel(
    uint8_t xPosition, 
    uint8_t yPosition, 
    uint8_t red, 
    uint8_t green, 
    uint8_t blue)
{
    LedStripsQueue::Message message {};
    message.type = LedStripsQueue::Message::EType::Pixel;
    message.pixel.xPosition = xPosition;
    message.pixel.yPosition = yPosition;
    message.pixel.red = red;
    message.pixel.green = green;
    message.pixel.blue = blue;
    GetLedStripsQueue().GetRtosQueue().Send(&message, 0);
}

void LedStripsQueueWriter::SendFrameReady()
{
    LedStripsQueue::Message message {};
    message.type = LedStripsQueue::Message::EType::FrameReady;
    GetLedStripsQueue().GetRtosQueue().Send(&message, 0);
}
