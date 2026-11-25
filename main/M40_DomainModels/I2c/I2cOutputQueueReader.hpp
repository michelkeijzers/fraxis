#pragma once

#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

class I2cOutputQueue;
class Lcd2004;
class Tm1637;
class IoPins;

class I2cOutputQueueReader : public QueueProcessor
{
public:
    I2cOutputQueueReader(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        I2cOutputQueue& i2cOutputQueue,  
        Lcd2004& lcd2004, 
        IoPins& ioPins);

    I2cOutputQueueReader(
        const I2cOutputQueueReader&) = default;
    
    I2cOutputQueueReader& operator=(
        const I2cOutputQueueReader&) = default;
    
    I2cOutputQueueReader(
        I2cOutputQueueReader&&) = default;
    
    I2cOutputQueueReader& operator=(
        I2cOutputQueueReader&&) = default;

    ~I2cOutputQueueReader() override = default;
    
    bool HandleMessage();

private:
    I2cOutputQueue& GetI2cOutputQueue();
    
    Tm1637& GetTm1637ById(
        Types::ETm1637Id tm1637Id);


    Lcd2004& _lcd2004;

    IoPins& _ioPins;
};
