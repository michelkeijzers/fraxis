#pragma once

#include "Uart.hpp"

class WindowsUart : public Uart
{
public:
    WindowsUart() = default;
    ~WindowsUart() = default;

protected:
    void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize) override;

    void Send(
        std::span<const std::byte> data) override;
};
