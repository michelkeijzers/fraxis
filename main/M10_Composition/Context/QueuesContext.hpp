#pragma once

#include <memory>

// Forward declarations of domain models
class I2cInputQueue;
class I2cOutputQueue;
class SpiInputQueue;
class SpiOutputQueue;
class LedStripsQueue;
class DiagnosticsQueue;
class DiagnosticsQueueWriter;
class I2sInputQueue;
class I2sOutputQueue;
class PassiveBuzzerOutputQueue;

class QueuesContext
{
public:
    QueuesContext();

    QueuesContext(
        const QueuesContext&) = delete;

    QueuesContext& operator=(
        const QueuesContext&) = delete;

    QueuesContext(
        QueuesContext&&) = delete;

    QueuesContext& operator=(
        QueuesContext&&) = delete;

    ~QueuesContext();

    void Set(
        std::unique_ptr<I2cInputQueue> i2cInputQueue,
        std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
        std::unique_ptr<SpiInputQueue> spiInputQueue,
        std::unique_ptr<SpiOutputQueue> spiOutputQueue,
        std::unique_ptr<LedStripsQueue> ledStripsQueue,
        std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
        std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter,
        std::unique_ptr<I2sInputQueue> i2sInputQueue,
        std::unique_ptr<I2sOutputQueue> i2sOutputQueue,
        std::unique_ptr<PassiveBuzzerOutputQueue> passiveBuzzerOutputQueue);

    I2cInputQueue& GetI2cInputQueue();
    
    I2cOutputQueue& GetI2cOutputQueue();
    
    SpiInputQueue& GetSpiInputQueue();
    
    SpiOutputQueue& GetSpiOutputQueue();
    
    LedStripsQueue& GetLedStripsQueue();
    
    DiagnosticsQueue& GetDiagnosticsQueue();
    
    DiagnosticsQueueWriter& GetDiagnosticsQueueWriter();
    
    I2sInputQueue& GetI2sInputQueue();
    
    I2sOutputQueue& GetI2sOutputQueue();
    
    PassiveBuzzerOutputQueue& GetPassiveBuzzerOutputQueue();
    
private:
    std::unique_ptr<I2cInputQueue> _i2cInputQueue;
    
    std::unique_ptr<I2cOutputQueue> _i2cOutputQueue;
    
    std::unique_ptr<SpiInputQueue> _spiInputQueue;
    
    std::unique_ptr<SpiOutputQueue> _spiOutputQueue;
    
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
    
    std::unique_ptr<DiagnosticsQueue> _diagnosticsQueue;
    
    std::unique_ptr<DiagnosticsQueueWriter> _diagnosticsQueueWriter;
    
    std::unique_ptr<I2sInputQueue> _i2sInputQueue;
    
    std::unique_ptr<I2sOutputQueue> _i2sOutputQueue;

    std::unique_ptr<PassiveBuzzerOutputQueue> _passiveBuzzerOutputQueue;
};
