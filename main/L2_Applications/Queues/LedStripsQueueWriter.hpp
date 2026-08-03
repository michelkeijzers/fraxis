#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

class LedStripsQueue;
class ApplicationsManager;

class LedStripsQueueWriter : public QueueProcessor
{
public:
    LedStripsQueueWriter(
        LedStripsQueue& i2cInputQueue, 
        ApplicationsManager& applicationsManager);
    ~LedStripsQueueWriter();
    
    void SendPixel(
        uint8_t x, 
        uint8_t y, 
        uint8_t red, 
        uint8_t green, 
        uint8_t blue);
    void SendFrameReady();

private:
    LedStripsQueue& GetLedStripsQueue();

    ApplicationsManager& _applicationsManager;
};
