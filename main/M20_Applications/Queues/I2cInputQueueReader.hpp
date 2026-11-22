#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class I2cInputQueue;
class ApplicationsManager;

class I2cInputQueueReader : public QueueProcessor
{
public:
    I2cInputQueueReader(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        I2cInputQueue& i2CinputQueue, 
        ApplicationsManager& applicationsManager);

    I2cInputQueueReader(
        const I2cInputQueueReader&) = delete;
    
    I2cInputQueueReader& operator=(
        const I2cInputQueueReader&) = delete;
    
    I2cInputQueueReader(
        I2cInputQueueReader&&) = delete;
    
    I2cInputQueueReader& operator=(
        I2cInputQueueReader&&) = delete;

    ~I2cInputQueueReader() override = default;
    
    bool HandleMessage();

private:
    I2cInputQueue& GetI2cInputQueue();
    
    ApplicationsManager& _applicationsManager;
};
