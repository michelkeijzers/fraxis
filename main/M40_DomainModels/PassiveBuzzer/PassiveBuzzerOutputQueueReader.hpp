#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../PassiveBuzzer/PassiveBuzzer.hpp"

class PassiveBuzzerOutputQueue;

class PassiveBuzzerOutputQueueReader : public QueueProcessor
{
public:
    PassiveBuzzerOutputQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        PassiveBuzzerOutputQueue& i2sOutputQueue,
        PassiveBuzzer& passiveBuzzer);

    PassiveBuzzerOutputQueueReader(
        const PassiveBuzzerOutputQueueReader&) = delete;
    
    PassiveBuzzerOutputQueueReader& operator=(
        const PassiveBuzzerOutputQueueReader&) = delete;
    
    PassiveBuzzerOutputQueueReader(
        PassiveBuzzerOutputQueueReader&&) = delete;
    
    PassiveBuzzerOutputQueueReader& operator=(
        PassiveBuzzerOutputQueueReader&&) = delete;

    ~PassiveBuzzerOutputQueueReader() override = default;

    bool HandleMessage();

private:
    PassiveBuzzerOutputQueue& GetPassiveBuzzerOutputQueue();

    PassiveBuzzer& _passiveBuzzer;
};
