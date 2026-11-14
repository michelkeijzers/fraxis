// @file Random.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IRandom.hpp"
#include <cstdint>

namespace M80::Random
{
    class Random : public IRandom
    {
    public:
        Random();

        Random(
            const Random&) = delete;

        Random& operator=(
            const Random&) = delete;

        Random(
            Random&&) = delete;
        
        Random& operator=(
            Random&&) = delete;

        virtual ~Random() override;

        virtual uint32_t GetRandom() override = 0;

        virtual uint8_t GetNext8() override;

        virtual uint16_t GetNext16() override;

        virtual uint32_t GetNext() override;

        virtual uint32_t GetNext(
            uint32_t max) override;

        virtual uint32_t GetNextBetween(
            uint32_t min,
            uint32_t max) override;
    };
}
