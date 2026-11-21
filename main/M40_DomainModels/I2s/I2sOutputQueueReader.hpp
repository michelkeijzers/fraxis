#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "I2sMicrophone/I2sMicrophone.hpp"
#include "I2sDac/I2sDac.hpp"
#include "PassiveBuzzer/PassiveBuzzer.hpp"

class I2sOutputQueue;

class I2sOutputQueueReader : public QueueProcessor
{
public:
    I2sOutputQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        I2sOutputQueue& i2sOutputQueue,
        I2sDac& dac,
        PassiveBuzzer& passiveBuzzer);

    I2sOutputQueueReader(
        const I2sOutputQueueReader&) = delete;
    
    I2sOutputQueueReader& operator=(
        const I2sOutputQueueReader&) = delete;
    
    I2sOutputQueueReader(
        I2sOutputQueueReader&&) = delete;
    
    I2sOutputQueueReader& operator=(
        I2sOutputQueueReader&&) = delete;

    ~I2sOutputQueueReader() override = default;

    bool HandleMessage();

private:
    I2sOutputQueue& GetI2sOutputQueue();

    I2sDac& _i2sDac;
    
    PassiveBuzzer& _passiveBuzzer;
};
