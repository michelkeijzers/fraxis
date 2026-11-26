#include "QueuesContext.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M30_Messages/I2c/I2cInputQueue.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../M30_Messages/I2s/I2sInputQueue.hpp"
#include "../../M30_Messages/I2s/I2sOutputQueue.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
#include "../../M30_Messages/Spi/SpiOutputQueue.hpp"
#include "../../M30_Messages/LedStrips/LedStripsQueue.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include "../../M30_Messages/PassiveBuzzer/PassiveBuzzerQueue.hpp"
#include "../../M30_Messages/SevenSegmentsDisplays/SevenSegmentsDisplaysQueue.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

QueuesContext::QueuesContext()
:
    _diagnosticsQueue(nullptr),
    _diagnosticsQueueWriter(nullptr),
    _i2cInputQueue(nullptr),
    _i2cOutputQueue(nullptr),
    _i2sInputQueue(nullptr),
    _i2sOutputQueue(nullptr),
    _ledStripsQueue(nullptr),
    _passiveBuzzerQueue(nullptr),
    _sevenSegmentsDisplaysQueue(nullptr),
    _spiInputQueue(nullptr),
    _spiOutputQueue(nullptr)
{
    // No functionality required.
}

QueuesContext::~QueuesContext() = default;

void QueuesContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<I2cInputQueue> i2cInputQueue,
    std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
    std::unique_ptr<I2sInputQueue> i2sInputQueue,
    std::unique_ptr<I2sOutputQueue> i2sOutputQueue,
    std::unique_ptr<SpiInputQueue> spiInputQueue,
    std::unique_ptr<SpiOutputQueue> spiOutputQueue,
    std::unique_ptr<LedStripsQueue> ledStripsQueue,
    std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
    std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter,
    std::unique_ptr<PassiveBuzzerQueue> passiveBuzzerQueue,
    std::unique_ptr< SevenSegmentsDisplaysQueue> sevenSegmentsDisplaysQueue)
{
    _i2cInputQueue = std::move(i2cInputQueue);
    _i2cOutputQueue = std::move(i2cOutputQueue);
    _i2sInputQueue = std::move(i2sInputQueue);
    _i2sOutputQueue = std::move(i2sOutputQueue);
    _spiInputQueue = std::move(spiInputQueue);
    _spiOutputQueue = std::move(spiOutputQueue);
    _ledStripsQueue = std::move(ledStripsQueue);
    _diagnosticsQueue = std::move(diagnosticsQueue);
    _diagnosticsQueueWriter = std::move(diagnosticsQueueWriter);
    _passiveBuzzerQueue = std::move(passiveBuzzerQueue);
    _sevenSegmentsDisplaysQueue = std::move(sevenSegmentsDisplaysQueue);
}

I2cInputQueue& QueuesContext::GetI2cInputQueue()
{
    return *_i2cInputQueue; 
}

I2cOutputQueue& QueuesContext::GetI2cOutputQueue() 
{
    return *_i2cOutputQueue; 
}


I2sInputQueue& QueuesContext::GetI2sInputQueue()
{
    return *_i2sInputQueue;
}

I2sOutputQueue& QueuesContext::GetI2sOutputQueue()
{
    return *_i2sOutputQueue;
}

SpiInputQueue& QueuesContext::GetSpiInputQueue()
{
    return *_spiInputQueue; 
}

SpiOutputQueue& QueuesContext::GetSpiOutputQueue() 
{
    return *_spiOutputQueue; 
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

PassiveBuzzerQueue& QueuesContext::GetPassiveBuzzerQueue()
{
    return *_passiveBuzzerQueue;
}

SevenSegmentsDisplaysQueue& QueuesContext::GetSevenSegmentsDisplaysQueue()
{
    return *_sevenSegmentsDisplaysQueue;
}
