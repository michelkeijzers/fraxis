#pragma once

#include <memory>

// Forward declarations of domain models
class I2cInputQueue;
class I2cOutputQueue;
class LedStripsQueue;

class QueuesContext
{
public:
    QueuesContext();
    ~QueuesContext();

    void Set(
        std::unique_ptr<I2cInputQueue> i2cInputQueue,
        std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
        std::unique_ptr<LedStripsQueue> ledStripsQueue
    );

    I2cInputQueue& GetI2cInputQueue();
    I2cOutputQueue& GetI2cOutputQueue();
    LedStripsQueue& GetLedStripsQueue();
    
private:
    std::unique_ptr<I2cInputQueue> _i2cInputQueue;
    std::unique_ptr<I2cOutputQueue> _i2cOutputQueue;
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
};
