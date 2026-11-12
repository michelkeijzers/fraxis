// @file WindowsRmt.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Rmt.hpp"

namespace M80::Rmt
{
    class WindowsRmt : public Rmt
    {
    public:
        WindowsRmt() = default;
        ~WindowsRmt() = default;

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
    };
}
