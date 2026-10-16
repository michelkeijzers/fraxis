#include "TimeUtilities.hpp"

#include <chrono>
using namespace std::chrono;
    
/* static */ std::chrono::microseconds TimeUtilities::GetCurrentTimeInUs()
{
    return duration_cast<microseconds>(steady_clock::now().time_since_epoch());
}

/* static */ std::chrono::microseconds TimeUtilities::GetUsBetween(
    std::chrono::microseconds fromUs,
    std::chrono::microseconds toUs)
{
    return toUs - fromUs;
}

/* static */ std::chrono::microseconds TimeUtilities::GetUsSince(
    std::chrono::microseconds startUs)
{
    std::chrono::microseconds nowUs = GetCurrentTimeInUs();
    std::chrono::microseconds diffUs = nowUs - startUs;

    return duration_cast<microseconds>(microseconds(diffUs));
}

/* static */ std::chrono::microseconds TimeUtilities::FrequencyToIntervalUs(
    uint32_t frequencyInHz) 
{
    return std::chrono::microseconds(1'000'000 / frequencyInHz);
}
