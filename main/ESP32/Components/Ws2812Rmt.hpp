#pragma once

#include <cstdint>
#include "driver/rmt_tx.h"

class Ws2812Rmt
{
public:
    Ws2812Rmt(gpio_num_t pin, uint16_t led_count);

    void Initialize();
    void Send(const uint8_t* grb_data);

private:
    gpio_num_t _pin;
    uint16_t _led_count;

    rmt_channel_handle_t _channel;
    rmt_encoder_handle_t _encoder;
};
