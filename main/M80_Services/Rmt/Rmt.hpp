// @file Rmt.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif

#include <cstdint>
#include <stddef.h>
#include <vector>

namespace M80::Rmt
{
    class Rmt
    {
    public:
        Rmt() = default;

        Rmt(
            const Rmt&) = delete;

        Rmt& operator=(
            const Rmt&) = delete;

        Rmt(
            Rmt&&) = delete;

        Rmt& operator=(
            Rmt&&) = delete;

        virtual ~Rmt() = default;

        virtual esp_err_t DelEncoder() = 0;

        virtual esp_err_t DelChannel() = 0;

        virtual esp_err_t NewTxChannel(
            uint8_t pin) = 0;

        virtual esp_err_t Enable() = 0;

        virtual esp_err_t NewSimpleEncoder() = 0;

        virtual esp_err_t Transmit(
            const void* payload, // NOSONAR S5008: TODO: void* to more useful
            size_t payload_bytes) = 0;

        virtual esp_err_t TxWaitAllDone() = 0;
    };
}
