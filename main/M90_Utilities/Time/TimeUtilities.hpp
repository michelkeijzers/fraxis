#pragma once

#include <cstdint>
#include <chrono>

namespace M90::Time
{
    class TimeUtilities
    {
    public:
        static constexpr uint32_t GetUnixTime(
            uint16_t year,
            uint8_t month,
            uint8_t day,
            uint8_t hour,
            uint8_t minute,
            uint8_t second)
        {
            int y = year;
            int m = month;
            if (m <= 2) {
                m += 12;
                y -= 1;
            }

            int32_t days =
                (365L * y) + (y / 4) - (y / 100) + (y / 400) + ((153 * m + 8) / 5) + day - 719468;

            int64_t total_seconds = (static_cast<int64_t>(days) * 86400) +
                (static_cast<int64_t>(hour) * 3600) +
                (static_cast<int64_t>(minute) * 60) +
                second;

            if (total_seconds < 0) return 0;
            if (total_seconds > UINT32_MAX) return UINT32_MAX;

            return static_cast<uint32_t>(total_seconds);
        };

        static std::chrono::microseconds GetCurrentTimeInUs();
        static std::chrono::microseconds GetUsBetween(
            std::chrono::microseconds fromUs,
            std::chrono::microseconds toUs);
        static std::chrono::microseconds GetUsSince(
            std::chrono::microseconds startUs);

        static std::chrono::microseconds FrequencyToIntervalUs(
            uint32_t frequencyInHz);
    };
}
