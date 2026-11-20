// @file BitUtilities.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>

namespace M90::Math
{
    /// @brief This class contains bit related functionality.
    /// @remarks 
    /// This class is NOT used in the production code of Fraxis.
    /// Therefore, no IBitUtilities.hpp created.
    class BitUtilities
    {
    public:
        BitUtilities() = default;

        ~BitUtilities() = default;

        /// @brief Sets a bit in a value
        int SetBit(
            int value, 
            uint8_t bitNumber, 
            bool on) const
        {
            int mask = 1 << bitNumber;
            return on ? (value | mask) : (value & ~mask);
        }

        bool IsBitSet(
            int value,
            uint8_t bitNumber) const
        {
            return (value & (1 << bitNumber)) != 0;
        }
    };
}
