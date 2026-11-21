// @file ITimeUtilities.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>
#include <chrono>

namespace M90::Time
{
    class ITimeUtilities
    {
    public:
        virtual ~ITimeUtilities() = default;

        virtual std::chrono::microseconds GetCurrentTimeInUs() const = 0;

        virtual std::chrono::microseconds GetUsBetween(
            std::chrono::microseconds fromUs,
            std::chrono::microseconds toUs) const = 0;

        virtual std::chrono::microseconds GetUsSince(
            std::chrono::microseconds startUs) const = 0;

        virtual std::chrono::microseconds FrequencyToIntervalUs(
            uint32_t frequencyInHz) const = 0;
    };
}
