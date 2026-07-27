#pragma once

#include <memory>

// Forward declarations of domain models
class LedStripsQueue;
class I2cInputQueue;
class I2cOutputQueue;

class QueuesContext
{
public:
    QueuesContext();
    ~QueuesContext();

    void Set(
        std::unique_ptr<LedStripsQueue> ledStripsQueue,
        std::unique_ptr<I2cInputQueue> i2cInputQueue,
        std::unique_ptr<I2cOutputQueue> i2cOutputQueue);

    LedStripsQueue& GetLedStripsQueue();
    I2cInputQueue& GetI2cInputQueue();
    I2cOutputQueue& GetI2cOutputQueue();
    
private:
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
    std::unique_ptr<I2cInputQueue> _i2cInputQueue;
    std::unique_ptr<I2cOutputQueue> _i2cOutputQueue;
};
