// @file IMathUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>
#include <type_traits> 

namespace M90::Math
{
    class IMathUtilities
    {
    public:
        virtual int Clamp(
            int value,
            int minValue,
            int maxValue) const = 0;
    };
}
