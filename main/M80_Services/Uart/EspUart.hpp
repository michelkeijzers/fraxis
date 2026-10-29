#ifdef ESP_PLATFORM

#pragma once

#include "uart.hpp"

class EspUart : public Uart
{
public:
    EspUart();
    
    EspUart(const EspUart&) = delete;
    EspUart& operator=(const EspUart&) = delete;
    EspUart(EspUart&&) = delete;
    EspUart& operator=(EspUart&&) = delete;

    ~EspUart() override;

protected:
    void Initialize(
        uint32_t baudRate,
        uint16_t rxBufferSize,
        uint16_t txBufferSize) override;

    void Send(
        std::span<const std::byte> data) override;
};

#endif // ESP_PLATFORM
