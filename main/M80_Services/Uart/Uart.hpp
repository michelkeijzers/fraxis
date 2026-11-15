// @file Uart.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IUart.hpp" 

namespace M80::Uart
{
    class Uart : public IUart
    {
    public:
        Uart() = default;

        Uart(
            const Uart&) = delete;

        Uart& operator=(
            const Uart&) = delete;

        Uart(
            Uart&&) = delete;

        Uart& operator=(
            Uart&&) = delete;

        virtual ~Uart() = default;

        virtual void Initialize(
            uint32_t baudRate,
            uint16_t rxBufferSize,
            uint16_t txBufferSize) = 0;

        virtual void Send(
            std::span<const std::byte> data) = 0;
    };
}
