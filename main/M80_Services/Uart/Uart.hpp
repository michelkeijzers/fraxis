
#pragma once

#include <cstdint>

class Uart
{
public:
    Uart() = default;
    virtual ~Uart() = default;

    virtual void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize) = 0;

    virtual void Send(
        const char* data,
        const uint16_t length) = 0;
};
