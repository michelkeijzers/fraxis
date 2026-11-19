// @file IRtosQueue.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M80_Services/IService.hpp"
#include <cstdint>

namespace M81::RtosQueue
{
    class IRtosQueue
    {
    public:
        IRtosQueue() = default;

        IRtosQueue(
            const IRtosQueue&) = delete;

        IRtosQueue& operator=(
            const IRtosQueue&) = delete;

        IRtosQueue(
            IRtosQueue&&) = delete;
        
        IRtosQueue& operator=(
            IRtosQueue&&) = delete;

        virtual ~IRtosQueue() = default;

        virtual bool Send(
            const void* itemToQueue,
            uint32_t msToWait) = 0;

        virtual bool Receive(
            void* item,
            uint32_t
            msToWait) = 0;

        virtual bool Peek(
            void* item,
            uint32_t ticksToWait) = 0;

        [[nodiscard]] virtual uint32_t MessagesWaiting() const = 0;

        [[nodiscard]] virtual uint32_t SpacesAvailable() const = 0;

    };
}
