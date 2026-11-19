// @file I2c.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "I2c.hpp"

namespace M80::I2c
{
    I2c::I2c(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No functionality required.
    }
}
