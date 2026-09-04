#ifdef ESP_PLATFORM

#pragma once

#include "uart.hpp"

class EspUart : public Uart
{
public:
    EspUart();
    ~EspUart();

protected:
    virtual void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize);

    virtual void Send(
        const char* data,
        const uint16_t length) override;
};

#endif // ESP_PLATFORM
