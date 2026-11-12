// @file EspRandom.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#include "EspRandom.hpp"
#include <stdint.h>
#include "esp_random.h"

namespace M80::Random
{
    EspRandom::EspRandom() = default;

    EspRandom::~EspRandom() = default;

    uint32_t EspRandom::GetRandom()
    {
        return esp_random();
    }
}

#endif // ESP_PLATFORM
