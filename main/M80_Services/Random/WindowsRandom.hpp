// @file WindowsRandom.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>
#include "Random.hpp"
#include <random>

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::Random
{
    class WindowsRandom : public Random
    {
    public:
        explicit WindowsRandom(
            M90::Assert::IAssert& assert);

        ~WindowsRandom() = default;

        uint32_t GetRandom() override;

    private:
        std::mt19937 _gen; // NOSONAR: S2245 Safe (not used for critical random values)
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
