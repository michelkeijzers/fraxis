// @file Algorithm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IAlgorithm.hpp" 

namespace M90::Algorithm
{
    class Algorithm : public IAlgorithm
    {
    public:
        void Swap(
            uint8_t& a,
            uint8_t& b) override;

        void Swap(
            uint16_t& a,
            uint16_t& b) override;

        void Swap(
            uint32_t& a,
            uint32_t& b) override;
    };
}
