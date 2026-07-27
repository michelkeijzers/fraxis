#pragma once

class I2cOutputQueue;
class IoPins;
class Displays;

class I2cOutputQueueReader
{
public:
    I2cOutputQueueReader(I2cOutputQueue& i2cOutputQueue, IoPins& ioPins, Displays& displays);
    ~I2cOutputQueueReader();
    
    bool HandleMessage();

private:
    I2cOutputQueue& _i2cOutputQueue;
    
    IoPins& _ioPins;
    Displays& _displays;
};
