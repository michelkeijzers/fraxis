#pragma once

class I2cInputQueue;
class ApplicationsManager;

class I2cInputQueueReader
{
public:
    I2cInputQueueReader(I2cInputQueue& i2CinputQueue, ApplicationsManager& applicationsManager);
    ~I2cInputQueueReader();
    
    bool HandleMessage();

private:
    I2cInputQueue& _i2cInputQueue;
    ApplicationsManager& _applicationsManager;
};
