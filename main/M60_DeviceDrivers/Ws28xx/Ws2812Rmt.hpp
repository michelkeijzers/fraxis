#pragma once

#include <cstdint>
#include <vector>

class Rmt;

class Ws2812Rmt
{
public:
    Ws2812Rmt(
        uint8_t pin, 
        uint16_t led_count,
        Rmt& rmt);

    Ws2812Rmt(const Ws2812Rmt&) = delete;
    Ws2812Rmt& operator=(const Ws2812Rmt&) = delete;
    Ws2812Rmt(Ws2812Rmt&&) = delete;
    Ws2812Rmt& operator=(Ws2812Rmt&&) = delete;

    ~Ws2812Rmt();

    void Initialize();
    void Send(
        const uint8_t* grb_data);

private:
    using rmt_symbol_word_t = struct {
        uint32_t duration0 : 15;
        uint32_t level0 : 1;
        uint32_t duration1 : 15;
        uint32_t level1 : 1;
    };

    uint8_t _pin;
    uint16_t _led_count;
    Rmt& _rmt;
    std::vector<rmt_symbol_word_t> _symbol_buffer;
};
