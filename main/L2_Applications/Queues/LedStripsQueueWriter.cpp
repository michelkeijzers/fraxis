#include "LedStripsQueueWriter.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../ApplicationsManager.hpp"

LedStripsQueueWriter::LedStripsQueueWriter(
    LedStripsQueue& ledStripsQueue, 
    ApplicationsManager& applicationsManager) 
:   _applicationsManager(applicationsManager)
{
    SetQueue(ledStripsQueue);
}

LedStripsQueueWriter::~LedStripsQueueWriter()
{
}

LedStripsQueue& LedStripsQueueWriter::GetLedStripsQueue()
{
    return static_cast<LedStripsQueue&>(GetQueue());
}

void LedStripsQueueWriter::SendPixel(
    uint8_t x, 
    uint8_t y, 
    uint8_t red, 
    uint8_t green, 
    uint8_t blue)
{
    LedStripsQueue::Message message;
    message.type = LedStripsQueue::Message::EType::Pixel;
    message.pixel.x = x;
    message.pixel.y = y;
    message.pixel.red = red;
    message.pixel.green = green;
    message.pixel.blue = blue;
    GetLedStripsQueue().GetRtosQueue().Send(&message, 0);
}

void LedStripsQueueWriter::SendFrameReady()
{
    LedStripsQueue::Message message;
    message.type = LedStripsQueue::Message::EType::FrameReady;
    GetLedStripsQueue().GetRtosQueue().Send(&message, 0);
}
