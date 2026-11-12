// @file Algorithm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

namespace M90::Algorithm
{
    class Algorithm
    {
    public:
        template<typename T>
        static void Swap(
            T& a,
            T& b)
        {
            T temp = a;
            a = b;
            b = temp;
        }
    };
}
