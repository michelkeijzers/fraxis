#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "I2sDac/I2sDac.hpp"
#include "I2sMicrophone/I2sMicrophone.hpp"
#include "I2sMixer/I2sMixer.hpp"

class I2sOutputQueue;

class I2sOutputQueueReader : public QueueProcessor
{
public:
    I2sOutputQueueReader(
        I2sOutputQueue& i2sOutputQueue,
        I2sDac& dac,
        I2sMicrophone& microphone,
        I2sMixer& mixer,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

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
    
    I2sMicrophone& _i2sMicrophone;

    I2sMixer& _i2sMixer;
};
