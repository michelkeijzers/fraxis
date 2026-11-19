#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class LedStripsQueue;
class LedStrips;

class LedStripsQueueReader : public QueueProcessor
{
public:
    LedStripsQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        LedStripsQueue& ledStripsQueue,
        LedStrips& ledStrips);

    LedStripsQueueReader(
        const LedStripsQueueReader&) = delete;
    
    LedStripsQueueReader& operator=(
        const LedStripsQueueReader&) = delete;
    
    LedStripsQueueReader(
        LedStripsQueueReader&&) = delete;
    
    LedStripsQueueReader& operator=(
        LedStripsQueueReader&&) = delete;

    ~LedStripsQueueReader() override = default;
    
    bool HandleMessage();

private:
    LedStripsQueue& GetLedStripsQueue();
    
    LedStrips& _ledStrips;
};
