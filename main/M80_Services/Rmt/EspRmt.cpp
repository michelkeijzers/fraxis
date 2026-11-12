// @file EspRmt.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#include "EspRmt.hpp"
#include "freertos/FreeRTOS.h"

namespace M80::Rmt
{
    EspRmt::EspRmt()
        : _channel(nullptr),
        _encoder(nullptr)
    {}

    EspRmt::~EspRmt()
    {}

    esp_err_t EspRmt::DelEncoder()
    {
        return rmt_del_encoder(_encoder);
    }

    esp_err_t EspRmt::DelChannel()
    {
        return rmt_del_channel(_channel);
    }

    esp_err_t EspRmt::NewTxChannel(
        uint8_t pin)
    {
        rmt_tx_channel_config_t tx_config = {};
        tx_config.gpio_num = static_cast<gpio_num_t>(pin);
        tx_config.clk_src = RMT_CLK_SRC_DEFAULT;
        tx_config.mem_block_symbols = 64;
        tx_config.resolution_hz = 10'000'000;   // 10 MHz
        tx_config.trans_queue_depth = 4;

        return rmt_new_tx_channel(&tx_config, &_channel);
    }

    esp_err_t EspRmt::Enable()
    {
        return rmt_enable(_channel);
    }

    esp_err_t EspRmt::NewSimpleEncoder()
    {
        rmt_simple_encoder_config_t enc_cfg = {};
        return rmt_new_simple_encoder(&enc_cfg, &_encoder);
    }

    esp_err_t EspRmt::Transmit(
        const void* payload,
        size_t payload_bytes)
    {
        rmt_transmit_config_t transmit_config = {};
        transmit_config.loop_count = 0;

        return rmt_transmit(_channel, _encoder, payload, payload_bytes, &transmit_config);
    }

    esp_err_t EspRmt::TxWaitAllDone()
    {
        constexpr int infiniteWait = -1;
        return rmt_tx_wait_all_done(_channel, infiniteWait);
    }
}

#endif // ESP_PLATFORM
