#include "QueuesContext.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M30_Messages/I2cInputQueue.hpp"
#include "../../M30_Messages/I2cOutputQueue.hpp"
#include "../../M30_Messages/SpiInputQueue.hpp"
#include "../../M30_Messages/SpiOutputQueue.hpp"
#include "../../M30_Messages/LedStripsQueue.hpp"
#include "../../M30_Messages/DiagnosticsQueue.hpp"
#include "../../M30_Messages/Audio/AudioInputQueue.hpp"
#include "../../M30_Messages/Audio/AudioOutputQueue.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

QueuesContext::QueuesContext()
: 
_i2cInputQueue(nullptr), 
    _i2cOutputQueue(nullptr), 
    _spiOutputQueue(nullptr), 
    _ledStripsQueue(nullptr),
    _diagnosticsQueue(nullptr),
    _audioInputQueue(nullptr),
    _audioOutputQueue(nullptr)
{
}

QueuesContext::~QueuesContext()
{
}

void QueuesContext::Set(
    std::unique_ptr<I2cInputQueue> i2cInputQueue,
    std::unique_ptr<I2cOutputQueue> i2cOutputQueue,
    std::unique_ptr<SpiInputQueue> spiInputQueue,
    std::unique_ptr<SpiOutputQueue> spiOutputQueue,
    std::unique_ptr<LedStripsQueue> ledStripsQueue,
    std::unique_ptr<DiagnosticsQueue> diagnosticsQueue,
    std::unique_ptr<DiagnosticsQueueWriter> diagnosticsQueueWriter,
    std::unique_ptr<AudioInputQueue> audioInputQueue,
    std::unique_ptr<AudioOutputQueue> audioOutputQueue)
{
    _i2cInputQueue = std::move(i2cInputQueue);
    _i2cOutputQueue = std::move(i2cOutputQueue);
    _spiInputQueue = std::move(spiInputQueue);
    _spiOutputQueue = std::move(spiOutputQueue);
    _ledStripsQueue = std::move(ledStripsQueue);
    _diagnosticsQueue = std::move(diagnosticsQueue);
    _diagnosticsQueueWriter = std::move(diagnosticsQueueWriter);
    _audioInputQueue = std::move(audioInputQueue);
    _audioOutputQueue = std::move(audioOutputQueue);
}

I2cInputQueue& QueuesContext::GetI2cInputQueue()
{
    return *_i2cInputQueue; 
}

I2cOutputQueue& QueuesContext::GetI2cOutputQueue() 
{
    return *_i2cOutputQueue; 
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

AudioInputQueue& QueuesContext::GetAudioInputQueue()
{
    return *_audioInputQueue;
}

AudioOutputQueue& QueuesContext::GetAudioOutputQueue()
{
    return *_audioOutputQueue;
}
