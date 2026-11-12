// @file WindowsUart.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Uart.hpp"

namespace M80::Uart
{
    class WindowsUart : public Uart
    {
    public:
        WindowsUart() = default;

        ~WindowsUart() = default;

    protected:
        void Initialize(
            uint32_t baudRate,
            uint16_t rxBufferSize,
            uint16_t txBufferSize) override;

        void Send(
            std::span<const std::byte> data) override;
    };
}
