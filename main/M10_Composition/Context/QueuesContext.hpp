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
class AudioInputQueue;
class AudioOutputQueue;

class QueuesContext
{
public:
    QueuesContext();
    ~QueuesContext();

    void Set(
        std::unique_ptr<I2cInputQueue> i2cInputQueue,
        std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
        std::unique_ptr<SpiInputQueue> spiInputQueue,
        std::unique_ptr<SpiOutputQueue> spiOutputQueue,
        std::unique_ptr<LedStripsQueue> ledStripsQueue,
        std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
        std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter,
        std::unique_ptr<AudioInputQueue> audioInputQueue,
        std::unique_ptr<AudioOutputQueue> audioOutputQueue);

    I2cInputQueue& GetI2cInputQueue();
    I2cOutputQueue& GetI2cOutputQueue();
    SpiInputQueue& GetSpiInputQueue();
    SpiOutputQueue& GetSpiOutputQueue();
    LedStripsQueue& GetLedStripsQueue();
    DiagnosticsQueue& GetDiagnosticsQueue();
    DiagnosticsQueueWriter& GetDiagnosticsQueueWriter();
    AudioInputQueue& GetAudioInputQueue();
    AudioOutputQueue& GetAudioOutputQueue();
    
private:
    std::unique_ptr<I2cInputQueue> _i2cInputQueue;
    std::unique_ptr<I2cOutputQueue> _i2cOutputQueue;
    std::unique_ptr<SpiInputQueue> _spiInputQueue;
    std::unique_ptr<SpiOutputQueue> _spiOutputQueue;
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
    std::unique_ptr<DiagnosticsQueue> _diagnosticsQueue;
    std::unique_ptr<DiagnosticsQueueWriter> _diagnosticsQueueWriter;
    std::unique_ptr<AudioInputQueue> _audioInputQueue;
    std::unique_ptr<AudioOutputQueue> _audioOutputQueue;
};
