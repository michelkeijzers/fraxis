// @file Random.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>

namespace M80::Random
{
    class Random
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

        virtual ~Random();

        virtual uint32_t GetRandom() = 0;

        virtual uint8_t GetNext8();

        virtual uint16_t GetNext16();

        virtual uint32_t GetNext();

        virtual uint32_t GetNext(
            uint32_t max);

        virtual uint32_t GetNextBetween(
            uint32_t min,
            uint32_t max);
    };
}
