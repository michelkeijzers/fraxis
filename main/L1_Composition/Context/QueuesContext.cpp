#include "../../L8_Services/RtosTask/RtosTask.hpp"

#include "QueuesContext.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"

QueuesContext::QueuesContext()
{
}

QueuesContext::~QueuesContext()
{
}

void QueuesContext::Set(
    std::unique_ptr<I2cInputQueue> i2cInputQueue,
    std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
    std::unique_ptr<LedStripsQueue> ledStripsQueue
)
{
    _i2cInputQueue = std::move(i2cInputQueue);
    _i2cOutputQueue = std::move(i2cOutputQueue);
    _ledStripsQueue = std::move(ledStripsQueue);
}

I2cInputQueue& QueuesContext::GetI2cInputQueue()
{
    return *_i2cInputQueue; 
}

I2cOutputQueue& QueuesContext::GetI2cOutputQueue()
{
    return *_i2cOutputQueue; 
}

LedStripsQueue& QueuesContext::GetLedStripsQueue() 
{
    return *_ledStripsQueue; 
}
