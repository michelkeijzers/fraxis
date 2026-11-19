// @file EspRandom.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "Random.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M80::Random
{
    class EspRandom : public Random
    {
    public:
        explicit EspRandom(
            M90::Assert::IAssert& assert);

        EspRandom(
            const EspRandom&) = delete;

        EspRandom& operator=(
            const EspRandom&) = delete;

        EspRandom(
            EspRandom&&) = delete;

        EspRandom& operator=(
            EspRandom&&) = delete;

        ~EspRandom() override;

    private:
        uint32_t GetRandom() override;
    };
}

#endif // ESP_PLATFORM
