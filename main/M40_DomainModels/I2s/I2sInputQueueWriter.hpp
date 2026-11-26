#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/I2s/I2sOutputQueue.hpp"
#include <cstdint>
#include <string>

class I2sInputQueue;
class I2sDac;
class I2sMicrophone;
class I2sMixer;

class I2sInputQueueWriter : public QueueProcessor
{
public:

    I2sInputQueueWriter(
        I2sInputQueue& i2sInputQueue,
        I2sDac& i2sDac,
        I2sMicrophone& i2sMicrophone,
        I2sMixer& i2sMixer,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    I2sInputQueueWriter(
        const I2sInputQueueWriter&) = delete;
    
    I2sInputQueueWriter& operator=(
        const I2sInputQueueWriter&) = delete;
    
    I2sInputQueueWriter(
        I2sInputQueueWriter&&) = delete;
    
    I2sInputQueueWriter& operator=(
        I2sInputQueueWriter&&) = delete;

    ~I2sInputQueueWriter() override = default;

    void SendMessages();

private:
    I2sInputQueue& GetI2sInputQueue();

    I2sDac& _i2sDac;

    I2sMicrophone& _i2sMicrophone;

    I2sMixer& _i2sMixer;
};
