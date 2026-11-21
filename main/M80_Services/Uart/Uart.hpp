// @file Uart.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Service.hpp"
#include "IUart.hpp" 

namespace M90::Assert
{
    class IAssert;
}

namespace M80::Uart
{
    class Uart : public Service, public IUart
    {
    public:
        explicit Uart(
            M90::Assert::IAssert& assert);

        Uart(
            const Uart&) = delete;

        Uart& operator=(
            const Uart&) = delete;

        Uart(
            Uart&&) = delete;

        Uart& operator=(
            Uart&&) = delete;

        virtual ~Uart() = default;

        void Initialize(
            uint32_t baudRate,
            uint16_t rxBufferSize,
            uint16_t txBufferSize) override = 0;

        void Send(
            std::span<const std::byte> data) override = 0;
    };
}
