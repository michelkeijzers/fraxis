// @file Uart.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>
#include <span>

namespace M80::Uart
{
    class IUart
    {
    public:
        IUart() = default;

        IUart(
            const IUart&) = delete;

        IUart& operator=(
            const IUart&) = delete;

        IUart(
            IUart&&) = delete;

        IUart& operator=(
            IUart&&) = delete;

        virtual ~IUart() = default;

        virtual void Initialize(
            uint32_t baudRate,
            uint16_t rxBufferSize,
            uint16_t txBufferSize) = 0;

        virtual void Send(
            std::span<const std::byte> data) = 0;
    };
}
