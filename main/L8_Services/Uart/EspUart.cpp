#ifdef ESP_PLATFORM

#include "EspUart.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <cstring>

EspUart::EspUart() 
{
}

EspUart::~EspUart() 
{
}

void EspUart::Initialize(
    uint32_t baudRate,
    uint16_t rxBufferSize,
    uint16_t txBufferSize)
{
    uart_config_t cfg;
    cfg.baud_rate = baudRate;
    cfg.data_bits = UART_DATA_8_BITS;
    cfg.parity    = UART_PARITY_DISABLE;
    cfg.stop_bits = UART_STOP_BITS_1;
    cfg.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    cfg.source_clk = UART_SCLK_APB;

    uart_param_config(UART_NUM_1, &cfg);

    uart_set_pin(
        UART_NUM_1,
        GPIO_NUM_17,   // TX
        GPIO_NUM_16,   // RX
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE);

    uart_driver_install(
        UART_NUM_1,
        rxBufferSize,   // RX buffer
        txBufferSize,   // TX buffer (software buffer)
        0,
        NULL,
        0
    ); // No initialization needed for now.
}

void EspUart::Send(
    const char* data,
    const uint16_t length)
{
    Assert::IsNotNullptr(Types::ETaskId::DiagnosticsTask, (void*) data, "data");
    uart_write_bytes(UART_NUM_1, data, length);
}

#endif // ESP_PLATFORM
