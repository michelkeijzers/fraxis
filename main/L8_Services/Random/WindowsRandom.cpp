#include "WindowsRandom.hpp"
#include <random>
#include <stdint.h>

WindowsRandom::WindowsRandom()
    : _gen(std::random_device{}())
{
}

uint32_t WindowsRandom::GetNext()
{
    return _gen();
}

uint8_t WindowsRandom::GetNext8()
{
    return static_cast<uint8_t>(_gen() & 0xFF);
}

uint16_t WindowsRandom::GetNext16()
{
    return static_cast<uint16_t>(_gen() & 0xFFFF);
}

uint32_t WindowsRandom::GetNext(uint32_t max)
{
    if (max == 0)
        return 0;

    std::uniform_int_distribution<uint32_t> dist(0, max - 1);
    return dist(_gen);
}

uint32_t WindowsRandom::GetNextBetween(uint32_t min, uint32_t max)
{
    if (min >= max)
        return min;

    std::uniform_int_distribution<uint32_t> dist(min, max);
    return dist(_gen);
}
