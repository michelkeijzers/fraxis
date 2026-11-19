// @file EspUart.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "uart.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M80::Uart
{
    class EspUart : public Uart
    {
    public:
        explicit EspUart(
            M90::Assert::IAssert& assert);

        EspUart(
            const EspUart&) = delete;

        EspUart& operator=(
            const EspUart&) = delete;

        EspUart(
            EspUart&&) = delete;

        EspUart& operator=(
            EspUart&&) = delete;

        ~EspUart() override;

    protected:
        void Initialize(
            uint32_t baudRate,
            uint16_t rxBufferSize,
            uint16_t txBufferSize) override;

        void Send(
            std::span<const std::byte> data) override;
    };
}

#endif // ESP_PLATFORM
