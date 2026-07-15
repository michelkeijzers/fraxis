#pragma once

#include <cstdint>

class LedStripMessage
{
public:
    enum class EId
    {
        Initialize,
        BufferReady
    };

    struct InitializeParameters
    {
        uint16_t numberOfLeds;
        uint8_t dataPin;
    };

    struct BufferReadyParameters
    {
    };

    EId id;

    union 
    {
        InitializeParameters  initializeParameters;
        BufferReadyParameters bufferReadyParameters;   
    };
};
