// @file WindowsRmt.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Rmt.hpp"

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::Rmt
{
    class WindowsRmt : public Rmt
    {
    public:
        explicit WindowsRmt(
            M90::Assert::IAssert& assert);

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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
