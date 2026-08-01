#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

class I2cOutputQueue;
class IoPins;
class Displays;

class I2cOutputQueueReader : public QueueProcessor
{
public:
    I2cOutputQueueReader(I2cOutputQueue& i2cOutputQueue, IoPins& ioPins, Displays& displays);
    ~I2cOutputQueueReader();
    
    bool HandleMessage();

private:
    I2cOutputQueue& GetI2cOutputQueue();
    
    IoPins& _ioPins;
    Displays& _displays;
};
