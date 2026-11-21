// @file TimeUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "ITimeUtilities.hpp"

namespace M90::Time
{
    class TimeUtilities : public ITimeUtilities
    {
    public:
        TimeUtilities() = default;

        ~TimeUtilities() = default;

        std::chrono::microseconds GetCurrentTimeInUs() const override;

        std::chrono::microseconds GetUsBetween(
            std::chrono::microseconds fromUs,
            std::chrono::microseconds toUs) const override;

        std::chrono::microseconds GetUsSince(
            std::chrono::microseconds startUs) const override;

        std::chrono::microseconds FrequencyToIntervalUs(
            uint32_t frequencyInHz) const override;
    };
}
