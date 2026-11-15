// @file Assert.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Algorithm.hpp"

namespace M90::Algorithm
{
    void Algorithm::Swap(
        uint8_t& a, 
        uint8_t& b)
    {
        uint8_t temp = a;
        a = b;
        b = temp;
    }

    void Algorithm::Swap(
        uint16_t& a, 
        uint16_t& b)
    {
        uint16_t temp = a;
        a = b;
        b = temp;
    }

    void Algorithm::Swap(
        uint32_t& a, 
        uint32_t& b)
    {
        uint32_t temp = a;
        a = b;
        b = temp;
    }
}
