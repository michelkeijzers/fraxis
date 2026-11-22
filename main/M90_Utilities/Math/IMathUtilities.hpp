// @file IMathUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

namespace M90::Math
{
    class IMathUtilities
    {
    public:
        virtual ~IMathUtilities() = default; 

        virtual int Clamp(
            int value,
            int minValue,
            int maxValue) const = 0;
    };
}
