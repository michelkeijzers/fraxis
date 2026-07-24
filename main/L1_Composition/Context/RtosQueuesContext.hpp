#pragma once

#include <memory>

// Forward declarations of domain models
class LedStripsQueue;
class InputQueue;
class OutputQueue;

class RtosQueuesContext
{
public:
    RtosQueuesContext();
    ~RtosQueuesContext();

    void Set(
        std::unique_ptr<LedStripsQueue> ledStripsQueue,
        std::unique_ptr<InputQueue> inputQueue,
        std::unique_ptr<OutputQueue> outputQueue);

    LedStripsQueue& GetLedStripsQueue() { return *_ledStripsQueue; }
    InputQueue& GetInputQueue()     { return *_inputQueue; }
    OutputQueue& GetOutputQueue()    { return *_outputQueue; }
    
private:
    std::unique_ptr<LedStripsQueue> _ledStripsQueue;
    std::unique_ptr<InputQueue> _inputQueue;
    std::unique_ptr<OutputQueue> _outputQueue;
};
