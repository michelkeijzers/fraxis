#if !defined(_WIN32) && !defined(_WIN64)

#include "EspRandom.hpp"
#include <stdint.h>
#include "esp_random.h"

uint32_t EspRandom::GetNext()
{
    return esp_random();
}

uint8_t EspRandom::GetNext8()
{
    return GetNext() & 0xFF;
}

uint16_t EspRandom::GetNext16()
{
    return GetNext() & 0xFFFF;
}

uint32_t EspRandom::GetNext(uint32_t max)
{
    return (max == 0) ? 0 : (esp_random() % max);
}

uint32_t EspRandom::GetNextBetween(uint32_t min, uint32_t max)
{
    if (min >= max)
    {
        return min;
    }

    uint32_t range = max - min + 1;
    return min + (esp_random() % range);
}

#endif