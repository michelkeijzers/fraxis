// @file IRandom.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M80_Services/IService.hpp"
#include <cstdint>

namespace M80::Random
{
    class IRandom : virtual public IService
    {
    public:
        IRandom& operator=(
            IRandom&&) = delete;

        virtual ~IRandom() = default;

        virtual uint32_t GetRandom() = 0;

        virtual uint8_t GetNext8() = 0;

        virtual uint16_t GetNext16() = 0;

        virtual uint32_t GetNext() = 0;

        virtual uint32_t GetNext(
            uint32_t max) = 0;

        virtual uint32_t GetNextBetween(
            uint32_t min,
            uint32_t max) = 0;
    };
}
