#pragma once

#include <cstdint>
#include <span>

class Uart
{
public:
    Uart() = default;

    Uart(const Uart&) = delete;
    Uart& operator=(const Uart&) = delete;
    Uart(Uart&&) = delete;
    Uart& operator=(Uart&&) = delete;

    virtual ~Uart() = default;

    virtual void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize) = 0;

    virtual void Send(
        std::span<const std::byte> data) = 0;
};
