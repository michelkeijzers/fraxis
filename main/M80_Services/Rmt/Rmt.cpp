// @file Rmt.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Rmt.hpp"

namespace M80::Rmt
{
    Rmt::Rmt(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No functionality required.
    }
}