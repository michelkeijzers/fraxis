// @file TimeUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "TimeUtilities.hpp"

using namespace std::chrono;

namespace M90::Time
{
    std::chrono::microseconds TimeUtilities::GetCurrentTimeInUs() const
    {
        return duration_cast<microseconds>(steady_clock::now().time_since_epoch());
    }

    std::chrono::microseconds TimeUtilities::GetUsBetween(
        std::chrono::microseconds fromUs,
        std::chrono::microseconds toUs) const
    {
        return toUs - fromUs;
    }

    std::chrono::microseconds TimeUtilities::GetUsSince(
        std::chrono::microseconds startUs) const
    {
        std::chrono::microseconds nowUs = GetCurrentTimeInUs();
        std::chrono::microseconds diffUs = nowUs - startUs;

        return duration_cast<microseconds>(microseconds(diffUs));
    }

    std::chrono::microseconds TimeUtilities::FrequencyToIntervalUs(
        uint32_t frequencyInHz) const
    {
        return std::chrono::microseconds(1'000'000 / frequencyInHz);
    }
}
