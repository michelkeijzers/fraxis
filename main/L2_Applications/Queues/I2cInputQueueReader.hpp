#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

class I2cInputQueue;
class ApplicationsManager;

class I2cInputQueueReader : public QueueProcessor
{
public:
    I2cInputQueueReader(
        I2cInputQueue& i2CinputQueue, 
        ApplicationsManager& applicationsManager);
    ~I2cInputQueueReader();
    
    bool HandleMessage();

private:
    I2cInputQueue& GetI2cInputQueue();
    
    ApplicationsManager& _applicationsManager;
};
