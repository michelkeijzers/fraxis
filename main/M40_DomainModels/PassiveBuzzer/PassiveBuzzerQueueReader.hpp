#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../PassiveBuzzer/PassiveBuzzer.hpp"

class PassiveBuzzerQueue;

class PassiveBuzzerQueueReader : public QueueProcessor
{
public:
    PassiveBuzzerQueueReader(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        PassiveBuzzerQueue& i2sOutputQueue,
        PassiveBuzzer& passiveBuzzer);

    PassiveBuzzerQueueReader(
        const PassiveBuzzerQueueReader&) = delete;
    
    PassiveBuzzerQueueReader& operator=(
        const PassiveBuzzerQueueReader&) = delete;
    
    PassiveBuzzerQueueReader(
        PassiveBuzzerQueueReader&&) = delete;
    
    PassiveBuzzerQueueReader& operator=(
        PassiveBuzzerQueueReader&&) = delete;

    ~PassiveBuzzerQueueReader() override = default;

    bool HandleMessage();

private:
    PassiveBuzzerQueue& GetPassiveBuzzerQueue();

    PassiveBuzzer& _passiveBuzzer;
};
