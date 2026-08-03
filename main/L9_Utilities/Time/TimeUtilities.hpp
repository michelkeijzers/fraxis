#pragma once

#include <cstdint>

class TimeUtilities
{
public:
    static uint64_t GetCurrentTimeInUs();
    static uint64_t GetUsBetween(
        uint64_t fromUs, 
        uint64_t toUs);
    static uint64_t GetUsSince(
        uint64_t startUs);

    static uint64_t FrequencyToIntervalUs(
        uint32_t frequencyInHz);
};
