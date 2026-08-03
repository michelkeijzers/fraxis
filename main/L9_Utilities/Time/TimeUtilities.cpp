#include "TimeUtilities.hpp"

#include <chrono>
using namespace std::chrono;
    
/* static */ uint64_t TimeUtilities::GetCurrentTimeInUs()
{
    return duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
}

/* static */ uint64_t TimeUtilities::GetUsBetween(
    uint64_t fromUs,
    uint64_t toUs)
{
    return toUs - fromUs;
}

/* static */ uint64_t TimeUtilities::GetUsSince(
    uint64_t startUs)
{
    uint64_t nowUs = GetCurrentTimeInUs();
    uint64_t diffUs = nowUs - startUs;

    return duration_cast<milliseconds>(
        microseconds(diffUs)
    ).count();
}

/* static */ uint64_t TimeUtilities::FrequencyToIntervalUs(
    uint32_t frequencyInHz) 
{
    return 1'000'000 / frequencyInHz;
}
