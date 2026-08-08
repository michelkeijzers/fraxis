#include "Ws2812Rmt.hpp"
#include "../../L8_Services/Rmt/Rmt.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

typedef struct {
    uint32_t duration0 : 15;
    uint32_t level0    : 1;
    uint32_t duration1 : 15;
    uint32_t level1    : 1;
} rmt_symbol_word_t;

Ws2812Rmt::Ws2812Rmt(
    uint8_t pin, 
    uint16_t led_count,
    Rmt& rmt)
:   _pin(pin), 
    _led_count(led_count), 
    _rmt(rmt)
{
}

Ws2812Rmt::~Ws2812Rmt()
{
    Assert::IsTrue(_rmt.DelEncoder(), "Failed to delete RMT encoder");
    Assert::IsTrue(_rmt.DelChannel(), "Failed to delete RMT channel");
}

void Ws2812Rmt::Initialize()
{
    Assert::IsTrue(_rmt.NewTxChannel(_pin), "Failed to create RMT channel");
    Assert::IsTrue(_rmt.Enable(), "Failed to enable RMT");
    Assert::IsTrue(_rmt.NewSimpleEncoder(), "Failed to create RMT encoder");
}

void Ws2812Rmt::Send(
    const uint8_t* grb_data)
{
    // WS2812 timing (in 10 MHz ticks)
    constexpr uint32_t T0H = 4;   // 0.4 µs
    constexpr uint32_t T0L = 9;   // 0.85 µs
    constexpr uint32_t T1H = 8;   // 0.8 µs
    constexpr uint32_t T1L = 5;   // 0.45 µs

    constexpr uint32_t reset_ticks = 300; // > 280 µs

    const size_t symbol_count = _led_count * 24 + 1;
    auto* symbols = (rmt_symbol_word_t*)malloc(symbol_count * sizeof(rmt_symbol_word_t));

    size_t idx = 0;

    for (uint16_t led = 0; led < _led_count; ++led)
    {
        uint8_t g = grb_data[led * 3 + 0];
        uint8_t r = grb_data[led * 3 + 1];
        uint8_t b = grb_data[led * 3 + 2];

        uint32_t bits = (g << 16) | (r << 8) | b; // NOSONAR ESP32 prefers uint32_t

        for (int bit = 23; bit >= 0; --bit)
        {
            bool one = bits & (1 << bit);

            symbols[idx].duration0 = one ? T1H : T0H;
            symbols[idx].level0    = 1;
            symbols[idx].duration1 = one ? T1L : T0L;
            symbols[idx].level1    = 0;
            idx++;
        }
    }

    // Reset pulse
    symbols[idx].duration0 = reset_ticks;
    symbols[idx].level0    = 0;
    symbols[idx].duration1 = 0;
    symbols[idx].level1    = 0;

    Assert::IsTrue(_rmt.Transmit(symbols, symbol_count * sizeof(rmt_symbol_word_t)), "Failed to transmit symbols");
    Assert::IsTrue(_rmt.TxWaitAllDone(), "Failed to wait for transmission to complete");
    free(symbols);
}
