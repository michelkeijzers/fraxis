// @file Random.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Random.hpp"

namespace M80::Random
{
    Random::Random() = default;

    Random::~Random() = default;

    uint8_t Random::GetNext8()
    {
        return GetRandom() & 0xFF;
    }

    uint16_t Random::GetNext16()
    {
        return GetRandom() & 0xFFFF;
    }

    uint32_t Random::GetNext()
    {
        return GetRandom();
    }

    uint32_t Random::GetNext(
        uint32_t max)
    {
        return (max == 0) ? 0 : (GetRandom() % max);
    }

    uint32_t Random::GetNextBetween(
        uint32_t min, uint32_t max)
    {
        if (min >= max)
        {
            return min;
        }

        uint32_t range = max - min + 1;
        return min + (GetRandom() % range);
    }
}
