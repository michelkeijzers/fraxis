// @file RtosQueue.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M80_Services/Service.hpp"
#include "IRtosQueue.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M81::RtosQueue
{
    class RtosQueue : public M80::Service, public IRtosQueue
    {
    public:
        explicit RtosQueue(
            M90::Assert::IAssert& assert);

        RtosQueue(
            const RtosQueue&) = delete;

        RtosQueue& operator=(
            const RtosQueue&) = delete;

        RtosQueue(
            RtosQueue&&) = delete;

        RtosQueue& operator=(
            RtosQueue&&) = delete;

        virtual ~RtosQueue() = default;
    };
}
