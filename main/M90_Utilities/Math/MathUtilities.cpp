// @file MathUtilities.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "MathUtilities.hpp"

namespace M90::Math
{
    int MathUtilities::Clamp(
        int value,
        int minValue,
        int maxValue) const
    {
        if (value < minValue)
        {
            return minValue;
        }

        if (value > maxValue)
        {
            return maxValue;
        }

        return value;
    }
}