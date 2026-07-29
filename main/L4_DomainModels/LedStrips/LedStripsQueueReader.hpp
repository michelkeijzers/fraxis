#pragma once

class LedStripsQueue;
class LedStrips;

class LedStripsQueueReader
{
public:
    LedStripsQueueReader(LedStripsQueue& ledStripsQueue, LedStrips& ledStrips);
    ~LedStripsQueueReader();
    
    bool HandleMessage();

private:
    LedStripsQueue& _ledStripsQueue;
    
    LedStrips& _ledStrips;
};
