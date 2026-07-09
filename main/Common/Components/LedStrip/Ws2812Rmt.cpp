#include "Ws2812Rmt.hpp"
#include "driver/rmt_tx.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

static const char* TAG = "WS2812";

Ws2812Rmt::Ws2812Rmt(gpio_num_t pin, uint16_t led_count)
    : _pin(pin), _led_count(led_count), _channel(nullptr), _encoder(nullptr)
{
}

void Ws2812Rmt::Initialize()
{
    rmt_tx_channel_config_t tx_config = {};
    tx_config.gpio_num = _pin;
    tx_config.clk_src = RMT_CLK_SRC_DEFAULT;
    tx_config.mem_block_symbols = 64;
    tx_config.resolution_hz = 10'000'000;   // 10 MHz
    tx_config.trans_queue_depth = 4;

    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_config, &_channel));
    ESP_ERROR_CHECK(rmt_enable(_channel));

    rmt_simple_encoder_config_t enc_cfg = {};
    ESP_ERROR_CHECK(rmt_new_simple_encoder(&enc_cfg, &_encoder));
}

void Ws2812Rmt::Send(const uint8_t* grb_data)
{
    // WS2812 timing (in 10 MHz ticks)
    const uint32_t T0H = 4;   // 0.4 µs
    const uint32_t T0L = 9;   // 0.85 µs
    const uint32_t T1H = 8;   // 0.8 µs
    const uint32_t T1L = 5;   // 0.45 µs

    const uint32_t reset_ticks = 300; // > 280 µs

    const size_t symbol_count = _led_count * 24 + 1;
    rmt_symbol_word_t* symbols = (rmt_symbol_word_t*)malloc(symbol_count * sizeof(rmt_symbol_word_t));

    size_t idx = 0;

    for (uint16_t led = 0; led < _led_count; ++led)
    {
        uint8_t g = grb_data[led * 3 + 0];
        uint8_t r = grb_data[led * 3 + 1];
        uint8_t b = grb_data[led * 3 + 2];

        uint32_t bits = (g << 16) | (r << 8) | b;

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

    rmt_transmit_config_t tx_cfg = {};
    tx_cfg.loop_count = 0;

    ESP_ERROR_CHECK(rmt_transmit(
        _channel,
        _encoder,
        symbols,
        symbol_count * sizeof(rmt_symbol_word_t),
        &tx_cfg
    ));

    ESP_ERROR_CHECK(rmt_tx_wait_all_done(_channel, portMAX_DELAY));

    free(symbols);
}
