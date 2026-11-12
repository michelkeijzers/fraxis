// @file EspRmt.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "Rmt.hpp"
#include "driver/rmt_tx.h"

namespace M80::Rmt
{
    class EspRmt : public Rmt
    {
    public:
        EspRmt();

        EspRmt(
            const EspRmt&) = delete;

        EspRmt& operator=(
            const EspRmt&) = delete;

        EspRmt(
            EspRmt&&) = delete;

        EspRmt& operator=(
            EspRmt&&) = delete;

        ~EspRmt() override;

    private:
        esp_err_t DelEncoder() override;

        esp_err_t DelChannel() override;

        esp_err_t NewTxChannel(
            uint8_t pin) override;

        esp_err_t Enable() override;

        esp_err_t NewSimpleEncoder() override;

        esp_err_t Transmit(
            const void* payload,
            size_t payload_bytes) override;

        esp_err_t TxWaitAllDone() override;

        rmt_channel_handle_t _channel;
        rmt_encoder_handle_t _encoder;
    };
}

#endif
