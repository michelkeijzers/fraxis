#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class LedStripsQueue;
class ApplicationsManager;

class LedStripsQueueWriter : public QueueProcessor
{
public:
    LedStripsQueueWriter(
        LedStripsQueue& i2cInputQueue, 
        ApplicationsManager& applicationsManager);

    LedStripsQueueWriter(const LedStripsQueueWriter&) = delete;
    LedStripsQueueWriter& operator=(const LedStripsQueueWriter&) = delete;
    LedStripsQueueWriter(LedStripsQueueWriter&&) = delete;
    LedStripsQueueWriter& operator=(LedStripsQueueWriter&&) = delete;

    ~LedStripsQueueWriter() override = default;
    
    void SendLedStripsBrightness(
        uint8_t brightness);
        
    void SendPixel(
        uint8_t xPosition, 
        uint8_t yPosition, 
        uint8_t red, 
        uint8_t green, 
        uint8_t blue);

    void SendFrameReady();

private:
    LedStripsQueue& GetLedStripsQueue();

    ApplicationsManager& _applicationsManager;
};
