#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

class LedStripsQueue;
class LedStrips;

class LedStripsQueueReader : public QueueProcessor
{
public:
    LedStripsQueueReader(
        LedStripsQueue& ledStripsQueue,
        LedStrips& ledStrips);
    ~LedStripsQueueReader() = default;
    
    bool HandleMessage();

private:
    LedStripsQueue& GetLedStripsQueue();
    
    LedStrips& _ledStrips;
};
