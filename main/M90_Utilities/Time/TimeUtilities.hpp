#pragma once

#include <cstdint>
#include <chrono>

class TimeUtilities
{
public:
    static std::chrono::microseconds GetCurrentTimeInUs();
    static std::chrono::microseconds GetUsBetween(
        std::chrono::microseconds fromUs, 
        std::chrono::microseconds toUs);
    static std::chrono::microseconds GetUsSince(
        std::chrono::microseconds startUs);

    static std::chrono::microseconds FrequencyToIntervalUs(
        uint32_t frequencyInHz);
};
