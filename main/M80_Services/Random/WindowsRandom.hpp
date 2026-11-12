// @file WindowsRandom.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>
#include "Random.hpp"
#include <random>

namespace M80::Random
{
    class WindowsRandom : public Random
    {
    public:
        WindowsRandom() = default;

        ~WindowsRandom() = default;

        uint32_t GetRandom() override;

    private:
        std::mt19937 _gen; // NOSONAR: S2245 Safe (not used for critical random values)
    };
}
