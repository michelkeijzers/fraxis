// @file IAlgorithm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>

namespace M90::Algorithm
{
    class IAlgorithm
    {
    public:
        virtual void Swap(
            uint16_t& a,
            uint16_t& b) = 0;

        virtual void Swap(
            uint8_t& a,
            uint8_t& b) = 0;

        virtual void Swap(
            uint32_t& a,
            uint32_t& b) = 0;
    };
}
