#include "QueuesContext.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M30_Messages/I2cInputQueue.hpp"
#include "../../M30_Messages/I2cOutputQueue.hpp"
#include "../../M30_Messages/LedStripsQueue.hpp"
#include "../../M30_Messages/DiagnosticsQueue.hpp"
#include "../../M30_Messages/NvsQueue.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

QueuesContext::QueuesContext()
: 
_i2cInputQueue(nullptr), 
    _i2cOutputQueue(nullptr), 
    _ledStripsQueue(nullptr),
    _diagnosticsQueue(nullptr),
    _nvsQueue(nullptr)
{
}

QueuesContext::~QueuesContext()
{
}

void QueuesContext::Set(
    std::unique_ptr<I2cInputQueue> i2cInputQueue,
    std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
    std::unique_ptr<LedStripsQueue> ledStripsQueue,
    std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
    std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter,
    std::unique_ptr<NvsQueue> nvsQueue)
{
    _i2cInputQueue = std::move(i2cInputQueue);
    _i2cOutputQueue = std::move(i2cOutputQueue);
    _ledStripsQueue = std::move(ledStripsQueue);
    _diagnosticsQueue = std::move(diagnosticsQueue);
    _diagnosticsQueueWriter = std::move(diagnosticsQueueWriter);
    _nvsQueue = std::move(nvsQueue);
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

DiagnosticsQueue& QueuesContext::GetDiagnosticsQueue() 
{
    return *_diagnosticsQueue; 
}

DiagnosticsQueueWriter& QueuesContext::GetDiagnosticsQueueWriter() 
{
    return *_diagnosticsQueueWriter; 
}

NvsQueue& QueuesContext::GetNvsQueue() 
{
    return *_nvsQueue;
}
