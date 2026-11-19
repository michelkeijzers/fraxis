// @file Spi.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Spi.hpp"

namespace M80::Spi
{
    Spi::Spi(
        M90::Assert::IAssert& assert)
        :
        M80::Service(assert)
    {
        // No functionality required.
    }
}
