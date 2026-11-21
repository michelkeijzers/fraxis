// @file I2sService.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "I2sService.hpp"

namespace M80::I2s
{
    I2sService::I2sService(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No functionality required.
    }
}
