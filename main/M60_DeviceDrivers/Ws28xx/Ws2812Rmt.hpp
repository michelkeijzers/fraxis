#pragma once

#include <cstdint>

class Rmt;

class Ws2812Rmt
{
public:
    Ws2812Rmt(
        uint8_t pin, 
        uint16_t led_count,
        Rmt& rmt);
    ~Ws2812Rmt();

    void Initialize();
    void Send(
        const uint8_t* grb_data);

private:
    uint8_t _pin;
    uint16_t _led_count;
    Rmt& _rmt;
};
