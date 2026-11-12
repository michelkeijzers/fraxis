// @file WindowsRandom.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsRandom.hpp"
#include <random>
#include <stdint.h>

namespace M80::Random
{
    uint32_t WindowsRandom::GetRandom()
    {
        return _gen();
    }
}
