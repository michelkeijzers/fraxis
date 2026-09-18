#pragma once

#include <memory>

// Forward declarations of domain models
class I2cInputQueue;
class I2cOutputQueue;
class LedStripsQueue;
class DiagnosticsQueue;
class DiagnosticsQueueWriter;

class QueuesContext
{
public:
    QueuesContext();
    ~QueuesContext();

    void Set(
        std::unique_ptr<I2cInputQueue> i2cInputQueue,
        std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
        std::unique_ptr<LedStripsQueue> ledStripsQueue,
        std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
        std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter
    );

    I2cInputQueue& GetI2cInputQueue();
    I2cOutputQueue& GetI2cOutputQueue();
    LedStripsQueue& GetLedStripsQueue();
    DiagnosticsQueue& GetDiagnosticsQueue();
    DiagnosticsQueueWriter& GetDiagnosticsQueueWriter();
    
private:
    std::unique_ptr<I2cInputQueue> _i2cInputQueue;
    std::unique_ptr<I2cOutputQueue> _i2cOutputQueue;
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
    std::unique_ptr<DiagnosticsQueue> _diagnosticsQueue;
    std::unique_ptr<DiagnosticsQueueWriter> _diagnosticsQueueWriter;
};
