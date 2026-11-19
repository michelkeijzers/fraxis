// @file Uart.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Uart.hpp"

namespace M80::Uart
{
    Uart::Uart(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No functionality required.
    }
}
