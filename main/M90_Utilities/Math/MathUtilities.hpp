// @file MathUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IMathUtilities.hpp"

namespace M90::Math
{
    class MathUtilities : public IMathUtilities
    {
    public:
        int Clamp(
            int value,
            int minValue,
            int maxValue) const override;
    };
}
