#pragma once

#include "uart.hpp"

class WindowsUart : public Uart
{
public:
    WindowsUart() = default;
    ~WindowsUart() = default;

protected:
    virtual void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize);

    virtual void Send(
        const char* data,
        const uint16_t length) override;
};
